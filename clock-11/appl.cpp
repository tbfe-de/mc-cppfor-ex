#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <regex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "Clock.h"

namespace UI { ////////////////////////////////////////////////////////////////

struct CommandMenu {
    std::string description;
    std::string syntax_regex;
    std::function<void(const std::smatch&)> execute;
};

using MenuControl = std::initializer_list<CommandMenu>;
using MenuPrelude = std::function<void()>;

void normalize_ws(std::string& line) {
        static const std::regex strip_ws_left{R"(^[ \t]+)",
                                std::regex_constants::optimize};
        static const std::regex strip_ws_right{R"([ \t]+$)",
                                std::regex_constants::optimize};
        static const std::regex trim_ws_middle{R"([ \t]+)",
                                std::regex_constants::optimize};
        static const char space[2] = {' ', '\0'};        // replace by ...
        line = std::regex_replace(line, strip_ws_left, &space[1]);  // nothing
        line = std::regex_replace(line, strip_ws_right, &space[1]); // nothing
        line = std::regex_replace(line, trim_ws_middle, &space[0]); // 1 space
}

void debug_match_args(const std::smatch& m, std::ostream& dbg_log) {
    dbg_log << "arguments matched: " << m.size() << std::endl;
    for (std::smatch::size_type n = 1; n < m.size(); ++n) {
        dbg_log << "- [" << n << "]:\t" << m[n].str() << std::endl;
    }
}

void main_loop(std::istream& in, std::ostream& out, std::ostream& dbg_log,
               MenuPrelude prelude, const MenuControl& menu) {
    auto show_help = [&] {
        out << "--- Available Commands:\n";
        for (const auto& e : menu) {
            out << "  : " << e.description << std::endl;
        }
    };
    auto parse_line = [&](const std::string cmd) {
        for (const auto& e : menu) {
            std::regex re{e.syntax_regex};
            std::smatch m;
            if (!std::regex_match(cmd, m, re)) continue;
            dbg_log << "OK: " << e.description << std::endl;
            if (e.execute) {
                try {
                    e.execute(m);
                }
                catch (std::exception& ex) {
                    out << "!!! " << ex.what() << std::endl;
                }
            }
            else {
                out << "!!! **not yet implemented**" << std::endl;
            }
            return true;
        }
        return false;
    };

    show_help();
    std::string cmd;
    while ((prelude ? prelude() : []{}()),
           out << "==> " << std::flush,
           std::getline(in, cmd)) {
        normalize_ws(cmd);
        if (!parse_line(cmd)) show_help();
    }
}

} //namespace UI///////////////////////////////////////////////////////////////

namespace KitchenTimer { //////////////////////////////////////////////////////

    enum class State : char {
        Ready      = 'R',
        Countdown  = 'C',
        Paused     = 'P',
        Expired    = 'X',
    };

    using ControlledClock = std::tuple<Clock, State>;
    using TimerCollection = std::vector<ControlledClock>;
    using DHMS = std::array<Clock::value_type, 4>;

    struct CommandError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };
    struct NoSuchTimer : public CommandError {
        NoSuchTimer() : CommandError("no such timer") {}
    };
    struct TimerStillInUse : public CommandError {
        TimerStillInUse() : CommandError("timer still in use") {}
    };
    struct OutOfRange : public CommandError {
        OutOfRange() : CommandError("out of range value") {}
    };

    TimerCollection allTimers;

    auto CC_IteratorFor(const std::string& name) {
        auto name_cmp {
            [name_c_str = name.c_str()](const auto& e) {
                const auto& clockRef{ std::get<Clock>(e) };
                return (std::strcmp(clockRef.GetName(), name_c_str) == 0);
            }
        };
        const auto result {
            std::find_if(allTimers.begin(), allTimers.end(), name_cmp)
        };
        if (result == allTimers.end()) {
            throw NoSuchTimer{};
        }
        return result;
    }

    void Create(const std::string& name, const DHMS& dhms) {
        try {
            auto& ccRef{ *CC_IteratorFor(name) };
            auto& clockRef{ std::get<Clock>(ccRef) };
            auto& stateRef{ std::get<State>(ccRef) };
            if (stateRef != State::Ready) {
                throw TimerStillInUse{};
            }
            try {
                clockRef.Days(dhms.at(0))
                        .Hours(dhms.at(1))
                        .Minutes(dhms.at(2))
                        .Seconds(dhms.at(3));
            }
            catch (Clock::OutOfRange) {
                throw OutOfRange{};
            }
        }
        catch (const NoSuchTimer&) {
            try {
                Clock clk{ name.c_str(), dhms.at(0), dhms.at(1),
                                         dhms.at(2), dhms.at(3) };
                allTimers.emplace_back(std::move(clk), State::Ready);
            }
            catch (Clock::OutOfRange&) {
                throw OutOfRange{};
            }
        }
    }

    void Start(const std::string& name) {
        auto& ccRef{ *CC_IteratorFor(name) };
        auto& stateRef{ std::get<State>(ccRef) };
        switch (stateRef) {
        case State::Ready:
            stateRef = State::Countdown;
            return;
        }
    }

    void Pause(const std::string& name) {
        auto& ccRef{ *CC_IteratorFor(name) };
        auto& stateRef{ std::get<State>(ccRef) };
        switch (stateRef) {
        case State::Countdown:
            stateRef = State::Paused;
            return;
        }
    }

    void Resume(const std::string& name) {
        auto& ccRef{ *CC_IteratorFor(name) };
        auto& stateRef{ std::get<State>(ccRef) };
        switch (stateRef) {
        case State::Paused:
            stateRef = State::Countdown;
            return;
        }
    }

    void Delete(const std::string& name) {
        auto ccIt{ CC_IteratorFor(name) };
        allTimers.erase(ccIt);
    }

    void TickAll() {
        for (auto& e : allTimers) {
             auto& clockRef{ std::get<Clock>(e) };
             auto& stateRef{ std::get<State>(e) };
             switch (stateRef) {
             case State::Countdown:
                 clockRef.TickDown();
                 if (clockRef.IsFloor()) {
                     stateRef = State::Expired;
                 }
                 return;
             case State::Expired:
                 if (!clockRef.IsCeiling()) {
                     clockRef.TickUp();
                 }
                 return;
             }
        }
    }

    void ShowAll(std::ostream& dbg_log) {
        for (const auto& e : allTimers) {
            dbg_log << '[' << char(std::get<State>(e)) << ']'
                    << ' ' << std::get<Clock>(e) << std::endl;
        }
    }

    UI::MenuControl menuControl = {
       { //-------------------------------------------------------------
           "create <timer> <days> <hours> <minutes> <seconds>",
           R"((?:create|c) ([a-z]+) (\d+) (\d+) (\d+) (\d+))",
           [](auto m) {
               Create(m[1].str(),
                      DHMS{ Clock::value_type(std::stoi(m[2].str())),
                            Clock::value_type(std::stoi(m[3].str())),
                            Clock::value_type(std::stoi(m[4].str())),
                            Clock::value_type(std::stoi(m[5].str()))
                      });
           }
       },
       { //-------------------------------------------------------------
           "start <timer>",
           R"((?:start|s) ([a-z]+))",
           [](auto m) { Start(m[1].str()); }
       },
       { //-------------------------------------------------------------
           "pause <timer>",
           R"((?:pause|p) ([a-z]+))",
           [](auto m) { Pause(m[1].str()); }
       },
       { //-------------------------------------------------------------
           "resume <timer>",
           R"((?:resume|r) ([a-z]+))",
           [](auto m) { Resume(m[1].str()); }
       },
       { //-------------------------------------------------------------
           "delete <timer>",
           R"((?:delete|d) ([a-z]+))",
           [](auto m) { Delete(m[1].str()); }
       },
       { //-------------------------------------------------------------
           "<steps>",
           R"(\d+)",
           [](auto m) {
               auto steps { std::stoi(m[0].str()) };
               while (steps-- > 0) {
                   TickAll();
               }
           }
       },
       { //-------------------------------------------------------------
           "quit",
           R"(quit|q)",
          [](auto) { throw 0; }
       },
    };

} //namespace KitchenTimer/////////////////////////////////////////////////////


void appl() {
    UI::main_loop(std::cin, std::cout, std::clog,
                  std::bind(KitchenTimer::ShowAll, std::ref(std::clog)),
                  KitchenTimer::menuControl);
}

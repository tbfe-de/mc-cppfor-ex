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
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "Clock.h"

namespace UI { ////////////////////////////////////////////////////////////////

namespace Command {
    // type aliases
    using Params = std::smatch;
    using Result = std::tuple<bool, std::string>;
    using Func = std::function<Result(Params)>;
    using Exec = std::tuple<bool, Func>;
    struct Menu {
        // type aliases
        using Prelude = std::function<void()>;
        using Control = std::initializer_list<Menu>;
        using Postlude = std::function<void(const Params&)>;
        // data members
        std::string description;
        std::string syntax_regex;
        Func execute;
    };
}

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

void debug_match_args(const Command::Params& params, std::ostream& dbg_out) {
    dbg_out << "arguments matched: " << params.size() << std::endl;
    for (std::smatch::size_type n = 0; n < params.size(); ++n) {
        std::clog << "- [" << n << "]:\t"
                  << '>' << params[n].str() << '<' << std::endl;
    }
}

void main_loop(std::istream& in, std::ostream& out, std::ostream& dbg_out,
               const Command::Menu::Prelude prelude,
               const Command::Menu::Control& menu,
               const Command::Menu::Postlude postlude) {
    auto show_help = [&menu, &out] {
        out << "--- Available Commands:\n";
        for (const auto& e : menu) {
         // -------=======================--------------
            out << "  : " << e.description << std::endl;
         // -------=======================--------------
        }
    };
    
    std::string cmd_line;
    Command::Func cmd_func;
    Command::Params cmd_params;
    auto parse_line = [&menu, &cmd_line, &cmd_func, &cmd_params, &dbg_out] {
        for (const auto& e : menu) {
            std::regex re{e.syntax_regex};
         // ----==========================================---
            if (std::regex_match(cmd_line, cmd_params, re)) {
         // ----==========================================---
                cmd_func = e.execute;
                dbg_out << "OK: " << e.description << std::endl;
                return true;
            }
        }
        return false;
    };

    auto execute_cmd = [&cmd_func, &cmd_params, &out] {
        if (cmd_func) {
         // -------------====================---
            auto result{ cmd_func(cmd_params) };
         // -------------====================---
            const auto success{ std::get<bool>(result) };
            const auto& message{ std::get<std::string>(result) };
            const auto label{ success ? ":::" : "***"};
            out << label << ' ' << message << std::endl; }
        else {
            out << "!!! not yet implemented !!!" << std::endl;
        }
    };

    show_help();
    while ((prelude ? prelude : []{})(),
           out << "==> " << std::flush,
           std::getline(in, cmd_line)) {
        normalize_ws(cmd_line);
        if (parse_line()) {
            execute_cmd();
            if (postlude) {
                postlude(cmd_params);
            }
        }
        else {
            show_help();
        }
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
using DHMS = std::array<int, 4>;

TimerCollection allTimers;

auto CC_IteratorFor(const std::string& name, bool create = false) {
    auto name_cmp {
        [name_c_str = name.c_str()](const auto& e) {
            const auto& clockRef{ std::get<Clock>(e) };
            return (std::strcmp(clockRef.GetName(), name_c_str) == 0);
        }
    };
    auto result {
        std::find_if(allTimers.begin(), allTimers.end(), name_cmp)
    };
    if ((result == allTimers.end()) && create) {
        ControlledClock cc{ name.c_str(), State::Ready };
        result = allTimers.insert(result, std::move(cc)); 
    }
    return result;
}

auto Create(const std::string& name, const DHMS& dhms) {
    std::ostringstream os{};
    const auto ccIt{ CC_IteratorFor(name, true) };
    auto& clockRef{ std::get<Clock>(*ccIt) };
    auto& stateRef{ std::get<State>(*ccIt) };
    if (stateRef != State::Ready) {
        os << "timer(" << name << ") currently in use";
        return UI::Command::Result{ false, os.str() };
    }
    auto range_limited_set{
        [&clockRef, &os](const char* field, int limit, auto value, auto to) {
            if (value < limit) {
                (clockRef.*to)(value);
            } else {
                if (!os.str().empty()) {
                   os << '\n';
                }
                os << "value(" << value << ")"
                      " exceeds limit(" << limit << ")"
                      " for " << field;
            }
        }
    };

    range_limited_set("days", 255, dhms.at(0), &Clock::Days);
    range_limited_set("hours", 24, dhms.at(1), &Clock::Hours);
    range_limited_set("minutes", 60, dhms.at(2), &Clock::Minutes);
    range_limited_set("seconds", 60, dhms.at(3), &Clock::Seconds);

    if (!os.str().empty()) {
        allTimers.erase(ccIt);
        return UI::Command::Result{ false, os.str() };
    }

    os << "timer '" << name << "' ready to be started";
    return UI::Command::Result{ true, os.str() };
}

auto Start(const std::string& name) {
    std::ostringstream os{};
    const auto ccIt{ CC_IteratorFor(name) };
    if (ccIt == allTimers.end()) {
        os << "timer '" << name << "' does not exist";
        return UI::Command::Result{ false, os.str() };
    }
    auto& stateRef{ std::get<State>(*ccIt) };
    switch (stateRef) {
    case State::Ready:
     // - - - - - ->>>>>>>>>>>>>>>>-
        stateRef = State::Countdown;
     // - - - - - ->>>>>>>>>>>>>>>>-
        os << "timer '" << name << "' counting down";
        return UI::Command::Result{ true, os.str() };
    default:
        os << "timer '" << name << "' already active";
        return UI::Command::Result{ false, os.str() };
    }
}

auto Pause(const std::string& name) {
    std::ostringstream os{};
    const auto ccIt{ CC_IteratorFor(name) };
    if (ccIt == allTimers.end()) {
        os << "timer '" << name << "' does not exist";
        return UI::Command::Result{ false, os.str() };
    }
    auto& stateRef{ std::get<State>(*ccIt) };
    switch (stateRef) {
    case State::Countdown:
     // - - - - - ->>>>>>>>>>>>>-
        stateRef = State::Paused;
     // - - - - - ->>>>>>>>>>>>>-
        os << "timer '" << name << "' pauses ...";
        return UI::Command::Result{ true, os.str() };
    default:
        os << "timer '" << name << "' not counting";
        return UI::Command::Result{ false, os.str() };
    }
}

auto Resume(const std::string& name) {
    std::ostringstream os{};
    const auto ccIt{ CC_IteratorFor(name) };
    if (ccIt == allTimers.end()) {
        os << "timer '" << name << "' doesn't exist";
        return UI::Command::Result{ false, os.str() };
    }
    auto& stateRef{ std::get<State>(*ccIt) };
    switch (stateRef) {
    case State::Paused:
        os << "timer '" << name << "' ... resumes";
     // - - - - - ->>>>>>>>>>>>>>>>-
        stateRef = State::Countdown;
     // - - - - - ->>>>>>>>>>>>>>>>-
        return UI::Command::Result{ true, os.str() };
    default:
        os << "timer '" << name << "' not paused";
        return UI::Command::Result{ false, os.str() };
    }
}

auto Delete(const std::string& name) {
    std::ostringstream os{};
    auto ccIt{ CC_IteratorFor(name) };
    if (ccIt == allTimers.end()) {
        os << "timer '" << name << "' doesn't exist";
        return UI::Command::Result{ false, os.str() };
    }
    allTimers.erase(ccIt);
    os << "timer '" << name << "' deleted";
    return UI::Command::Result{ true, os.str() };
}

auto TickAll(const std::string& steps) {
    auto advance_timer{
        [](auto& e) {
            auto& clockRef{ std::get<Clock>(e) };
            auto& stateRef{ std::get<State>(e) };
            switch (stateRef) {
            case State::Countdown:
             // ===================-
                clockRef.TickDown();
             // ===================-
                if (clockRef.IsFloor()) {
                 // - - - - - ->>>>>>>>>>>>>>-
                    stateRef = State::Expired;
                 // - - - - - ->>>>>>>>>>>>>>-
                }
                break;
            case State::Expired:
                if (!clockRef.IsCeiling()) {
                 // =================-
                    clockRef.TickUp();
                 // =================-
                }
                break;
            default:
               break;
            }
        }
    };

    for (auto count = std::stoi(steps); count > 0; --count) {
        for (auto& e : allTimers) {
         // ================-
            advance_timer(e);
         // ================-
        }
    }

    std::ostringstream os{};
    os << "advanced counters " << steps << " steps";
    return UI::Command::Result{ true, os.str() };
}

void ShowAll(std::ostream& dbg_log) {
    for (const auto& e : allTimers) {
        dbg_log << '[' << char(std::get<State>(e)) << ']'
                << ' ' << std::get<Clock>(e) << std::endl;
    }
}

UI::Command::Menu::Control menuControl = {
   { //-------------------------------------------------------------
       "create <timer> <days> <hours> <minutes> <seconds>",
       R"((?:create|c) ([a-z]+) (\d+) (\d+) (\d+) (\d+))",
       [](auto m) {
           return Create(m[1].str(),
                  DHMS{ std::stoi(m[2].str()),
                        std::stoi(m[3].str()),
                        std::stoi(m[4].str()),
                        std::stoi(m[5].str())
                  });
       }
   },
   { //-------------------------------------------------------------
       "start <timer>",
       R"((?:start|s) ([a-z]+))",
       [](auto m) { return Start(m[1].str()); }
   },
   { //-------------------------------------------------------------
       "pause <timer>",
       R"((?:pause|p) ([a-z]+))",
       [](auto m) { return Pause(m[1].str()); }
   },
   { //-------------------------------------------------------------
       "resume <timer>",
       R"((?:resume|r) ([a-z]+))",
       [](auto m) { return Resume(m[1].str()); }
   },
   { //-------------------------------------------------------------
       "delete <timer>",
       R"((?:delete|d) ([a-z]+))",
       [](auto m) { return Delete(m[1].str()); }
   },
   { //-------------------------------------------------------------
       "<steps>",
       R"(\d+)",
       [](auto m) { return TickAll(m[0].str()); }
   },
   { //-------------------------------------------------------------
       "quit",
       R"(quit|q)",
       [](auto) -> UI::Command::Result { throw 0; }
   },
};

} //namespace KitchenTimer/////////////////////////////////////////////////////


void appl() {
    UI::main_loop(std::cin, std::cout, std::clog,
                  std::bind(KitchenTimer::ShowAll, std::ref(std::clog)),
                  KitchenTimer::menuControl,
                  UI::Command::Menu::Postlude{});
}

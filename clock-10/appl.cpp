#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>

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
            const auto label{ success ? "OK:" : "???"};
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

#include "Clock.h"

namespace KitchenTimer {

using DHMS = std::array<Clock::value_type, 4>;

auto Create(const UI::Command::Params& args) {
    std::ostringstream os{};
    DHMS dhms;
    auto range_limited_set{
        [&os](const char* field, int limit, const auto& from, auto& to) {
            const auto value{ std::stoul(from) };
            if (value < limit) {
                to = value;
            } else {
                if (!os.str().empty()) {
                   os << '\n';
                }
                os << "*** value(" << value << ")"
                      " exceeds limit(" << limit << ")"
                      " for " << field;
            }
        }
    };

    range_limited_set("days",   255, args[2].str(), dhms.at(0));
    range_limited_set("hours",   24, args[3].str(), dhms.at(1));
    range_limited_set("minutes", 60, args[4].str(), dhms.at(2));
    range_limited_set("seconds", 60, args[5].str(), dhms.at(3));

    if (!os.str().empty()) {
        return UI::Command::Result{ false, os.str() };
    }
    //
    // TBD: add timer to global timer collection
    //
    return UI::Command::Result{ true, {} };
}

UI::Command::Menu::Control commandMenu = {
   { //-----------------------------------------------------------
       "create <timer> <days> <hours> <minutes> <seconds>",
       R"((?:create|c) ([a-z]+) (\d+) (\d+) (\d+) (\d+))",
       KitchenTimer::Create
   },
   { //-----------------------------------------------------------
       "start <timer>",
       R"((?:start|s) ([a-z]+))",
   },
   { //-----------------------------------------------------------
       "pause <timer>",
       R"((?:pause|p) ([a-z]+))",
   },
   { //-----------------------------------------------------------
       "resume <timer>",
       R"((?:resume|r) ([a-z]+))",
   },
   { //-----------------------------------------------------------
       "delete <timer>",
       R"((?:delete|d) ([a-z]+))",
   },
   { //-----------------------------------------------------------
       "quit",
       R"(quit|q)",
       [](auto) -> UI::Command::Result { throw 0; }
   },
};

} //namespace KitchenTimer/////////////////////////////////////////////////////

void appl() {
    using namespace std::placeholders;
    UI::main_loop(std::cin, std::cout, std::clog,
                  UI::Command::Menu::Prelude{},
                  KitchenTimer::commandMenu,
                  std::bind(UI::debug_match_args, _1, std::ref(std::clog))
                 );
}

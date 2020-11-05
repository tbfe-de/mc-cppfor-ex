#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <tuple>

namespace UI { ////////////////////////////////////////////////////////////////

using CommandParams = std::smatch;
using CommandResult = std::tuple<bool, std::string>;
using CommandFunc = std::function<CommandResult(CommandParams)>;
using CommandExec = std::tuple<bool, CommandFunc>;

struct CommandMenu {
    std::string description;
    std::string syntax_regex;
    CommandFunc execute;
};

using MenuControl = std::initializer_list<CommandMenu>;

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

void debug_match_args(const std::smatch& m) {
    std::clog << "arguments matched: " << m.size() << std::endl;
    for (std::smatch::size_type n = 1; n < m.size(); ++n) {
	std::clog << "- [" << n << "]:\t" << m[n].str() << std::endl;
    }
}

void main_loop(std::istream& in, std::ostream& out, std::ostream& dbg_out,
               const MenuControl& menu) {
    auto show_help = [&menu, &out] {
        out << "--- Available Commands:\n";
        for (const auto& e : menu) {
	    out << "  : " << e.description << std::endl;
        }
    };
    
    std::string cmd_line;
    CommandFunc cmd_func;
    CommandParams cmd_params;
    auto parse_line = [&menu, &cmd_line, &cmd_func, &cmd_params, &out, &dbg_out] {
        for (const auto& e : menu) {
	    std::regex re{e.syntax_regex};
	    if (std::regex_match(cmd_line, cmd_params, re)) {
                cmd_func = e.execute;
	        dbg_out << "OK: " << e.description << std::endl;
                return true;
            }
        }
        return false;
    };

    show_help();
    while (out << "==> " << std::flush,
        std::getline(in, cmd_line)) {
        normalize_ws(cmd_line);
        if (parse_line()) {
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
        }
        else {
            show_help();
        }
    }
}

} //namespace UI///////////////////////////////////////////////////////////////

void appl() {
    UI::MenuControl m = {
       { //-----------------------------------------------------------
           "create <timer> ?days? ?hours? ?minutes? ?seconds?",
           R"((?:create|c) ([a-z]+) (\d+) (\d+) (\d+) (\d+))",
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
          [](auto) -> UI::CommandResult { throw 0; }
       },
    };

    UI::main_loop(std::cin, std::cout, std::clog, m);
}

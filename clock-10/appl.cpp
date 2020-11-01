#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>

namespace UI { ////////////////////////////////////////////////////////////////

struct CommandMenu {
    std::string description;
    std::string syntax_regex;
    std::function<void(const std::smatch&)> execute;
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

void main_loop(std::istream& in, std::ostream& out, const MenuControl& menu) {
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
	    out << "OK: " << e.description << std::endl;
            if (e.execute) {
                e.execute(m);
            }
            else {
                out << "!!!! not yet implemented" << std::endl;
            }
            return true;
        }
        return false;
    };

    show_help();
    std::string cmd;
    while (out << "==> " << std::flush,
       std::getline(in, cmd)) {
        normalize_ws(cmd);
        if (!parse_line(cmd)) show_help();
    }
}

} //namespace UI///////////////////////////////////////////////////////////////

void appl() {
    UI::MenuControl m = {
       { //-----------------------------------------------------------
           "create <timer> ?days? ?hours? ?minutes? ?seconds?",
           R"((:??create|c) ([a-z]+) (\d+) (\d+) (\d+) (\d+))",
       },
       { //-----------------------------------------------------------
           "start <timer>",
           R"((:??start|s) ([a-z]+) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "pause <timer>",
           R"((:??pause|p) ([a-z]+) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "resume <timer>",
           R"((:??resume|r) ([a-z]+) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "delete <timer>",
           R"((:??delete|d) ([a-z]+) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "timers",
           R"((:??timers|t))",
       },
       { //-----------------------------------------------------------
           "quit",
           R"(quit|q)",
          [](auto) { throw 0; }
       },
    };

    UI::main_loop(std::cin, std::cout, m);
}

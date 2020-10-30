#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>


struct CommandMenu {
    std::string description;
    std::string syntax_regex;
    std::function<void()> execute;
};

using MenuControl = std::initializer_list<CommandMenu>;

void main_command_loop(std::istream& in, std::ostream& out, const MenuControl& menu) {
    auto show_help = [&] {
        out << "--- Available Commands:\n";
        for (const auto& e : menu) {
	    out << "==> " << e.description << std::endl;
        }
    };
    auto parse_line = [&](const std::string cmd) {
        for (const auto& e : menu) {
	    std::regex re{e.syntax_regex};
	    std::smatch m;
	    if (!std::regex_match(cmd, m, re)) continue;
	    out << "*OK: " << e.description << std::endl;
            if (e.execute) {
                e.execute();
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
	   if (!parse_line(cmd)) show_help();
    }
}

void appl() {
    MenuControl m = {
       { //-----------------------------------------------------------
           "create <timer> ?days? ?hours? ?minutes? ?seconds?",
           R"((:??create|c) ([a-z]+) (\d+) (\d+) (\d+) (\d+))",
       },
       { //-----------------------------------------------------------
           "start <timer>",
           R"((:??start|s) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "pause <timer>",
           R"((:??pause|p) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "remove <timer>",
           R"((:??remove|r) ([a-z]+))",
       },
       { //-----------------------------------------------------------
           "quit",
           R"(quit|q)",
          [] { throw 0; }
       },
    };

    main_command_loop(std::cin, std::cout, m);
}

#include <array>
#include <iostream>

struct NotYetImplemented : public std::runtime_error {
	NotYetImplemented() : std::runtime_error("not yet implemented") {}
};

struct NonStandardException {};

void foo() {
    std::array<int, 2> data;
    data[1] = 1;		// index NOT checked (but is OK) ...
//  data[2] = 2;		// ... same but out of bounds (=> UB)
    data.at(1) = 3;		// index CHECKED (and is OK) ...
    data.at(2) = 4;		// ... same but of bounds (=> throws)
}

void appl() {
// 
// (for demonstration compile with of the lines below uncommented)
//
//  throw NonStandardException{};
    throw NotYetImplemented{};
//  throw std::runtime_error{"code needs still to be written"};
//  throw "HELP! (call police)";
//  throw 911;
//  foo();
}



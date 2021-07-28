#include "ClockWork.h"

ClockWork::ID_Generator ClockWork::rand_id{};

void ClockWork::tick() {
    for (const auto &e : subscribers_) {
        if (e.second) {
	        e.second(); 
        }
    }
}

void ClockWork::run(unsigned long long) {
    throw "ClockWork::run not yet implemented";
}

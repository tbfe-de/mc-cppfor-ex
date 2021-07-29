#include "ClockWork.h"

#include <chrono>

ClockWork::ID_Generator ClockWork::rand_id{};

void ClockWork::tick() {
    for (const auto &e : subscribers) {
        if (e.second) {
	        e.second(); 
        }
    }
}

void ClockWork::run(ULL tck) {
    remaining_ticks = tck;
    if (!runner.joinable() && (tck > 0))  {
        runner = std::thread{[this] {
            auto rt = remaining_ticks.load();
            while (rt > 0) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1s);
                tick();
                if (remaining_ticks.compare_exchange_strong(rt, rt-1)) {
                    --rt;
                }
            }
            runner.detach();
        }};
    }
}

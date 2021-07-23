#include "ClockWork.h"

ClockWork::ID_Generator ClockWork::rand_id;

void ClockWork::tick() {
    for (CallBackRegistry::const_iterator it = subscribers_.begin();
                                          it != subscribers_.end();
                                        ++it) {
         if (it->second) {
	        it->second(); 
        }
    }
}

void ClockWork::run(unsigned long long) {
    throw "ClockWork::run not yet implemented";
}

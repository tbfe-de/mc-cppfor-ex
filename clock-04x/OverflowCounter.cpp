#include "OverflowCounter.h"

#ifndef OC_SIMPLE_IMPLEMENTATION
void OverflowCounter::HasOverflowed(int amount) {
    next_counter_.Count(amount);
}
#endif

void OverflowCounter::HasOverflowed() {
    next_counter_.Count();
}

void OverflowCounter::HasResetted() {
    next_counter_.Reset();
}

#include "OverflowCounter.h"

#ifndef OC_SIMPLE_IMPLEMENTATION
void OverflowCounter::PostOverflowAction(int amount) {
    next_counter_.Count(amount);
}
#endif

void OverflowCounter::PostOverflowAction() {
    next_counter_.Count();
}

void OverflowCounter::PostResetAction() {
    next_counter_.Reset();
}

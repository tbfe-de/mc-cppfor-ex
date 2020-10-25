#include "OverflowCounter.h"

void OverflowCounter::HasOverflowed() {
    next_counter_.Count();
}

void OverflowCounter::HasResetted() {
    next_counter_.Reset();
}

#include "OverflowCounter.h"

void OverflowCounter::PostOverflowAction() {
    next_counter_.Count();
}

void OverflowCounter::PostResetAction() {
    next_counter_.Reset();
}

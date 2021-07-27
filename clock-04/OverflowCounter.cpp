#include "OverflowCounter.h"

void OverflowCounter::OverflowAction() {
    next_counter_.Count();
}

void OverflowCounter::ResetAction() {
    next_counter_.Reset();
}

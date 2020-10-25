#include "OverflowCounter.h"

void OverflowCounter::Count() {
    LimitCounter::Count();
    if (LimitCounter::GetValue() == 0) {
            next_counter_.Count();
    }
}

void OverflowCounter::Reset() {
    LimitCounter::Reset();
    next_counter_.Reset();
}

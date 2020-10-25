#include "OverflowCounter.h"

bool OverflowCounter::Count() {
    const auto overflowed = LimitCounter::Count();
    if (overflowed) {
            next_counter_.Count();
    }
    return overflowed;
}

void OverflowCounter::Reset() {
    LimitCounter::Reset();
    next_counter_.Reset();
}

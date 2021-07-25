#include "LimitCounter.h"

void LimitCounter::Count(int amount) {
    while (amount-- > 0) {
        Count();
    }
}

void LimitCounter::Count() {
    if (++value_ >= max_value_) {
        WillOverflow();
        value_ = 0;
        HasOverflowed();
    }
}

void LimitCounter::Reset() {
    WillReset();
    value_ = 0;
    HasResetted();
}
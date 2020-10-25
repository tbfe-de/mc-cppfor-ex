#include "LimitCounter.h"

void LimitCounter::Count(int amount) {
    while (amount-- > 0) {
        Count();
    }
}

void LimitCounter::Count() {
    if (++value_ >= max_value_) {
        value_ = 0;
        HasOverflowed();
    }
}

void LimitCounter::Reset() {
    value_ = 0;
    HasResetted();
}

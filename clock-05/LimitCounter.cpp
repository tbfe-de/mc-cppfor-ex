#include "LimitCounter.h"

void LimitCounter::Count(int amount) {
    while (amount-- > 0) {
        Count();
    }
}

void LimitCounter::Count() {
    if (++value_ >= max_value_) {
        PreOverflowAction();
        value_ = 0;
        PostOverflowAction();
    }
}

void LimitCounter::Reset() {
    PreResetAction();
    value_ = 0;
    PostResetAction();
}
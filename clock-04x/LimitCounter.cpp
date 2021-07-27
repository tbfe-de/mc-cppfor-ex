#include "LimitCounter.h"

#ifdef LC_SIMPLE_IMPLEMENTATION

void LimitCounter::CountMany(int amount) {
    while (amount-- > 0) {
        Count();
    }
}

void LimitCounter::PostOverflowAction(int) {
	/*empty*/
}

#else

void LimitCounter::CountMany(int amount) {
    if (amount > 0) {
        const auto new_value = value_ + amount;
    	value_ = new_value % max_value_;
        PostOverflowAction(new_value / max_value_);
    }
}

void LimitCounter::PostOverflowAction(int amount) {
    while (amount-- > 0) {
        PostOverflowAction();
    }
}

#endif

void LimitCounter::Count(int amount) {
    CountMany(amount);
}

void LimitCounter::Count() {
    if (++value_ >= max_value_) {
        value_ = 0;
        PostOverflowAction();
    }
}

void LimitCounter::Reset() {
    value_ = 0;
    PostResetAction();
}

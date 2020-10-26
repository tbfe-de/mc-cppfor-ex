#include "LimitCounter.h"

#ifdef LC_SIMPLE_IMPLEMENTATION

void LimitCounter::CountMany(int amount) {
    while (amount-- > 0) {
        Count();
    }
}

void LimitCounter::HasOverflowed(int) {
	/*empty*/
}

#else

void LimitCounter::CountMany(int amount) {
    if (amount > 0) {
        const auto new_value = value_ + amount;
    	value_ = new_value % max_value_;
        HasOverflowed(new_value / max_value_);
    }
}

void LimitCounter::HasOverflowed(int amount) {
    while (amount-- > 0) {
        HasOverflowed();
    }
}

#endif

void LimitCounter::Count(int amount) {
    CountMany(amount);
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

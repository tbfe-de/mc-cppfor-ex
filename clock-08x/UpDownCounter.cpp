#include "UpDownCounter.h"

bool UpDownCounter::SetValue(value_type value) {
    const auto old_value = value_;
    value_ = value;
    try {
        check_in_range_value();
        return true;
    }
    catch (const OutOfRangeValue&) {
        value_ = old_value;
        return false;
    }
}

void UpDownCounter::UpCount() {
    if (++value_ == max_value_) {
        value_ = 0;
        if (next_counter_) {
            next_counter_->UpCount();
        }
    }
}

void UpDownCounter::DownCount() {
    if (value_ == 0) {
	value_ = max_value_;
        if (next_counter_) {
            next_counter_->DownCount();
	}
    }
    --value_;
}

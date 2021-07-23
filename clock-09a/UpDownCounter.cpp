#include "UpDownCounter.h"

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

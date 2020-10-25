#include "Counter.h"

void Counter::Count(int amount) {
    while (amount-- > 0) {
        if (++value_ >= max_value_) {
            value_ = 0;
            if (next_counter_) {
                next_counter_->Count(1);
            }
        }
    }
}

void Counter::Reset() {
    value_ = 0;
    if (next_counter_) {
	next_counter_->Reset();
    }
}

#include "Counter.h"

void Counter::Count() {
    if (++value_ >= max_value_) {
        value_ = 0;
        if (next_counter_) {
            next_counter_->Count(1);
        }
    }
}

#ifdef SIMPLE_IMPLEMENTATION

void Counter::Count(int steps) {
    while (steps-- > 0) {
	    Counter::Count();
    }
}

#else

#include <cassert>

void Counter::Count(int steps) {
    assert(max_value_ > 0);
    if (steps <= 0) return;
    const auto tmp = value_ + steps;
    value_ = tmp % max_value_;
    const auto next_steps = tmp / max_value_;
    if (next_steps && next_counter_) {
        next_counter_->Count(next_steps);
    }
}

#endif

void Counter::Reset() {
    value_ = 0;
    if (next_counter_) {
	next_counter_->Reset();
    }
}

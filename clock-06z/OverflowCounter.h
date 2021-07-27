#ifndef OVERFLOW_COUNTER_H
#define OVERFLOW_COUNTER_H

#include "LimitCounter.h"

class OverflowCounter : public CounterBase<OverflowCounter> {
    ICounter& next_counter_;
public:
    OverflowCounter(int max_value, ICounter& next_counter)
        : CounterBase<OverflowCounter>{max_value}
        , next_counter_{next_counter}
    {}
    void PostOverflowAction() { next_counter_.Count(); }
    void PostResetAction() { next_counter_.Reset(); }
};


#endif
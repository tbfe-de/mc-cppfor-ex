#ifndef OVERFLOW_COUNTER_H
#define OVERFLOW_COUNTER_H

#include "LimitCounter.h"

class OverflowCounter_Details : protected LimitCounter_Details {
    ICounter& next_counter_;
protected:
    OverflowCounter_Details(ICounter& next_counter)
        : LimitCounter_Details()
        , next_counter_(next_counter)
    {}
    void PostOverflowAction() { next_counter_.Count(); }
    void PostResetAction() { next_counter_.Reset(); }
};

typedef CounterBase<OverflowCounter_Details> OverflowCounter;

#endif
#ifndef OVERFLOW_COUNTER_H
#define OVERFLOW_COUNTER_H

#include "LimitCounter.h"

class OverflowCounter : public LimitCounter {
    LimitCounter& next_counter_;
public:
    OverflowCounter(const OverflowCounter&); // will NOT be implemented
    OverflowCounter& operator=(const OverflowCounter&); // will NOT be implemented
    OverflowCounter(int max_value, LimitCounter& next_counter)
        : LimitCounter(max_value)
        , next_counter_(next_counter)
    {}
    virtual void PostOverflowAction();
    virtual void PostResetAction();
};

#endif

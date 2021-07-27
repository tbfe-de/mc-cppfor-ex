#ifndef OVERFLOW_COUNTER_H
#define OVERFLOW_COUNTER_H

#include "LimitCounter.h"

class OverflowCounter : public LimitCounter {
    ICounter& next_counter_;
public:
    OverflowCounter(int max_value, ICounter& next_counter)
        : LimitCounter{max_value}
        , next_counter_{next_counter}
    {}
    virtual void PostOverflowAction() override;
    virtual void PostResetAction() override;
};

#endif

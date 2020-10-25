#ifndef OVERFLOW_COUNTER_H
#define OVERFLOW_COUNTER_H

#include "LimitCounter.h"

class OverflowCounter : public LimitCounter {
    LimitCounter& next_counter_;
public:
    OverflowCounter(const OverflowCounter&) =delete;
    OverflowCounter& operator=(const OverflowCounter&) =delete;
    OverflowCounter(OverflowCounter&&) =delete;
    OverflowCounter& operator=(OverflowCounter&&) =delete;
    OverflowCounter(int max_value, LimitCounter& next_counter)
        : LimitCounter{max_value}
        , next_counter_{next_counter}
    {}
    
    using LimitCounter::Count;
    virtual void Count() override;
    virtual void Reset() override;
};


#endif

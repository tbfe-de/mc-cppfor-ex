#ifndef COUNTER_H
#define COUNTER_H

#include "ICounter.h"

class LimitCounter : public ICounter {
private:
    int value_;
    const int max_value_;
    virtual void PreOverflowAction() {}
    virtual void PreResetAction() {}
    virtual void PostOverflowAction() {}
    virtual void PostResetAction() {}
public:
    LimitCounter(int max_value)
        : value_(0)
        , max_value_(max_value)
    {}
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count(int amount);
    virtual void Count();
    virtual void Reset();
};

#endif
#ifndef COUNTER_H
#define COUNTER_H

#include "ICounter.h"

class LimitCounter : virtual public ICounter {
private:
    int value_{};
    const int max_value_{};
    virtual void WillOverflow() {}
    virtual void WillReset() {}
    virtual void HasOverflowed() {}
    virtual void HasResetted() {}
public:
    LimitCounter() =delete;
    LimitCounter(int max_value)
        : value_{0}
        , max_value_{max_value}
    {}
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count(int amount);
    virtual void Count() override final;
    virtual void Reset() override final;
};

#endif

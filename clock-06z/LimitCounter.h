#ifndef COUNTER_H
#define COUNTER_H

#include <utility>

#include "ICounter.h"

template<typename Details>
class CounterBase : public ICounter {
private:
    int value_{};
    const int max_value_{};
public:
    CounterBase(int max_value)
        : value_{0}
        , max_value_{max_value}
    {} 
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count(int amount);
    virtual void Count() override final;
    virtual void Reset() override final;
    void WillOverflow() {}
    void WillReset() {}
    void HasOverflowed() {}
    void HasResetted() {}
};

template<typename Details>
void CounterBase<Details>::Count(int amount) {
    while (amount-- > 0) {
        Count();
    }
}

template<typename Details>
void CounterBase<Details>::Count() {
    if (++value_ >= max_value_) {
        static_cast<Details*>(this)->WillOverflow();
        value_ = 0;
        static_cast<Details*>(this)->HasOverflowed();
    }
}

template<typename Details>
void CounterBase<Details>::Reset() {
    static_cast<Details*>(this)->WillReset();
    value_ = 0;
    static_cast<Details*>(this)->HasResetted();
}

class LimitCounter_Details : public CounterBase<LimitCounter_Details> {
	/*empty*/
};

using LimitCounter = CounterBase<LimitCounter_Details>;

#endif

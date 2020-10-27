#ifndef COUNTER_H
#define COUNTER_H

#include <utility>

#include "ICounter.h"

template<typename Details>
class CounterBase : public ICounter, private Details {
private:
    int value_{};
    const int max_value_{};
    using Details::WillOverflow;
    using Details::WillReset;
    using Details::HasOverflowed;
    using Details::HasResetted;
public:
    CounterBase(int max_value)
        : value_{0}
        , max_value_{max_value}
    {}
    template<typename T>
    CounterBase(int max_value, T&& details_arg)
        : Details{std::forward<T>(details_arg)}
        , value_{0}
        , max_value_{max_value}
    {} 
    template<typename T1, typename T2>
    CounterBase(int max_value, T1&& details_arg1, T2&& details_arg2)
        : Details{std::forward<T1>(details_arg1), std::forward<T2>(details_arg2)}
        , value_{0}
        , max_value_{max_value}
    {} 
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count(int amount);
    virtual void Count() override final;
    virtual void Reset() override final;
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
        WillOverflow();
        value_ = 0;
        HasOverflowed();
    }
}

template<typename Details>
void CounterBase<Details>::Reset() {
    WillReset();
    value_ = 0;
    HasResetted();
}

class LimitCounter_Details {
public:
    void WillOverflow() {}
    void WillReset() {}
    void HasOverflowed() {}
    void HasResetted() {}
};

using LimitCounter = CounterBase<LimitCounter_Details>;

#endif

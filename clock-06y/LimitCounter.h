#ifndef COUNTER_H
#define COUNTER_H

#include <utility>

#include "ICounter.h"

template<typename Details>
class CounterBase : public ICounter, private Details {
private:
    int value_{};
    const int max_value_{};
    using Details::PreOverflowAction;
    using Details::PreResetAction;
    using Details::PostOverflowAction;
    using Details::PostResetAction;
public:
    template<typename... Ts>
    CounterBase(int max_value, Ts&&... details_arg)
        : Details{std::forward<Ts>(details_arg)...}
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
        PreOverflowAction();
        value_ = 0;
        PostOverflowAction();
    }
}

template<typename Details>
void CounterBase<Details>::Reset() {
    PreResetAction();
    value_ = 0;
    PostResetAction();
}

class LimitCounter_Details {
protected:
    void PreOverflowAction() {}
    void PreResetAction() {}
    void PostOverflowAction() {}
    void PostResetAction() {}
};

using LimitCounter = CounterBase<LimitCounter_Details>;

#endif

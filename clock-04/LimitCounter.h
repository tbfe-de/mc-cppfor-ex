#ifndef COUNTER_H
#define COUNTER_H

#include <limits>

class LimitCounter {
private:
    int value_{};
    const int max_value_{};
    virtual void HasOverflowed() {}
    virtual void HasResetted() {}
public:
    LimitCounter(int max_value = std::numeric_limits<int>::max())
        : value_{0}
        , max_value_{max_value}
    {}
    auto SetValue(int value) { value_ = value; }
    auto GetValue() const { return value_; }
    void Count(int amount);
    void Count();
    void Reset();
};

#endif

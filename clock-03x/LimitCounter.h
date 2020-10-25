#ifndef LIMIT_COUNTER_H
#define LIMIT_COUNTER_H

#include <limits>

class LimitCounter {
private:
    int value_{};
    const int max_value_{};
public:
    LimitCounter(int max_value = std::numeric_limits<int>::max())
        : value_{0}
        , max_value_{max_value}
    {}
    auto SetValue(int value) { value_ = value; }
    auto GetValue() const { return value_; }
    void Count(int amount);
    virtual void Count();
    virtual void Reset();
};

#endif

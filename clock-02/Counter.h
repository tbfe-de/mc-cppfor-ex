#ifndef COUNTER_H
#define COUNTER_H

#include <limits>

class Counter {
private:
    int value_{0};
    const int max_value_{ std::numeric_limits<int>::max() };
    Counter* next_counter_{};
public:
    Counter(const Counter&) =delete;
    Counter& operator=(const Counter&) =delete;
    Counter(int max_value, Counter* next_counter = nullptr)
        : max_value_{max_value}
        , next_counter_{next_counter}
    {}
    Counter(Counter* next_counter = nullptr)
        : next_counter_{next_counter}
    {}
    auto SetValue(int value) { value_ = value; }
    auto GetValue() const { return value_; }
    void Count(int amount = 1);
    void Reset();
};

#endif

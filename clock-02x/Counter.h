#ifndef COUNTER_H
#define COUNTER_H

#include <limits>

class Counter {
private:
    int value_{};
    const int max_value_{};
    Counter* next_counter_{};
public:
    Counter(Counter* next_counter = nullptr)
	: max_value_(std::numeric_limits<int>::max())
	, next_counter_{next_counter}
    {}
    Counter(const Counter&) =delete;
    Counter& operator=(const Counter&) =delete;
    Counter(Counter&&) =delete;
    Counter& operator=(Counter&&) =delete;
    Counter(int max_value, Counter* next_counter = nullptr)
        : max_value_{max_value}
        , next_counter_{next_counter}
    {}
    auto SetValue(int value) { value_ = value; }
    auto GetValue() const { return value_; }
    auto GetLimit() const { return max_value_; }
    void Count(int amount = 1);
    void Reset();
};

#endif

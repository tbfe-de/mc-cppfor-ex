#ifndef COUNTER_H
#define COUNTER_H

#include <stddef.h> // for NULL

class Counter {
private:
    int value_;
    const int max_value_;
    Counter* next_counter_;
public:
    Counter(const Counter&); // will NOT be implemented
    Counter& operator=(const Counter&); // will NOT be implemented
    Counter(int max_value, Counter* next_counter = NULL)
        : value_(0)
        , max_value_(max_value)
        , next_counter_(next_counter)
    {}
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count(int amount = 1);
    void Reset();
};

#endif

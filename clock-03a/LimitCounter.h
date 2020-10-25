#ifndef LIMIT_COUNTER_H
#define LIMIT_COUNTER_H

#include <cstddef> // for NULL
#include <limits>

class LimitCounter {
private:
    int value_;
    const int max_value_;
public:
    LimitCounter(int max_value = std::numeric_limits<int>::max())
        : value_(0)
        , max_value_(max_value)
    {}
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count(int amount);
    virtual bool Count();
    virtual void Reset();
};

#endif

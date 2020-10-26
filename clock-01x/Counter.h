#ifndef COUNTER_H
#define COUNTER_H

class Counter {
private:
    int value_{};
    const int max_value_{};
    Counter* next_counter_{};
public:
    Counter(const Counter&) =delete;
    Counter& operator=(const Counter&) =delete;
    Counter(int max_value, Counter* next_counter = nullptr)
        : value_{0}
        , max_value_{max_value}
        , next_counter_{next_counter}
    {}
    void SetValue(int value) { value_ = value; }
    int GetValue() const { return value_; }
    void Count();
    void Count(int amount);
    void Reset();
};

#endif

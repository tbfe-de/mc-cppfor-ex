#ifndef UP_DOWN_COUNTER_H
#define UP_DOWN_COUNTER_H

#include <type_traits>

template<typename T>
class UpDownCounter {
public:
    using value_type = T;
    static_assert(std::is_integral<value_type>::value
               && std::is_unsigned<value_type>::value,
                  "designed to work with unsigned integral types only");
private:
    value_type value_{};
    const value_type max_value_{};
    UpDownCounter* next_counter_{};
public:
    UpDownCounter() =default;
    UpDownCounter(const UpDownCounter&) =delete;
    UpDownCounter(UpDownCounter&&) =delete;
    UpDownCounter& operator=(const UpDownCounter&) =delete;
    UpDownCounter& operator=(UpDownCounter&&) =delete;

    UpDownCounter(value_type value, value_type max_value, UpDownCounter* next_counter)
        : value_{value}
        , max_value_{max_value}
        , next_counter_{next_counter}
    {}
    UpDownCounter(value_type max_value, UpDownCounter* next_counter)
        : UpDownCounter(0, max_value, next_counter)
    {} 
    UpDownCounter(value_type max_value)
        : UpDownCounter(0, max_value, nullptr)
    {} 
    UpDownCounter(UpDownCounter* next_counter_)
        : UpDownCounter(0, 0, nullptr)
    {} 

    void SetValue(value_type value) { value_ = value; }
    int GetValue() const { return value_; }
    int GetLimit() const { return max_value_; }
    void UpCount();
    void DownCount();
};

template<typename T>
void UpDownCounter<T>::UpCount() {
    if (++value_ == max_value_) {
        value_ = 0;
        if (next_counter_) {
            next_counter_->UpCount();
        }
    }
}

template<typename T>
void UpDownCounter<T>::DownCount() {
    if (value_ == 0) {
        value_ = max_value_;
        if (next_counter_) {
                next_counter_->DownCount();
        }
    }
    --value_;
}

#endif

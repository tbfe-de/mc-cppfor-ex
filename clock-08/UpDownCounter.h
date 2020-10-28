#ifndef UP_DOWN_COUNTER_H
#define UP_DOWN_COUNTER_H

#include <cstdint>
#include <type_traits>

class UpDownCounter {
public:
    using value_type = std::uint8_t;
    static_assert(std::is_integral<value_type>::value
    	       && std::is_unsigned<value_type>::value,
                  "designed to work with unsigned integral types only");
private:
    value_type value_{};
    const value_type max_value_{};
    UpDownCounter *next_counter_{};
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
    UpDownCounter(value_type value, value_type max_value)
        : UpDownCounter(value, max_value, nullptr)
    {} 
    UpDownCounter(value_type max_value)
        : UpDownCounter(0, max_value, nullptr)
    {} 
    UpDownCounter(UpDownCounter* next_counter)
        : UpDownCounter(0, 0, next_counter)
    {} 

    void SetValue(value_type value) { value_ = value; }
    int GetValue() const { return value_; }
    int GetLimit() const { return max_value_; }
    void UpCount();
    void DownCount();
};

#endif

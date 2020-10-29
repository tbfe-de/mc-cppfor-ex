#ifndef UP_DOWN_COUNTER_H
#define UP_DOWN_COUNTER_H

#include <cstdint>
#include <stdexcept>
#include <type_traits>

class UpDownCounter {
public:
    using value_type = std::uint8_t;
    struct OutOfRangeValue : std::out_of_range {
        const value_type Value;
        const value_type MaxValue;
        OutOfRangeValue(value_type value, value_type max_value)
            : std::out_of_range{"UpDownCounter::OutOfRangeValue"}
            , Value{value}
            , MaxValue{max_value}
        {}
    };
    void check_in_range_value() {
        if ((max_value_ != 0) && (value_ >= max_value_)) {
            throw OutOfRangeValue{value_, max_value_};
        }
    }
    static_assert(std::is_integral<value_type>::value
               && std::is_unsigned<value_type>::value,
                  "designed to work with unsigned integral types only");
private:
    value_type value_{};
    const value_type max_value_{};
    UpDownCounter *next_counter_{};
public:
    UpDownCounter(const UpDownCounter&) =delete;
    UpDownCounter(UpDownCounter&&) =delete;
    UpDownCounter& operator=(const UpDownCounter&) =delete;
    UpDownCounter& operator=(UpDownCounter&&) =delete;

    // chaining counter with explicit maximum and explicit initial value
    //
    UpDownCounter(value_type value, value_type max_value, UpDownCounter* next_counter)
        : value_{value}
        , max_value_{max_value}
        , next_counter_{next_counter}
    {
        check_in_range_value();
    }

    // NON-chaining counter with NO maximum and initial value zero
    //
    UpDownCounter()
        : UpDownCounter(0, 0, nullptr)
    {}

    // chaining counter with explicit maximum and initial value zero
    //
    UpDownCounter(value_type max_value, UpDownCounter* next_counter)
        : UpDownCounter(0, max_value, next_counter)
    {}

    // NON-chaining counter with explicit maximum and explicit initial value
    //
    UpDownCounter(value_type value, value_type max_value)
        : UpDownCounter(value, max_value, nullptr)
    {} 

    // NON-chaining counter with explicit maximum and initial value zero
    //
    UpDownCounter(value_type max_value)
        : UpDownCounter(0, max_value, nullptr)
    {}

    // chaining counter with NO maximum and initial value zero
    //
    UpDownCounter(UpDownCounter* next_counter)
        : UpDownCounter(0, 0, next_counter)
    {} 

    void SetValue(value_type value) {
        value_ = value;
        check_in_range_value();
    }
    int GetValue() const { return value_; }
    int GetLimit() const { return max_value_; }
    void UpCount();
    void DownCount();
};

#endif

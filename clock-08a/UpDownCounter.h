#ifndef UP_DOWN_COUNTER_H
#define UP_DOWN_COUNTER_H

#include <cstdint>
#include <stdexcept>
#include <type_traits>

class UpDownCounter {
public:
    typedef std::uint8_t value_type ;
    // NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // designed to work with unsigned integral types only);
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    struct OutOfRangeValue : std::out_of_range {
        const value_type Value;
        const value_type MaxValue;
        OutOfRangeValue(value_type value, value_type max_value)
            : std::out_of_range("UpDownCounter::OutOfRangeValue")
            , Value(value)
            , MaxValue(max_value)
        {}
    };
    void check_in_range_value() {
        if ((max_value_ != 0) && (value_ >= max_value_)) {
            throw OutOfRangeValue(value_, max_value_);
        }
    }
private:
    value_type value_;
    const value_type max_value_;
    UpDownCounter *next_counter_;
                                   // COPYING WILL NOT BE IMPLEMENTED BUT ...
    UpDownCounter(const UpDownCounter&);            // avoid Compiler default
    UpDownCounter& operator=(const UpDownCounter&); // avoid Compiler default
public:

    // chaining counter with explicit maximum and explicit initial value
    //
    UpDownCounter(value_type value, value_type max_value, UpDownCounter* next_counter)
        : value_(value)
        , max_value_(max_value)
        , next_counter_(next_counter)
    {
        check_in_range_value();
    }

    // NON-chaining counter with NO maximum and initial value zero
    //
    UpDownCounter()
        : value_(0)
        , max_value_(0)
        , next_counter_(NULL)
    {
        check_in_range_value();
    }

    // chaining counter with explicit maximum and initial value zero
    //
    UpDownCounter(value_type max_value, UpDownCounter* next_counter)
        : value_(0)
        , max_value_(max_value)
        , next_counter_(next_counter)
    {
        check_in_range_value();
    }

    // NON-chaining counter with explicit maximum and explicit initial value
    //
    UpDownCounter(value_type value, value_type max_value)
        : value_(value)
        , max_value_(max_value)
        , next_counter_(NULL)
    {
        check_in_range_value();
    } 

    // NON-chaining counter with explicit maximum and initial value zero
    //
    UpDownCounter(value_type max_value)
        : value_(0)
        , max_value_(max_value)
        , next_counter_(NULL)
    {
        check_in_range_value();
    }

    // chaining counter with NO maximum and initial value zero
    //
    UpDownCounter(UpDownCounter* next_counter)
        : value_(0)
        , max_value_(0)
        , next_counter_(next_counter)
    {
        check_in_range_value();
    } 

    void SetValue(value_type value) {
        value_ = value;
        check_in_range_value();
    }
    value_type GetValue() const { return value_; }
    value_type GetLimit() const { return max_value_; }
    void UpCount();
    void DownCount();
};

#endif

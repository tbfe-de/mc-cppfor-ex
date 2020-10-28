#ifndef UP_DOWN_COUNTER_H
#define UP_DOWN_COUNTER_H

#include <cstddef> // for NULL

//#include <stdint>
//#include <type_traits>

class UpDownCounter {
public:
    typedef unsigned char value_type;

// NO alternative to this prior to C++11 !!
//  static_assert(std::is_integral<value_type>::value
//    	       && std::is_unsigned<value_type>::value,
//                "designed to work with unsigned integral types only");
// (maybe consider using STATIC_ASSERT from https://boost.org)

private:
    value_type value_;              // NO direct member initialization in C++98
    const value_type max_value_;    // (so CAREFULLY check ALL the constructors
    UpDownCounter *next_counter_;   // for complete member initialization lists)
public:
    UpDownCounter()
	: value_(0)
	, max_value_(0)
	, next_counter_(NULL)
    {}
    UpDownCounter(const UpDownCounter&); // will NOT be implemented
    UpDownCounter& operator=(const UpDownCounter&); // will NOT be implemented

    UpDownCounter(value_type value, value_type max_value, UpDownCounter* next_counter)
        : value_(value)
        , max_value_(max_value)
        , next_counter_(next_counter)
    {}
    UpDownCounter(value_type max_value, UpDownCounter* next_counter)
        : value_(0)
        , max_value_(max_value)
        , next_counter_(next_counter)
    {} 
    UpDownCounter(value_type value, value_type max_value)
        : value_(value)
        , max_value_(max_value)
        , next_counter_(NULL)
    {} 
    UpDownCounter(value_type max_value)
        : value_(0)
        , max_value_(max_value)
        , next_counter_(NULL)
    {} 
    UpDownCounter(UpDownCounter* next_counter)
        : value_(0)
        , max_value_(0)
        , next_counter_(next_counter)
    {} 

    void SetValue(value_type value) { value_ = value; }
    int GetValue() const { return value_; }
    int GetLimit() const { return max_value_; }
    void UpCount();
    void DownCount();
};

#endif

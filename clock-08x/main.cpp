#ifdef UNIT_TESTING

#include <iostream>
#include <sstream>

int SHOW_tests{0};
int SHOW_failed{0};
#define SHOW_(expect, ...)\
    do {\
        ++SHOW_tests;\
        std::ostringstream result;\
        result.copyfmt(std::cout);\
        result << (__VA_ARGS__);\
        if (result.str() != expect) {\
                std::cout << __FUNCTION__ <<  ':' << __LINE__ << '\t'\
                          << #__VA_ARGS__ << " --> " << result.str()\
                          << " != " << expect << std::endl;\
                ++SHOW_failed;\
        }\
    }\
    while (0)
#define SHOW_TEST_SUMMARY()\
    ((void)((SHOW_failed == 0)\
            ? std::cout << "*** " << SHOW_tests << " tests PASSED" << std::endl\
            : std::cout << "!!! " << SHOW_failed << " of "\
                                  << SHOW_tests << " tests FAILED" << std::endl))
    

#include "UpDownCounter.h"

void single_counter_constructors() {
    using ULL = unsigned long long;
    SHOW_("3", ULL{UpDownCounter{3, 5, nullptr}.GetValue()});
    SHOW_("5", ULL{UpDownCounter{3, 5, nullptr}.GetLimit()});
//  SHOW_("3", ULL{UpDownCounter{3, 5, NULL}.GetValue()});
//  SHOW_("5", ULL{UpDownCounter{3, 5, NULL}.GetLimit()});
    SHOW_("3", ULL{UpDownCounter{3, 5}.GetValue()});
    SHOW_("5", ULL{UpDownCounter{3, 5}.GetLimit()});
    SHOW_("0", ULL{UpDownCounter{5, nullptr}.GetValue()});
    SHOW_("5", ULL{UpDownCounter{5, nullptr}.GetLimit()});
//  SHOW_("0", ULL{UpDownCounter{5, NULL}.GetValue()});
//  SHOW_("5", ULL{UpDownCounter{5, NULL}.GetLimit()});
    SHOW_("0", ULL{UpDownCounter{5}.GetValue()});
    SHOW_("5", ULL{UpDownCounter{5}.GetLimit()});
    SHOW_("0", ULL{UpDownCounter{}.GetValue()});
    SHOW_("0", ULL{UpDownCounter{}.GetLimit()});
}

void chained_counter_constructors() {
    using ULL = unsigned long long;
    UpDownCounter hi{0, 3}; SHOW_("0", ULL{hi.GetValue()});
                            SHOW_("3", ULL{hi.GetLimit()});
    UpDownCounter lo{&hi};  SHOW_("0", ULL{lo.GetValue()});
                            SHOW_("0", ULL{lo.GetLimit()});
    SHOW_("2",    lo.DownCount(),      ULL{hi.GetValue()});
    SHOW_("0",    lo.UpCount(),        ULL{hi.GetValue()});

    // !!!
    // TBD: Test other combinations with chained counters
    // !!!
}

#include <limits>

void single_counter_setter() {
    using ULL = unsigned long long;
    UpDownCounter ud_0_max{};  SHOW_("0", ULL{ud_0_max.GetValue()});
                               SHOW_("0", ULL{ud_0_max.GetLimit()});
    SHOW_("123",  ud_0_max.SetValue(123), ULL{ud_0_max.GetValue()});
                               SHOW_("0", ULL{ud_0_max.GetLimit()});
}

#include <string>

void single_counter_max_wrap() {
    const auto max = std::numeric_limits<UpDownCounter::value_type>::max();
    auto max_init = [](auto m) {
	std::ostringstream os;
        os << m;
        return os.str();
    };
    const auto almost_max = max_init(max-1);
    const auto exactly_max = max_init(max+0);

    using ULL = unsigned long long;
    UpDownCounter ud_0_max{};               SHOW_("0", ULL{ud_0_max.GetValue()});
                                            SHOW_("0", ULL{ud_0_max.GetLimit()});
    SHOW_(almost_max,        ud_0_max.SetValue(max-1), ULL{ud_0_max.GetValue()});
    SHOW_(exactly_max,       ud_0_max.UpCount(),       ULL{ud_0_max.GetValue()});
    SHOW_("0",               ud_0_max.UpCount(),       ULL{ud_0_max.GetValue()});
    SHOW_("1",               ud_0_max.UpCount(),       ULL{ud_0_max.GetValue()});
    SHOW_("0",               ud_0_max.DownCount(),     ULL{ud_0_max.GetValue()});
    SHOW_(exactly_max,       ud_0_max.DownCount(),     ULL{ud_0_max.GetValue()});
    SHOW_(almost_max,        ud_0_max.DownCount(),     ULL{ud_0_max.GetValue()});
}

void single_counter_oflow() {
    using ULL = unsigned long long;
    UpDownCounter ud_3_5{3, 5}; SHOW_("3", ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
    SHOW_("4", ud_3_5.UpCount(),           ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
    SHOW_("0", ud_3_5.UpCount(),           ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
    SHOW_("1", ud_3_5.UpCount(),           ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
    SHOW_("0", ud_3_5.DownCount(),         ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
    SHOW_("4", ud_3_5.DownCount(),         ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
    SHOW_("3", ud_3_5.DownCount(),         ULL{ud_3_5.GetValue()});
                                SHOW_("5", ULL{ud_3_5.GetLimit()});
}

void chained_counters_oflow() {
    using ULL = unsigned long long;
    UpDownCounter hi{3};        SHOW_("0", ULL{hi.GetValue()});
                                SHOW_("3", ULL{hi.GetLimit()});
    UpDownCounter lo{4, &hi};   SHOW_("0", ULL{lo.GetValue()});
                                SHOW_("4", ULL{lo.GetLimit()});
    SHOW_("1", lo.UpCount(),               ULL{lo.GetValue()});
                                SHOW_("0", ULL{hi.GetValue()});
    SHOW_("2", lo.UpCount(),               ULL{lo.GetValue()});
                                SHOW_("0", ULL{hi.GetValue()});
    SHOW_("3", lo.UpCount(),               ULL{lo.GetValue()});
                                SHOW_("0", ULL{hi.GetValue()});
    SHOW_("0", lo.UpCount(),               ULL{lo.GetValue()});
                                SHOW_("1", ULL{hi.GetValue()});
    SHOW_("1", lo.UpCount(),               ULL{lo.GetValue()});
                                SHOW_("1", ULL{hi.GetValue()});
    SHOW_("0", lo.DownCount(),             ULL{lo.GetValue()});
                                SHOW_("1", ULL{hi.GetValue()});
    SHOW_("3", lo.DownCount(),             ULL{lo.GetValue()});
                                SHOW_("0", ULL{hi.GetValue()});
}

void out_of_range_set() {
    using ULL = unsigned long long;
    UpDownCounter xx{1, 3}; SHOW_("1",    ULL{xx.GetValue()});
                            SHOW_("3",    ULL{xx.GetLimit()});
                            SHOW_("true",     xx.SetValue(0));
                            SHOW_("0",    ULL{xx.GetValue()});
                            SHOW_("true",     xx.SetValue(1));
                            SHOW_("1",    ULL{xx.GetValue()});
                            SHOW_("true",     xx.SetValue(2));
                            SHOW_("2",    ULL{xx.GetValue()});
                            SHOW_("false",    xx.SetValue(3));
                            SHOW_("2",    ULL{xx.GetValue()});
                            SHOW_("false",    xx.SetValue(4));
                            SHOW_("2",    ULL{xx.GetValue()});
                            SHOW_("false",    xx.SetValue(9));
                            SHOW_("2",    ULL{xx.GetValue()});
}

void out_of_range_throw() {
    using ULL = unsigned long long;
    const auto max = std::numeric_limits<UpDownCounter::value_type>::max();
    try {
        UpDownCounter xx{3, 2};
        SHOW_("should have thrown", 0);
    }
    catch (UpDownCounter::OutOfRangeValue& ex) {
        SHOW_("3", ULL{ex.Value});
        SHOW_("2", ULL{ex.MaxValue});
    }
    try {
        UpDownCounter ok{max, UpDownCounter::value_type{0}};
    }
    catch (...) {
        SHOW_("should NOT have thrown", 0);
    }
    try {
        UpDownCounter{}.SetValue(max);
    }
    catch (...) {
        SHOW_("should NOT have thrown", 0);
    }
}

void counter_tests() {
    single_counter_constructors();
    chained_counter_constructors();
    single_counter_setter();
    single_counter_max_wrap();
    single_counter_oflow();
    chained_counters_oflow();
    out_of_range_set();
    out_of_range_throw();
}

#include "Clock.h"

void clock_tick_tests() {
    Clock c{"myclock"};
    SHOW_("myclock=0.00:00:00",   c);
    SHOW_("true",                 c.IsFloor());
    SHOW_("myclock=0.00:00:01",   c.TickUp());
    SHOW_("false",                c.IsFloor());
    SHOW_("myclock=0.00:00:02",   c.TickUp());
    SHOW_("myclock=0.00:00:03",   c.TickUp());
    SHOW_("myclock=0.00:00:58",   c.Seconds(58));
    SHOW_("myclock=0.00:00:59",   c.TickUp());
    SHOW_("myclock=0.00:01:00",   c.TickUp());
    SHOW_("false",                c.IsFloor());
    SHOW_("myclock=0.00:01:01",   c.TickUp());
    SHOW_("myclock=0.00:59:59",   c.Minutes(59).Seconds(59));
    SHOW_("myclock=0.01:00:00",   c.TickUp());
    SHOW_("false",                c.IsFloor());
    SHOW_("myclock=0.23:59:59",   c.Hours(23).Minutes(59).Seconds(59));
    SHOW_("myclock=1.00:00:00",   c.TickUp());
    SHOW_("false",                c.IsFloor());
    SHOW_("myclock=123.00:00:00", c.Days(123));
    SHOW_("myclock=122.23:59:59", c.TickDown());
    SHOW_("myclock=122.23:00:01", c.Minutes().Seconds(1));
    SHOW_("myclock=122.23:00:00", c.TickDown());
    SHOW_("myclock=122.22:59:59", c.TickDown());
    SHOW_("myclock=122.00:00:00", c.Hours().Minutes().Seconds());
    SHOW_("false",                c.IsFloor());
    SHOW_("myclock=0.00:00:00",   c.Days());
    SHOW_("true",                 c.IsFloor());
}

#include <initializer_list>

Clock make_clock(const std::initializer_list<int>& init) {
    auto init_it = init.begin();
    auto save_sequential_assign_from = [&init_it](auto li) {
        const auto result = (init_it != li.end()) ? *init_it++ : 0;
	return static_cast<UpDownCounter::value_type>(result);
    };
    const auto d = save_sequential_assign_from(init);
    const auto h = save_sequential_assign_from(init);
    const auto m = save_sequential_assign_from(init);
    const auto s = save_sequential_assign_from(init);
    return Clock{"clk2", d, h, m, s};
}

void clock_move_tests() {
    Clock c{make_clock({4, 3, 2, 1})}; SHOW_("clk2=4.03:02:01", c);
    Clock c2{std::move(c)};            SHOW_("clk2=4.03:02:01", c2);
    c = make_clock({0, 0, 0, 1});      SHOW_("clk2=0.00:00:01", c);
}

void clock_tests() {
    clock_tick_tests();
    clock_move_tests();
}

int main() {
    std::cout.setf(std::ios::boolalpha);
    counter_tests();
    clock_tests();
    SHOW_TEST_SUMMARY();
}

#else

#include <cstdlib>
#include <stdexcept>
#include <iostream>

extern void appl();

int main()
{
    try {
        appl();
        return EXIT_SUCCESS;
    }
    catch (const char* e) {
        std::clog << "terminated -- reason: " << e << std::endl;
    }
    catch (int e) {
        std::clog << "terminated -- error code: " << e << std::endl;
    }
    catch (std::exception &e) {
        std::clog << "terminated -- uncaught exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::clog << "terminated -- uncaught non-standard exception" << std::endl;
    }
    return EXIT_FAILURE;
}
#endif

#ifdef UNIT_TESTING

#include <iostream>
#include <sstream>

int SHOW_tests = 0;
int SHOW_failed = 0;
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
    typedef unsigned long long ULL;
    SHOW_("3", ULL(UpDownCounter(3, 5, nullptr).GetValue()));
    SHOW_("5", ULL(UpDownCounter(3, 5, nullptr).GetLimit()));
//  SHOW_("3", ULL(UpDownCounter(3, 5, NULL).GetValue()));
//  SHOW_("5", ULL(UpDownCounter(3, 5, NULL).GetLimit()));
    SHOW_("3", ULL(UpDownCounter(3, 5).GetValue()));
    SHOW_("5", ULL(UpDownCounter(3, 5).GetLimit()));
    SHOW_("0", ULL(UpDownCounter(5, nullptr).GetValue()));
    SHOW_("5", ULL(UpDownCounter(5, nullptr).GetLimit()));
//  SHOW_("0", ULL(UpDownCounter(5, NULL).GetValue()));
//  SHOW_("5", ULL(UpDownCounter(5, NULL).GetLimit()));
    SHOW_("0", ULL(UpDownCounter(5).GetValue()));
    SHOW_("5", ULL(UpDownCounter(5).GetLimit()));
    SHOW_("0", ULL(UpDownCounter().GetValue()));
    SHOW_("0", ULL(UpDownCounter().GetLimit()));
}

void chained_counter_constructors() {
    typedef unsigned long long ULL;
    UpDownCounter hi(0, 3); SHOW_("0", ULL(hi.GetValue()));
                            SHOW_("3", ULL(hi.GetLimit()));
    UpDownCounter lo(&hi);  SHOW_("0", ULL(lo.GetValue()));
                            SHOW_("0", ULL(lo.GetLimit()));
    SHOW_("2",    lo.DownCount(),      ULL(hi.GetValue()));
    SHOW_("0",    lo.UpCount(),        ULL(hi.GetValue()));

    // !!!
    // TBD: Test other combinations with chained counters
    // !!!
}

#include <limits>

void single_counter_setter() {
    typedef unsigned long long ULL;
    UpDownCounter ud_0_max;	SHOW_("0", ULL(ud_0_max.GetValue()));
                               	SHOW_("0", ULL(ud_0_max.GetLimit()));
    SHOW_("123",  ud_0_max.SetValue(123), ULL(ud_0_max.GetValue()));
                               	SHOW_("0", ULL(ud_0_max.GetLimit()));
}

#include <string>

template<typename T>
std::string max_init(T m) {
	std::ostringstream os;
        os << m;
        return os.str();
}

void single_counter_max_wrap() {
    typedef unsigned long long ULL;
    const ULL max = std::numeric_limits<UpDownCounter::value_type>::max();
    const std::string almost_max = max_init(max-1);
    const std::string exactly_max = max_init(max+0);

    UpDownCounter ud_0_max;                 SHOW_("0", ULL(ud_0_max.GetValue()));
                                            SHOW_("0", ULL(ud_0_max.GetLimit()));
    SHOW_(almost_max,        ud_0_max.SetValue(max-1), ULL(ud_0_max.GetValue()));
    SHOW_(exactly_max,       ud_0_max.UpCount(),       ULL(ud_0_max.GetValue()));
    SHOW_("0",               ud_0_max.UpCount(),       ULL(ud_0_max.GetValue()));
    SHOW_("1",               ud_0_max.UpCount(),       ULL(ud_0_max.GetValue()));
    SHOW_("0",               ud_0_max.DownCount(),     ULL(ud_0_max.GetValue()));
    SHOW_(exactly_max,       ud_0_max.DownCount(),     ULL(ud_0_max.GetValue()));
    SHOW_(almost_max,        ud_0_max.DownCount(),     ULL(ud_0_max.GetValue()));
}

void single_counter_oflow() {
    typedef unsigned long long ULL;
    UpDownCounter ud_3_5(3, 5); SHOW_("3", ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
    SHOW_("4", ud_3_5.UpCount(),           ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
    SHOW_("0", ud_3_5.UpCount(),           ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
    SHOW_("1", ud_3_5.UpCount(),           ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
    SHOW_("0", ud_3_5.DownCount(),         ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
    SHOW_("4", ud_3_5.DownCount(),         ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
    SHOW_("3", ud_3_5.DownCount(),         ULL(ud_3_5.GetValue()));
                                SHOW_("5", ULL(ud_3_5.GetLimit()));
}

void chained_counters_oflow() {
    typedef unsigned long long ULL;
    UpDownCounter hi(3);        SHOW_("0", ULL(hi.GetValue()));
                                SHOW_("3", ULL(hi.GetLimit()));
    UpDownCounter lo(4, &hi);   SHOW_("0", ULL(lo.GetValue()));
                                SHOW_("4", ULL(lo.GetLimit()));
    SHOW_("1", lo.UpCount(),               ULL(lo.GetValue()));
                                SHOW_("0", ULL(hi.GetValue()));
    SHOW_("2", lo.UpCount(),               ULL(lo.GetValue()));
                                SHOW_("0", ULL(hi.GetValue()));
    SHOW_("3", lo.UpCount(),               ULL(lo.GetValue()));
                                SHOW_("0", ULL(hi.GetValue()));
    SHOW_("0", lo.UpCount(),               ULL(lo.GetValue()));
                                SHOW_("1", ULL(hi.GetValue()));
    SHOW_("1", lo.UpCount(),               ULL(lo.GetValue()));
                                SHOW_("1", ULL(hi.GetValue()));
    SHOW_("0", lo.DownCount(),             ULL(lo.GetValue()));
                                SHOW_("1", ULL(hi.GetValue()));
    SHOW_("3", lo.DownCount(),             ULL(lo.GetValue()));
                                SHOW_("0", ULL(hi.GetValue()));
}

void out_of_range_throw() {
    typedef unsigned long long ULL;
    const ULL max = std::numeric_limits<UpDownCounter::value_type>::max();
    try {
        UpDownCounter xx(3, 2);
        SHOW_("should have thrown", 0);
    }
    catch (UpDownCounter::OutOfRangeValue& ex) {
        SHOW_("3", ULL(ex.Value));
        SHOW_("2", ULL(ex.MaxValue));
    }
    try {
        UpDownCounter(2).SetValue(3);
        SHOW_("should have thrown", 0);
    }
    catch (UpDownCounter::OutOfRangeValue& ex) {
        SHOW_("3", ULL(ex.Value));
        SHOW_("2", ULL(ex.MaxValue));
    }
    try {
        UpDownCounter ok(max, UpDownCounter::value_type(0));
    }
    catch (...) {
        SHOW_("should NOT have thrown", 0);
    }
    try {
        UpDownCounter().SetValue(max);
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
    out_of_range_throw();
}

#include "Clock.h"

void clock_tick_tests() {
    Clock c("myclock");
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

void clock_move_tests() {
    Clock c0("living", 4, 3, 2, 1);	SHOW_("living=4.03:02:01",	c0);
    Clock c1(c0);			SHOW_("living=4.03:02:01",	c1);
					SHOW_("?dead?=4.03:02:01", 	c0);
    c1.TickUp();			SHOW_("living=4.03:02:02",	c1);
					SHOW_("?dead?=4.03:02:01", 	c0);
    c0 = c1;				SHOW_("living=4.03:02:02",	c0);
    c0.TickUp();			SHOW_("living=4.03:02:03",	c0);
					SHOW_("?dead?=4.03:02:02", 	c1);
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



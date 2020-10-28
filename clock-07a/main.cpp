#ifdef UNIT_TESTING

#include <iostream>
#include <sstream>

#define SHOW_(expect, ...)\
    do {\
        std::ostringstream result;\
        result.copyfmt(std::cout);\
        result << (__VA_ARGS__);\
        std::cout << __FUNCTION__ <<  ':' << __LINE__ << '\t'\
                  << #__VA_ARGS__ << " --> " << result.str();\
        if (result.str() != expect) {\
                std::cout << " != " << expect;\
        }\
        std::cout << std::endl;\
    }\
    while (0)

#include "UpDownCounter.h"

void single_counter_constructors() {
    SHOW_("3", UpDownCounter(3, 5, NULL).GetValue());
    SHOW_("5", UpDownCounter(3, 5, NULL).GetLimit());
//  SHOW_("3", UpDownCounter(3, 5, NULL).GetValue());
//  SHOW_("5", UpDownCounter(3, 5, NULL).GetLimit());
    SHOW_("3", UpDownCounter(3, 5).GetValue());
    SHOW_("5", UpDownCounter(3, 5).GetLimit());
    SHOW_("0", UpDownCounter(5, static_cast<UpDownCounter*>(NULL)).GetValue());
    SHOW_("5", UpDownCounter(5, static_cast<UpDownCounter*>(NULL)).GetLimit());
//  SHOW_("0", UpDownCounter(5, NULL).GetValue());
//  SHOW_("5", UpDownCounter(5, NULL).GetLimit());
    SHOW_("0", UpDownCounter(5).GetValue());
    SHOW_("5", UpDownCounter(5).GetLimit());
    SHOW_("0", UpDownCounter().GetValue());
    SHOW_("0", UpDownCounter().GetLimit());
}

void chained_counter_constructors() {
    UpDownCounter hi(0, 3); SHOW_("0", hi.GetValue());
                            SHOW_("3", hi.GetLimit());
    UpDownCounter lo(&hi);  SHOW_("0", lo.GetValue());
                            SHOW_("0", lo.GetLimit());
    SHOW_("2",    lo.DownCount(),      hi.GetValue());
    SHOW_("0",    lo.UpCount(),        hi.GetValue());

    // !!!
    // TBD: Test other combinations with chained counters
    // !!!
}

#include <limits>

void single_counter_setter() {
    UpDownCounter ud_0_max;    SHOW_("0", ud_0_max.GetValue());
                               SHOW_("0", ud_0_max.GetLimit());
    SHOW_("123",  ud_0_max.SetValue(123), ud_0_max.GetValue());
                               SHOW_("0", ud_0_max.GetLimit());
}

#include <string>

std::string max_init(int m) {
	std::ostringstream os;
        os << m;
        return os.str();
}

void single_counter_max_wrap() {
    const int max
        = std::numeric_limits<UpDownCounter::value_type>::max();
    const std::string almost_max = max_init(max-1);
    const std::string exactly_max = max_init(max+0);

    UpDownCounter ud_0_max;                 SHOW_("0", ud_0_max.GetValue());
                                            SHOW_("0", ud_0_max.GetLimit());
    SHOW_(almost_max,        ud_0_max.SetValue(max-1), ud_0_max.GetValue());
    SHOW_(exactly_max,       ud_0_max.UpCount(),       ud_0_max.GetValue());
    SHOW_("0",               ud_0_max.UpCount(),       ud_0_max.GetValue());
    SHOW_("1",               ud_0_max.UpCount(),       ud_0_max.GetValue());
    SHOW_("0",               ud_0_max.DownCount(),     ud_0_max.GetValue());
    SHOW_(exactly_max,       ud_0_max.DownCount(),     ud_0_max.GetValue());
    SHOW_(almost_max,        ud_0_max.DownCount(),     ud_0_max.GetValue());
}

void single_counter_oflow() {
    UpDownCounter ud_3_5(3, 5); SHOW_("3", ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
    SHOW_("4", ud_3_5.UpCount(),           ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
    SHOW_("0", ud_3_5.UpCount(),           ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
    SHOW_("1", ud_3_5.UpCount(),           ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
    SHOW_("0", ud_3_5.DownCount(),         ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
    SHOW_("4", ud_3_5.DownCount(),         ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
    SHOW_("3", ud_3_5.DownCount(),         ud_3_5.GetValue());
                                SHOW_("5", ud_3_5.GetLimit());
}

void chained_counters_oflow() {
    UpDownCounter hi(3);        SHOW_("0", hi.GetValue());
                                SHOW_("3", hi.GetLimit());
    UpDownCounter lo(4, &hi);   SHOW_("0", lo.GetValue());
                                SHOW_("4", hi.GetLimit());
    SHOW_("1", lo.UpCount(),               lo.GetValue());
                                SHOW_("0", hi.GetValue());
    SHOW_("2", lo.UpCount(),               lo.GetValue());
                                SHOW_("0", hi.GetValue());
    SHOW_("3", lo.UpCount(),               lo.GetValue());
                                SHOW_("0", hi.GetValue());
    SHOW_("0", lo.UpCount(),               lo.GetValue());
                                SHOW_("1", hi.GetValue());
    SHOW_("1", lo.UpCount(),               lo.GetValue());
                                SHOW_("1", hi.GetValue());
    SHOW_("0", lo.DownCount(),             lo.GetValue());
                                SHOW_("1", hi.GetValue());
    SHOW_("3", lo.DownCount(),             lo.GetValue());
                                SHOW_("0", hi.GetValue());
}

void counter_tests() {
    single_counter_constructors();
    chained_counter_constructors();
    single_counter_setter();
    single_counter_max_wrap();
    single_counter_oflow();
    chained_counters_oflow();
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

int main() {
    std::cout.setf(std::ios::boolalpha);
    counter_tests();
    clock_tick_tests();
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
    return EXIT_FAILURE;
}
#endif



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
    

#include "DHMS_Counter.h"

void counter_ctors() {
    using ULL = unsigned long long;
    DHMS_Counter c{};               SHOW_("0", ULL{c.GetSeconds()}  );
                                    SHOW_("0", ULL{c.GetMinutes()}  );
                                    SHOW_("0", ULL{c.GetHours()}    );
                                    SHOW_("0", ULL{c.GetDays()}     );
    DHMS_Counter c2{1, 2, 3, 4};    SHOW_("4", ULL{c2.GetSeconds()} );
                                    SHOW_("3", ULL{c2.GetMinutes()} );
                                    SHOW_("2", ULL{c2.GetHours()}   );
                                    SHOW_("1", ULL{c2.GetDays()}    );
}

void counter_setters() {
    using ULL = unsigned long long;
    DHMS_Counter c{};
    c.SetSeconds(1);    SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("0",  ULL{c.GetMinutes()} );
                        SHOW_("0",  ULL{c.GetHours()}   );
                        SHOW_("0",  ULL{c.GetDays()}    );
    c.SetMinutes(2);    SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("2",  ULL{c.GetMinutes()} );
                        SHOW_("0",  ULL{c.GetHours()}   );
                        SHOW_("0",  ULL{c.GetDays()}    );
    c.SetHours(3);      SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("2",  ULL{c.GetMinutes()} );
                        SHOW_("3",  ULL{c.GetHours()}   );
                        SHOW_("0",  ULL{c.GetDays()}    );
    c.SetDays(4);       SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("2",  ULL{c.GetMinutes()} );
                        SHOW_("3",  ULL{c.GetHours()}   );
                        SHOW_("4",  ULL{c.GetDays()}    );
    c.SetDays(99);      SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("2",  ULL{c.GetMinutes()} );
                        SHOW_("3",  ULL{c.GetHours()}   );
                        SHOW_("99", ULL{c.GetDays()}    );
    c.SetMinutes(0);    SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("0",  ULL{c.GetMinutes()} );
                        SHOW_("3",  ULL{c.GetHours()}   );
                        SHOW_("99", ULL{c.GetDays()}    );
    c.SetHours(17);     SHOW_("1",  ULL{c.GetSeconds()} );
                        SHOW_("0",  ULL{c.GetMinutes()} );
                        SHOW_("17", ULL{c.GetHours()}   );
                        SHOW_("99", ULL{c.GetDays()}    );
    c.SetSeconds(59);   SHOW_("59", ULL{c.GetSeconds()} );
                        SHOW_("0",  ULL{c.GetMinutes()} );
                        SHOW_("17", ULL{c.GetHours()}   );
                        SHOW_("99", ULL{c.GetDays()}    );
}

void counter_upcount() {
    using ULL = unsigned long long;
    DHMS_Counter c1{0, 0, 0, 58};
    c1.UpCount();       SHOW_("59", ULL{c1.GetSeconds()});
                        SHOW_("0",  ULL{c1.GetMinutes()});
    c1.UpCount();       SHOW_("0",  ULL{c1.GetSeconds()});
                        SHOW_("1",  ULL{c1.GetMinutes()});
    DHMS_Counter c2{0, 0, 58, 59};
    c2.UpCount();       SHOW_("0",  ULL{c2.GetSeconds()} );
                        SHOW_("59", ULL{c2.GetMinutes()} );
    DHMS_Counter c3{0, 0, 59, 59};
    c3.UpCount();       SHOW_("0",  ULL{c3.GetSeconds()} );
                        SHOW_("0",  ULL{c3.GetMinutes()} );
                        SHOW_("1",  ULL{c3.GetHours()}   );
    DHMS_Counter c4{0, 23, 59, 59};
    c4.UpCount();       SHOW_("0",  ULL{c4.GetSeconds()} );
                        SHOW_("0",  ULL{c4.GetMinutes()} );
                        SHOW_("0",  ULL{c4.GetHours()}   );
                        SHOW_("1",  ULL{c4.GetDays()}   );
}

void counter_downcount() {
    //TBD
}

void counter_bounds() {
    //TBD
}

void counter_tests() {
    counter_ctors();    
    counter_setters();
    counter_upcount();
    counter_downcount();
    counter_bounds();
}

#include "Clock.h"

void clock_tick_tests() {
    Clock c{"myclock"};
    SHOW_("myclock=0.00:00:00",   c             );
    SHOW_("true",                 c.IsFloor()   );
    SHOW_("myclock=0.00:00:01",   c.TickUp()    );
    SHOW_("false",                c.IsFloor()   );
    SHOW_("myclock=0.00:00:02",   c.TickUp()    );
    SHOW_("myclock=0.00:00:03",   c.TickUp()    );
    SHOW_("myclock=0.00:00:58",   c.Seconds(58) );
    SHOW_("myclock=0.00:00:59",   c.TickUp()    );
    SHOW_("myclock=0.00:01:00",   c.TickUp()    );
    SHOW_("false",                c.IsFloor()   );
    SHOW_("myclock=0.00:01:01",   c.TickUp()    );
    SHOW_("myclock=0.00:59:59",   c.Minutes(59)
                                   .Seconds(59) );
    SHOW_("myclock=0.01:00:00",   c.TickUp()    );
    SHOW_("false",                c.IsFloor()   );
    SHOW_("myclock=0.23:59:59",   c.Hours(23)
                                   .Minutes(59)
                                   .Seconds(59) );
    SHOW_("myclock=1.00:00:00",   c.TickUp()    );
    SHOW_("false",                c.IsFloor()   );
    SHOW_("myclock=123.00:00:00", c.Days(123)   );
    SHOW_("myclock=122.23:59:59", c.TickDown()  );
    SHOW_("myclock=122.23:00:01", c.Minutes().Seconds(1));
    SHOW_("myclock=122.23:00:00", c.TickDown()  );
    SHOW_("myclock=122.22:59:59", c.TickDown()  );
    SHOW_("myclock=122.00:00:00", c.Hours()
                                   .Minutes()
                                   .Seconds()   );
    SHOW_("false",                c.IsFloor()   );
    SHOW_("myclock=0.00:00:00",   c.Days()      );
    SHOW_("true",                 c.IsFloor()   );
}

#include <initializer_list>

Clock make_clock(const std::initializer_list<int>& init) {
    auto init_it = init.begin();
    auto save_sequential_assign_from = [&init_it](auto li) {
        const auto result = (init_it != li.end()) ? *init_it++ : 0;
	return static_cast<DHMS_Counter::value_type>(result);
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

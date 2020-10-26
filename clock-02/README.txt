Adding an interface to the clock
================================

Adding an interface (class) `IClock` makes the design more
flexible. Among other things several different types of clocks
(with different counter arrangements) may implememt this
interface.

It is not shown in this solution, as simply moving all of the
former member functions of clock to the `IClock` interface is
disputable: It defeats at least one of the design goals, if is
to operate clocks with a different number of counters over that
interface.

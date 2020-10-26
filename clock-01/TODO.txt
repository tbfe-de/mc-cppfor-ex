To advance to the next step apply the following changes:

* Add an interface `IClock` through which several kinds of clocks
  may be operated, eg.:
  * an `HHMMSS_Clock` counting hours, minutes, and seconds (ie.
    as the previous `Clock` did);
  * a `Stopwatch` counting microseconds up to 999 and (unlimited)
    seconds.
  * am "operating hours meter" counting days (unlimeted), hours
    and minutes.

NOTE: You do not necessarily need to implement another clock but
      stay with the current (single) clock. But in that case at
      least show that you can create a `Clock` object in `main`
      and hand it over to a function `appl` accepting and
      `IClock&` argument.

* Setup the project to consist of header files and separately
  compiled source filess (= implementation files).
  * minimize referencing headers from implementations;
  * if necessary use forward declarations (or maybe introduce
    forwarding headers).

=================================================================

Optional:

* Discuss ways to easily provide "unlimited" counters.

* How could "permanent overflow indicators" be added to the last
  counter stage, indicating that the whole chain had overlown at
  least once?

* Discuss the problem of the `Set` member function, which may
  require a different number of arguments depending on the number
  of `Counter`-s used in that kind of clock implementation.

NOTE: If time allows, feel free to implement some of the features
      only discussed/suggested above.


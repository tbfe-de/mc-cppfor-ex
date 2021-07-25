# Adding an Interface to the Clock

There are two ways to do this exercise:

1. Review the solution `clock-02` so that you can answer the
   following questions:
   - Which two files are new compared to what we started with?
   - Which one of the new file defines a class and which one
     a function?
   - In what respect is the new class special and justifies
     to call it an "interface"?
   - Which translation unit defines `Clock` instances and
     therefore depends on the actual class `Clock`?
   - Which translation unit only refers to `Clock` objects
     via the interface and therefore does NOT depend on
     class `Clock`?
   - Why can't `operator<<` not be put in the interface?
   - How is `operator<<` still decoupled from the
     implementation of `Clock` instances?

2. **Alternatively** If you are already moderately
   experienced with the basics of C++ and OOP class design,
   so that the concept interfaces isn't completely new to
   you, maybe go right ahead and start with creating an
   interface through which the `Clock` class can be operated
   and which also decouples the implementation of a `CLock`
   from the clients using it. the code using it.

   The interface should consist of these three member
   functions which do the obvious (judging from their name):
   - `TickUp(int seconds)` - advance the clock by the given
     number of seconds (default 1 second).
   - `Set(int hours, int minutes, int seconds)` - set the
      clock to the given values.
   - `Print(std::ostream& strm)` - output the current state of
     the clock in `HH:MM:SS` format to `strm`.

   If you actually do an implementation setup the project
   - so that it consists of header files and separately
     compiled source files (aka. "implementation files" or
     "translation units");
   - but strive minimizing header file references from
     implementations;
   - if necessary use forward declarations (or maybe introduce
     forwarding headers).

* * * * *

Advanced (only if you did part 2):

Make yourself aware of the special interfaces feature that they
may operate on several kinds of clocks, eg.:
  - an `HHMMSS_Clock` counting hours, minutes, and seconds (ie.
    as the previous `Clock` did);
  - a `Stopwatch` counting microseconds up to 999 and (unlimited)
    seconds.
  - an "operating hours meter" counting days (unlimited), hours
    and minutes.

NOTE: You do not need to implement all these kinds of clocks.

* * * * *

Optional:

- Discuss ways to easily provide "unlimited" counters.
- How could "permanent overflow indicators" be added to the
  last counter stage, indicating that the whole chain had
  overflown at least once?
- Discuss the problem of the `Set` member function which may
  require a different number of arguments depending on the number
  of `Counter`-s used in that kind of clock implementation.

NOTE: Again the intend here is you need NOT go and implement
      something but only consider the particular problems that
      may arise fro such extensions.

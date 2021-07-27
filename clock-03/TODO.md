# Applying the "Non Virtual Interface" Idiom

Change the class design to apply the NVI-Idiom (= Non
Virtual Interface)
- Make the currently `public` member function
    `LimitCounter::Count` and `LimitCounter::Reset`
    NON-`virtual` and `final`.
- From inside these member functions, when the counter value
  is reset, call new `virtual` member functions, say
  - `LimitCounter::OverflowAction` and
  - `LimitCounter::ResetAction`
- Implement both EMPTY in class `LimitCounter`.
- Overwrite both in class `OverflowCounter` to simply call
  - `next_counter_.Count()` or
  - `next_counter_.Reset()` respectively

**Note:**\
These two functions may (and should) be private but can
still be overridden in the derived class.

* * * * *

Optional:

- Consider the case that
  - there may be many more such "extension points" like
    `LimitCounter::OverflowAction` and `LimitCounter::ResetAction`
  -  most of which stay unused in the derived classes.
- What are the Pros and Cons?

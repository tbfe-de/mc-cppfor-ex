# A Counter Chain Connected via References

Proceed as follows:

- Improve the design by avoiding the need to have a data
  member `next_counter_` in the counters when it is not
  needed (ie. in the last counter of the chain):
  - implement one class `LimitCounter`
    - handling the reset logic in its `Count` member
      function but …
    - … does NOT allow to chain to a next counter stage;
  - from that derive a class `OverflowCounter` which calls
    the base class member function `LimitCounter::Count` for
    the reset logic.
  - once it detects a reset needed to take takes place it
    forwards the carry in the appropriate way.
- As there is always a next counter stage, instead of a
  pointer a reference can (and should) be used to connect to
  it.

For an easier start here are the skeletons of the two classes:
```
class LimitCounter {
private:
    int value_;
    int max_value;
public:
    LimitCounter(int max_value)
        : value_{0}
        , max_value_{max_value}
    {}
    …
};

class OverflowCounter : public LimitCounter {
private:
    LimitCounter& next_counter_;
    ...
public:
    OverflowCounter(int max_value, LimitCounter& next_counter)
        : LimitCounter{max_value}
        , next_counter{next_counter_}
    {}
    …
};
```

- The "hint" whether a reset took place, may
  - EITHER be given by a `bool` return value of\
    `LimitCounter::Count` which then is tested\
    in `OverflowCounter::Count`
  - OR by testing the base class counter value.

For an easier start here are the skeletons how the two
`Count` member functions might be implemented.

**EITHER** (first solution) that is the way to go:
```
bool LimitCounter::Count() {
    // TBD: increment counter
    if (/* TBD: test whether limit is reached, if so */) {
        // TBD: reset value to 0
        return true;
    }
    return false;
}
// override (and reuse) the inherited implementation
bool OverflowCounter::Count() {
    if (LimitCounter::Count()) {
        next_counter_.Count();
        return true;
    }
    return false;
}
```

**ALTERNATIVELY** (second solution) that is the way to go:
```
void LimitCounter::Count() {
    // TBD: increment counter
    if (/* TBD: test whether limit is reached, if so */) {
        // TBD: reset value to 0
        return true;
    }
}
// then override (and reuse) the inherited implementation
void OverflowCounter::Count() {
    LimitCounter::Count();
    if (LimitCounter::GetValue() == 0) {
        // obviously a reset occurred
        next_counter_.Count();
    }
}
```

- Apply similar changes for the `LimitCounter::Reset`:
  - simply set the counter value to `0`
- And to `OverflowCounter::Reset`:
  - call the inherited implementation,
  - then reset the chained counter.
    
* * * * *

Optional:

- Make sure you understand the design and especially why
  - with three or more counters in the chain it is ESSENTIAL
    to use late binding (= `virtual` member functions) for
    `LimitCounter::Count` and `LimitCounter::Reset`,
  - while with only two counters (ie. a single
    `OverflowCounter` connected to a single `LimitCounter`)
    it would work without.
- Furthermore, comparing the new design with a base and a derived
  class to the previous pointer-based solution with a single
  class, which made a decision whether there is a next counter
  in the chain in a conditional statement …

```
    …
    if (next_counter_ != nullptr)
        next_counter_.Count();
    …
```

- …: WHERE is this test gone now?
- I.e. How does the equivalent branch in the control-flow
  happen?
- Or isn't still necessary to be handled any longer?

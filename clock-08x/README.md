# Various Improvements of `Clock` and `UpDownCounter`

This variant demonstrates how the different behavior when
setting an "out of range" value either in the constructor or
with `SetValue` may be achieved with a common helper
function that throws an exception.
- As argued in the `README.md` of the main stream this
  solution appears to be inferior because of a less
  consistent user experience.
- Especially "converting back" the behavior of a helper
  function that throws an exception into returning a
  value with a local `try`- `catch` construct is
  sub-optimal as exception handling typically involves
  more overhead then just testing a return value.
- Therefore a common helper preferably should indicate the
  problem with a return value which is tested and turned
  into throwing an exception in the constructor, not vice
  versa.
- For details wrt. to the difference in implementation do a
  side by side compare of files
  - `clock-08/UpDownCounter.h` to
  - `clock-08x/UpDownCounter.h`
  - `clock-08/UpDownCounter.cpp` to
  - `clock-08x/UpDownCounter.cpp`.
- For details wrt. to the difference in unit testing do a side
  - `clock-08/main.cpp` to
  - `clock-08x/main.cpp`.
   
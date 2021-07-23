# Improved Output / TDD Support via `SHOW` Macro

The macro `SHOW_` - as a variant of `SHOW` with an
underscore added - now has an extra argument allowing to specify
an expected value.
- If the actual value meets the expectation it will be no
  further immediate output will be generated.
- If the actual output differs from the expectation both
  will be shown:
  - expectation and
  - actual output.

 The intend is of course to make the failed expectations
 standout in the test output.
 - This approach will be extended later into the TDD paradigm
   (= Test Driven Development).
- A summary will then be added to indicate when the `main`
  function ends what is the number of passed vs. failed
  tests.
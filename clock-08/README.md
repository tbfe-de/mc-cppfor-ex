# Various Improvements of `Clock` and `UpDownCounter`

Selected items proposed in TODO.md of the previous step can
be discussed with the instructor now – feel free to ask any
questions you have.

One general point to understand in advance is the code in
file `main.cpp` has two separate purposes:

1. It implements intensive unit testing for all the classes
    developed so far.
2. It calls the actual "application function" `appl` which
    is still to be developed.

**Which part of the main function is controlled by the macro
`UNIT_TESTING`.**
- If the macro is defined, a `main` function with all the
  unit tests is compiled.
- If the macro is NOT defined, a main function calling
  `appl` is compiled.

Here is an overview of what has been implemented from the
TODO-s of the previous step:

## General Topic – Exceptions

In `appl.cpp` various ways to throw exceptions are
demonstrated. All but one are commented out, as they are
meant to test the code the `catch`-blocks in `main.cpp`.

- The intend here is to try out an exception by
  un-commenting the `throw` you want to demonstrate in
  `appl` and "visually" check the message appearing as
  output.

- Besides that the current content of `appl` allows to
  demonstrate what might happen later, if the actual
  application i being developed, and would throw an
  exception from a standard library class.
  - More specifically in this case: if an `std::array` STL
    container is accessed outside its bounds.

## General Topic – TDD (Test Driven Development)

In `main.cpp` there are now two global variables
(`SHOW_tests` and `SHOW_failed`) counting the total number
of *tests done* vs. *failed tests* (i.e. those that didn't
produce the expected output).

- An additional macro `SHOW_TEST_SUMMARY()` is provided
  which is to show a message.
  - That macro is meant to be called **as last thing** in
    `main`.
  - The message itself depends on whether there are failed
    tests or *"all tests passed"*.

## General Topic – "Copy vs. Move"

Instead of simply `delete`-ing both, copy and the move
operations of class `Clock`, the move operation was
explicitly implemented.

For details do a side by side compare of
- header files
  - `clock-07/Clock.h` to
  - `clock-08/Clock.h`
- and implementation files
  - `clock-07/Clock.cpp` to
  - `clock-08/Clock.cpp`.

## General Topic – Code Robustness

Some changes with the intend to "improve the overall code
quality" have been made, covering the following main areas:

- Readability/understandability of the source code itself by
  adding comments, e.g. more clearly describing the purpose
  of the various `UpDownCounter` constructors.

- Robustness has been improved by:
  - "Precondition Checking", like catching potential USAGE
    errors early (e.g. whether a start value is given to the
    constructor that is already outside the limits within
    the counter can operate.
  - "Postcondition Checking", like catching potential
    IMPLEMENTATION error that led to counter value outside the
    allowed range.

- The different behavior to indicated an out of range value
  being set in the constructor and with `SetValue`
  (exception thrown vs. return `bool`) has been NOT been
  implemented in the main stream solution.
  - Reason: It might "surprise" users (= other developers
    using that class) who have not thoroughly checked the
    documentation.
  - As it is not possible to indicate the problem with a
    return value in both cases (as the constructor is
    supposed to always leave a valid object) it was decided
    to throw an exception in both cases.
  - That behavior was implemented in a common helper
    function (named `check_in_range_value`) it is guaranteed
    to work consistently in both case.

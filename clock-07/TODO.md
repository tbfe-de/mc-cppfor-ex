# Various Improvements or `UpDownCounter`

In this step there are suggestions for modifications you
can pick from.

* * * * *

**BUT STOP!**\
FIRST do an thorough code review so that you can answer the
the questions following below.**

(Or if you can't take notes which question stopped you so
that these can receive special attention when the solution
is discussed.)

* * * * *

- Obviously there are two different `main` programs included
  in `main.cpp` – how is it selected which one gets
  compiled?

- What is the difference between between the `SHOW` macro
  used until now and the `SHOW_` macro with the underscore
  at the end that is used here?
  - The version ending in an underscore was already part
    of one of the "dead end paths" in an earlier solution.
  - It wasn't continued then but is picked up now. If that
    dead end path was already covered, the explanations
    given then still appyly.

- Understand the purpose of the different constructors of
  class `UpDownCounter`:
  - Which ones are for building chains of counters?
  - Which ones allow to build a counter that are
    terminate a counter chain.

- What is the advantage of making `UpDownCounter` a template
  and which member variables and parameters will actually
  get a different type when the template is instantiated
  differently?

- What may be the reason for using a `static_assert` to
  enforce an unsigned type for instantiating the
  `UpDownCounter`?

- What (currently) happens if you compile `main` so that it
  run the code in `appl.cpp`?

* * * * *

If you think you have understood enough of the code to do
one or more of the modifications suggested below feel free
to try your hands on it.

- All suggestions following are INDEPENDENT from each other.
  You may well read the whole list first and then choose
  what you like best. Maybe start with the "General Topic"
  which is of most interest to you.

- Alternatively go to the solutions and compare the source
  files with tool of your choice showing the diff-s.

* * * * *

## General Topic – Code Robustness

- In the constructor of class `UpDownCounter` make sure the
  current value is inside the range `0` and `max_value - 1`
  - Proposal: If the value set is equal to or exceeds the
    maximum value allowed, set it to the allowed maximum.

- Similar in `SetValue`, but in this case indicate via a
  `bool` return value whether
  - the new value has actually been set (then return `true`)
  - or was out of range and has not been set (then return
    `false`).

## General Topic – Exceptions

- Modify the `main` program` calling the `appl` function
  as defined in source file `appl.c` so that it catches the
  exception currently thrown and displays its text before
  ending returning `EXIT_FAILURE`.


- Try throwing the following different exceptions from
  `appl` and demonstrate a `catch(...)` – i.e. using three
  dots as argument list – will handle them all. Note that
  the sub-items following here are ALTERNATIVES meant to
  be tried one after the other, NOT all together! But
  as trying them one after the other, leave the "inactive"
  ones as comment in the source code, as they will be
  useful to test the next main item.
  - throw just an integral number as "error code";
  - throw an exception class `NotYetImplemented` defined
    for that purpose;
  - throw an appropriate class from the standard exception
    hierarchy.

- In the `try`-block of the `main` program calling `appl`
  add all the appropriate `catch` blocks to show a meaningful
  message depending on which exception was caught, i.e. …
  - … if an integral value is thrown (as kind of a numeric
    "error code") include that value in the error message
     shown on `std::cerr`;
  - … if a `const char *` is thrown simply display it
    textually on `std::cerr`.
  - … if a standard exception is thrown display its `what()`
    text on `std::cerr`
  - … in the most generic catch block (the one defined with
    the three dots in the parenthesis) give a general
    message like *"application terminated with non-standard
    exception"*. (You cannot do more than that as no
    information is portably available in this case);
    
- If you throw an individually defined `NotYetImplemented`
    exception demonstrate what happens if there is **NO
    specific `catch` block** for it …
    - … ehen `NotYetImplemented` **IS** derived from one of
      standard exceptions (like it is typicallay recommended);
    - … and when `NotYetImplemented` is **NOT** derived
      from a standard exception.
    
## General Topic – TDD (Test Driven Development)

- Modify the `SHOW_`-macro so that …
  - … it generates output ONLY if the expectation is NOT met;
  - … it counts in two different global variables how many
    times it has been called and how many times of that the
    expectation was not met.
    
- At the end of the `main` program doing all the tests show
  a message how many tests have been run in total and how
  many of them failed (if any failed, otherwise you may just
  show "N tests passed" (with `N` being the total number of
  tests of course).

## General Topic – "Copy vs. Move"

- Consider the effort necessary – **without actually doing
  the implementation** – to turn `Clock` from currently
  being neither "copyable" nor "movable" into a "move only"
  class, i.e. a class which objects are still **NOT copyable**
  but may be returned as result from a "factory" function.
  - Be sure to understand the potential problem with the
    `UpDownCounter` chaining via pointers: the fact these
    objects are NEITHER "copyable" NOR "movable" themselves
    has an important reason!
  - The solution is NOT to provide move-operations in the
    `UpDownCounter` class: **the context to do a "move"
    correctly is NOT available within the `UpDownCounter`
    class itself.**
  - Rather the move-operations of class `Clock` needs to use
    the appropriate constructors of `UpDownCounter` (which
    already exists) to take the `value_` and `max_value_`
    of the `Clock` object being MOVED FROM but build the
    chain correctly in the `Clock` object being MOVED TO.
  - Beyond that, don't forget that `name_` (pointer member)
    of class `Clock` would need to be moved too.

- If you feel you understood that all – GO FOR IT AND DO THE
  IMPLEMENTATION …
  - … but do not forget to ADD TESTS for it too!
  - (Or maybe even write the tests before the implementation,
    which would be even more in the "spirit of TDD".)

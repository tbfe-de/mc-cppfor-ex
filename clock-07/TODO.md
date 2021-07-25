To advance to the next step apply the following changes:

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
STOP – FIRST do an thorough code review so that you at least can
answer the questions following below.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

* Obviously there are two different `main` programs included in
  `main.cpp` – how is it selected which one gets compiled?

* What is the difference between between the `SHOW` macro used
  until now and the `SHOW_` macro with the underscore at the end
  that is used here?

* Understand the purpose of the different constructors of class
  `UpDownCounter`:
  * Which ones are for building chains of counters?
  * Which ones allow to build a counter that uses?

* What is the advantage of making `UpDownCounter` a template and
  which member variables and parameters will actually get a
  different type when the template is instantiated differently?

* What may be the reason for using a `static_assert` to enforce
  an unsigned type for instantiating the `UpDownCounter`?

* What (currently) happens if you compile `main` so that it run
  the code in `appl.cpp`?

-----------------------------------------------------------------
If you think you have understood enough of the code to do one
or more of the modifications suggested below feel free to try
your hands on it.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
As all suggestions are INDEPENDANT of each other you may well
READ THE WHOLE LIST FIRST and then "pick and choose" according to
the "General Topic" which is of most interest to you.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
(Alternatively go to the solutions and compare the source files
with tool of your choice shows the diff-s.
-----------------------------------------------------------------

* General Topic – Code Robustness
  * In the constructor of class `UpDownCounter` make sure the
    current value is inside the range `0` and `max_value - 1`
    (Proposal: If the value set is equal to or exceeds the
    maximum value allowed set it to the maximum allowed value.
  * Similar in `SetValue`, but in this case indicate via a
    `bool` return value whether the new value has actually been
    set (then return `true`) or was out of range and has not
    been set (then return `false`).

* General Topic – Exceptions
  * Modify the `main` program` calling the `appl` function
    (defined in source file `appl.c`) so that it catches the
    exception currently thrown and displays its text before
    ending with `EXIT_FAILURE`.
  * Try throwing the following different exceptions from `appl`
    and demonstrate a `catch(...)` (i.e. using three dots as
    argument list will handle them all:
    * just an integral number as "error code";
    * an exception class `NotYetImplememted` defined for exactly
      that purpose;
    * an appropriate class from the standard exceptions;
  * In the `main` program calling `appl` in its `try` block,  add
    an add all the appropriate `catch` blocks to show a meaningful
    message depending on which exception was thrown, i.e.
    * if an integral value (as "error code") is thrown, include
      its value in the message;
    * if a `const char *` is throw simply display that;
    * if a standard exception is thrown display its `what()`
      text;
    * if the most generic catch block (the one defined with the
      three dots in its parenthesis) give a general message like
      "application terminated with non-standard exception" (you
      cannot do more than that as no information is portably
      available in this case);
    * If you throw an individually defined `NotYetImplemented`
      exception demonstrate what happens if there is NO specific
      `catch` block for it …
      * … when this exception is actually derived from one of
          standard exceptions;
      * … and when this is NOT the case.
    
* General Topic – TDD (Test Driven Development)
  * Modify the `SHOW_`-macro so that …
    * … it generates output ONLY if the expectation is NOT met
    * … it counts in two global variables how many times it has
    been called and how many time the expectation was not met.
  * At the end of the `main` program doing all the tests show a
    message how tests have been run and how many of them failed
    – if any, otherwise you may just show "N tests passed" (with
    `N` being the total number of tests of course).
  
* General Topic – "Copy vs. Move"
  * Consider the effort necessary to turn `Clock` from currently
    being neither "copyable" nor "movable" into a "move only"
    class (i.e. still not copyable but may be returned as result
    from a "factory" function.
    * Be sure to understand the potential problem with the
      `UpDownCounter` chaining via pointers – the fact these
      objects are NEITHER "copyable" NOR "movable" themselves has
      an important reason!
    * The solution is NOT to provide move-operations in the
      `UpDownCounter` class – the context to do it correctly
      is NOT available here!
    * Rather the move-operations of class `Clock` needs to use
      the appropriate constructors of `UpDownCounter` (which
      already exists) to take the `value_` and `max_value_` from
      the `Clock` object being MOVED FROM but build the chain in
      the correct for the object being MOVED TO.
    * Beyond that, don't forget that the `name_` (pointer member)
      of class `Clock` would need to be moved too.
  * If you feel you understood that all – GO FOR IT AND DO THE
    IMPLEMENTATION …
    * … and do not forget to ADD TESTS for it too
    * (or maybe write the tests before the implementation, which
      would be even more in the "spirit of TDD")

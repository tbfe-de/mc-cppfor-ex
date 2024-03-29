#  Encapsulate the Increment Logic and Data in a Class

- Instead of plain integers use objects of a simple class
  `Counter` with the following member data:
    - an `int value_` holding the current counter value;
    - a `const int max_value_` holding the limit up to which
      the counter can count until it gets reset to `0`;
    - `Counter *next_counter_` pointing to another counter
      to which an overflow is transferred when the current
      counter is reset;
    - for the last `Counter` in the chain that pointer needs
      to be be a `nullptr` and there needs to be a test for
      it before the overflow gets transferred.
- Centrally implement the reset logic when the limit is
  reached within the a member function `Count` in class
  `Counter`. (There are several ways to do this, see the
  "optional" section below.)
- Also implement member functions `SetValue` and `GetValue`
  so that the data members can be made `private`.

NOTE: You may implement **short** functions consisting of
      just some few statements as inline functions in the
      class `Counter`, in a file `Counter.h`. Functions
      containing logic (like conditions and loops) should
      rather have an implementation outside the class, i.e.
      in a file `Counter.cpp`-file that is compiled
      separately.

* * * * *

Optional:

- Consider the advantages and disadvantages for to implement
  the feature stepping the clock several seconds at once:
    - No arguments to `Count::Counter` it always counts just
      one step up (and falls back to zero when the limit is
      reached).\
       => `Clock::TickUp` needs to use a loop OR\
       => `Clock::TickUp` no longer  supports multiple steps;
    - ALTERNATIVELY: calculate the effective change of
      `value_` AND the count steps to be forwarded to
      `next_counter_`.
- Discuss the advantages and disadvantages of adding more
  member functions like:
    - `GetLimit` - return the value of `limit_`
    - `SetLimit` - change the value of `limit_`
    - `Reset` - reset `value_` to `0` for the counter itself
      AND the whole counter chain connected via `next_` (if
      any).
- Why is it a problem if a `Clock` object gets
  copy-constructed or copy-assigned from an already existing
  ond and how can these (automatically generated) operations
  be avoid?

* * * * *

Unrelated and/or Advanced:

- Devise a way to include the following information in the
  output by using a macro (suggested name `SHOW`):
    - The file name generating the output.
    - The line number in that the macro was invoked.
    - The expression evaluated to produce the output.

- Any other ideas for supporting something like very simple
  "TDD" (= Test Driven Development) approach based on the
  `SHOW` macro?

# Add Testing for class `ClockWork`

At this step a new class `ClockWork` is introdeced which basically
inplement the "Publisher Subscriber" pattern.

* * * * *

If not already done, give its header and implementation file a
short review before continuing.

**Understand that some pieces of its implementation are still
missing and will be addede in later steps.**

* * * * *

The intended use of a `ClockWork` is to "tick up" the registered
`Clock` objects. (In the final version that will be done in a
searate thread.)

To advance to the next step implement more intensive testing.
Some TBD-s have already been prepared in `main.cpp`.

Understand these small pitfalls and obstacles and how to avoid
them:

* An `std::ostringstream os` collects ALL of the input you send
  to it UNLESS you clear it in between.
  * So you have to …
    * … EITHER include all prior output in your expectations
    * … OR use `os.str("")` in between
    * … OR use separate `ostringstream`-s.

* The callbacks will run in no guaranteed particular order by
  `ClockWork::tick()`. so if the callbacks use a single letter
  output to indicate which one has been run, every permutation
  needs to be considered valid for a successful test.

Building on the standard algorithm `std::is_permutation` this
could be tested with the following helper function:

    #include <algorithm>
    bool check_permutation_of(const std::string s1,
                              std::ostringstream& os) {
        const auto s2 = os.str();
        return std::is_permutation(s1.cbegin(), s1.cend(),
                                   s2.cbegin(), s2.cend());
    }

**NOTE:**\
When unit-testing with `SHOW_` you need to test for the
expect result `"true"` as outcome of `check_permutation_of`
(or "1" depending on whether `std::ios::boolalpha` has or
has not been set for `std::cout`.)

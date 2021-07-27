# Understand the Command Loop implemented in `appl`

Review the command loop introduced in this step (instead of
just throwing an exception to indicate the application is
not yet ready for use).

- To test your understanding add some commands.
  - The commands you add are only meant you can SHOW how
    things work.
  - **They should not yet accord to what is already prepared
    and displayed as command menu.**
  - this will be done in the next step.

- What you rather may want to try is adding different KINDS of
  implementation for your "fake", that are all compatible with
  the `std::function` type expected, like:
  - Classic C-style function pointers.
  - C++ functors (= classes overloading the function call operator)
  - C++11 lambdas.

Fill Extension Points via Template Base Class
---------------------------------------------

Compared to the traditional "template methode pattern"
(according to the name chosen by the authors of the widely known
"GoF-Book"), which is filling extension points by overriding
inherited member functions in derived classes, an alternative
technique is shown here:

It is based on calling member functions from a base class which
is specified via a template argument, so that different base
classes can be used for different needs.

In the past this has sometimes been called "inverted template
method pattern" but meanwhile is more often called "policy based
design".

-----------------------------------------------------------------
NOTE: Applying this to the `LimitCounter` / `OverflowCounter`
      example is a little bit more complicated as the simplest
      possible form. Read on, it will be explained now.
-----------------------------------------------------------------

This technique has two possible problems, which are:

(1) If the base class providing the implemenations for the
    extension points needs to have its own (additional) data
    members these must be intialized somehow.

(2) If the base class needs access member data or functions of
    the (now derived) class constituting the "closed" part, it
    can get to them only via down-casts.

There are solutions for both short-commings, which are shown in
the extended solutions.

-----------------------------------------------------------------
NOTE: A detailed discussion of the extended solutions is defered
      until C++ templates are covered in more depth. Feel free to
      have a look in advance but maybe just note your questions,
      they will be answered later.
-----------------------------------------------------------------

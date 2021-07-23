# A Simple Class For Building a Clock

Everything goes into a single class.

Hours, minutes, and seconds are held by separate integers.
Overflow behavior is hard-coded within nested conditionals.

- PRO-s:
  - quickly written
  - easily understood

- CON-s:
  - no reusable components from which the clock is built
  - so the best approach to build similar but not quite
  - identical clocks is
    - (a) copy & paste all of Clock source code
    - (b) then modify what needs to be changed

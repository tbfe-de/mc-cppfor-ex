Fill Extension Points via Template CRTP
---------------------------------------

The basic idea here is the same, ie. filling extension points
from a template, but this case technically is like "a base class
being IMPLEMENTED as derived class at the same time.

NOTE: This technique, also known as CRTP or "Curiously Recurring
      Template Pattern", requires a down-cast at some point, so
      it may be considered as not "quite clean", Though actually
      there is just one line of code to check for a verification
      that all is fine.

TBD: more detailed explanation

+-----------------+
|  <<interface>>  |
|    ICounter     |
+--------.--------+
        /_\
         |
         |
         |    +-----------+
+-------------|  Details  |
|             +-----------+
|  CounterBase    |
+--.-----.--------+
  /_\   /_\
   |     |
   |     | <<bind>> Details = LimitCounter_Details
   |     |
   |  +-----------------+      +-----------------+
   |  |  LimitCounter   |<- - -|  <<C++typedef>> |
   |  |    _Details     |      |   LimitCounter  |
   |  +-----------------+      +-----------------+
   |
   | <<bind>> Details = OverflowCounter
   |
+-----------------+
|                 |
| OverflowCounter |
+-----------------+


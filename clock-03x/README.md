Separate Counting Into Two Classes
----------------------------------

Avoid necessity to give a "hint" via the return value of
`LimitCounter::Count` when an overflow occured so that the
chained counter can count up.

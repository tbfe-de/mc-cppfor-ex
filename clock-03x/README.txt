Separate counting into two classes
----------------------------------

Using references instead of pointers to chain the counters.
Avoid necessity to give a "hint" via the return value of
`LimitCounter::Count` when an overflow occured so that the
chained counter can count up.

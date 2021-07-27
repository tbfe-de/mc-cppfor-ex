# Simplify the code by using `std::unique_ptr`

As `std::unique_ptr` isn't available in C++98 the solution
uses `std::auto_ptr` (deprecated in C++11).

**But `std::auto_ptr` doesn't de-allocate arrays properly!**

**So the solution is in the realm of UNDEFINED BEHAVIOR!**

It still "typically" works only for the fact that type
`char` has no destructor and then again "typically" are no
bad consequence when pairing `new[]` with plain `delete`
(not `delete[]` as it should).

**DO NOT DEPEND ON IT IN THE COMPILE ENVIRONMENT YOU USE!**

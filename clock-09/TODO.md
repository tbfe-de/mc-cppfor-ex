# Cleanup Unit Testing Implementation With `SHOW_`

This is how to proceed:

- Determine which features only work in macros.
- From that determine which arguments a function to replace
  the macro would need to have.
- Understand that one of the arguments varies in type, so
  the function needs to be a template.
- Write a template function `SHOW_helper` according to that
  analysis.
- Keep the macro `SHOW_` to call that function with the
  proper arguments by using the features unique to macro
  expansion.

* * * * *

If you need help, read on below.

**But maybe first on your own.**

* * * * *

Here is what the template function would need to look like.
(Long expressive argument names are used to show the intent.
You may use shorter names in your solution.)

```
template<typename T>
void SHOW_helper(
    const std::string& expectation_string,
    const T& evaluated_expression,
    const char* textual_expression,
    const char* called_by_function,
    int called_at_source_line)
{
    // 
    // TBD
    //
}
```

* * * * *

Optional:

Consider to put the above helper function in an anonymous
namespace. Same for two variables that count the number of
tests and how many tests failed.

Alternatively put all of the above into a class with
`static` members only, maybe together with the function that
shows the summary.

Do you see any chance how the function that shows the summary
might be called automatically, when the `main` program ends?
- For solution with the namespace?
- For the solution with the (all `static` member) class?
- For a solution in which an object of that class is created?
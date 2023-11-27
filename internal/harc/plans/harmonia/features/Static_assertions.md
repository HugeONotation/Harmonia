# Static Assertions
A statement of the form `static_assert(boolean-expression, string-literal);` 
or `static_assert(boolean-expression)` is a static assertion statement.

`boolean-expression` is required to evaluate to `true` at compile time. If 
the expression does not evaluate to true, then the implementation shall 
report an error containing the contents of `string-literal`.

If `boolean-expression` cannot be evaluated at compile time, then the 
implementation shall produce a compilation error.

# Attributes
Attributes may act as hints to the compiler.   
Attributes may also change the semantics of the code.

## Struct Attributes
* packed - indicates that the members of a struct should not have padding. May lower alignment. May rearrange order of memebrs

## Function Attributes
* inline - indicates that a function should be inlined
* pure - indicates that the function does not exhibit external side effects
* deprecated(message) - use of function is discouraged, print message as error
* deprecated(func_ptr) - use of function is discouraged, suggest use of function 
  instead

### Parameter Attriutes
* nonaliasing(param_name) - indicates that the pointer does not alias any other pointer parameters
* nonaliasing(param_name, ...) - indicates that a pointer parameter does not alias with the specified parameter(s)
* synchronous - indicates that the memory referred to by the pointer isn't accessed by other threads

### Return Type Attributes
* discardable - means that discarding a value returned by the function is not problematic

## Alias Attributes
* unique - the alias will be treated as a type separate from the original. Explicit conversion between the two are possible.

## Variable Attributes
* align(isize) - sets the alignment of the variable 
* guard - indicates that a variable value should not be optimized away
* synchronous - indicates that the memory referred to by the pointer isn't accessed by other threads

## Code Block Attributes
* memory_bound - indicate that memory is likely to be a performance issue
* cpu_bound - indicate that processing speed is likely to be a performance issue

## Branch Attributes
* (un)likely - indicates that a branch is likely or not to be taken
* unpredictable - indicates that a branch is not predictable and that branchless types should be favored

## 


# Arrays and Vectors
* the goal will be to provide two abstractions at a language level which
  facilitate the writing of efficient code
* the first would be arrays, which follow the same semantics as arrays in
  mainstream programming languages
* the second would be vectors, which follow a structure of arrays layout
* these layouts could be combined to produce interlaced patterns

* it would be possible to turn a vector member into an array
* there should also be a means to switch between these layouts
* there should be a means to extract structs from a vector

* code is written in a way that it can either apply to an array, a vector, or
  just a scalar
* 

```
let Vector[16] vector; // Follows a AoS layout
let Vector{16} vector; // Follows a SoA layout
```

* construct objects a specific memory address
```
construct ptr Type(constructor_arguments...);
```

* allocate memory
* alignment doesn't apply if done in a vector context
```
allocate<T>(size, alignment)
```

* cli_arguments
    * `in` keyword
    * `out` keyword
    * `inout` keyword

* spans exist at a language-level
* expressed as an array with an asterisk instead of an integer literal
```
i32[*]
```

* pointers will be necessary to interface with C and C++ code
* there will be a system that 

* dynamic enums

## Classes
* 

## Types
* 
*

### Type Specifier
* scalar_type [array specifier]

### Tuples
* tuples are supported at a language level
* any sequence of types may be easily turned into a tuple
* `[type_name, ...]`

## Variable declaration
* declarations of constants begins with the `let` keyword
* declarations of variables begins with the `var` keyword
* `key_word [type_specifier] variable_name = initializer`
* the type specifier can be avoided if the type can be inferred from the initialization

## Function Declarations
```
func
[[annotations...]]
function_name(argument_declarations) return_type
```
* the program will require that the organ 

### Function Annotations
* `throws exception`
* `discardable`
* `inline`
* ``

## Structures
* structures are analogous to structs and classes in OO languages

### Struct Annotations
* `alignment`
* `pack`

* places into [[]]
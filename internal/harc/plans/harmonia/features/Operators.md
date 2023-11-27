# Operator
Harmonia allows for overloading a variety of operators

## Arithmetic operators
### Addition
`operator+(param, param)`

### Subtraction
`operator-(param, param)`

## Logical operators
### Logical not
`operator!(param)`

### Logical and
`operator&&(param, param)`

### Logical nand
`operator!&&(param, param)`
May be defaulted if logical not and logical and operator is overloaded

### Logical or
`operator||(param, param)`

### Logical nor
`operator!||(param, param)`
May be defaulted if logical not and logical or operator is overloaded

### Logical xor
`operator^^(param, param)`

### Logical xnor
`operator!^^(param, param)`
May be defaulted if logical not and logical xor operator is overloaded

## Bitwise operators
### Bitwise not
`operator~(param)`

### Bitwise and
`operator&(param, param)`
May be defaulted if bitwise not and bitwise or operators are overloaded

### Bitwise nand
`operator~&(param, param)`
May be defaulted if bitwise not and bitwise and operators are overloaded

### Bitwise or
`operator|(param, param)`
May be defaulted if bitwise not and bitwise and operators are overload

### Bitwise nor
`operator~|(param, param)`
May be defaulted if bitwise not and bitwise or operators are overloaded

### Bitwise xor
`operator^(param, param)`

### Bitwise xnor
`operator~^(param, param)`
May be defaulted if bitwise not and bitwise xor operators are overloaded

## Misc. Operator

### Member Access Operator
`operator.<TEXT>()`

### Address of Operator
`operator&(param)`

### Pointer Dereference Operator
`operator->(param)`

### Function Call Operator
`operator()(params...)`

### Subscript Access Element
`operator[](params...)`

### Subscript Create View
`operator[:](param0 = 0, params1 = length(*this))`

### Unpack
`operator [Type, ...](*this)`
* actually just a conversion to tuple type
* in order to apply, the conversion must be implicit

### Assignment Operator
`operator=(param)`
* assigment from parameter

### Conversion Operator
`operator Type(*this)`
* may have the `implicit` attribute 

# Layouts
* layouts take in an struct object
  * a list of member variables
  * each field will have an alignment requirement and a size requirement
* there would be two different categories of layouts: scalar and array layout
* 

## Array of Structures

## Structure of Arrays

## Array of Structure of Arrays
* for an optimal implementation, the cache line size (or a reasonable 
  estimate) must be known
* 

## Custom layouts
* custom layouts could be created by defining a new Layout which implements 
  the std.Layout trait
* this means s
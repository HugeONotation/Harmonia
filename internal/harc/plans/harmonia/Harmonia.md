# Harmonia
Harmonia is a systems programming language which is meant to facilitate the 
writing of efficient code that leverages vectorization in a way that is easy,
and portable. The language also seeks to be more modern than C and C++.

The language seeks to make the writing oc code which is SIMD vectorized 
easier in nature. 


## Memory Layout
### Array of Structures
`xyz|xyz|xyz|...`
* this is the format which is expected by most APIs
* it interacts besst with scalar code that needs to access multiple members 
* this is the approach that most programming languages favor

## Structure of Arrays
`xxxxxx|yyyyyy|zzzzzz`
* this allows for the individual members to be stored as arrays
* accessing one member will lead to ideal memory access patterns
* accessing multiple members may lead to slightly suboptimal memory access 
  patterns
* processing a single element is likely to be inefficient since for large 
  arrays, the elements will not be found in a single cache line

## Hybrid Approach
`xxxxyyyyzzz|xxxxyyyyzzzz|xxxxyyyyzzzz|...`
* friendly for SIMD vectorization
* can easily be made so that individual loads are always aligned
* processing a single element is suboptimal since the data may need to eb 
  read from multiple contiguous cache lines

## Processing Arrays
* ideally, any operation that could be applied to an object of type T, could 
  also be applied to arrays of objects of type T, however, this is not 
  always possible. A subset of vectorizable functions must be defined.
* vectorizable functions may not
  * make function calls via function pointers
  * make calls to non-vectorizable functions
  * throw exceptions
  * use if statements (could be relaxed)
  * use for loops (could be relaxed)
  * use while loops (could be relaxed)
  * use goto
  * use switch statements
  * allocate memory (could theoretically be relaxed with work)
  * deallocate memory (could not be relazed)
  * taking the address of this
  * 
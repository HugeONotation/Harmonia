# Function CLI_arguments
* parameters may be marked using one fo the keywords `in`, `out` or `inout`
* if none of these are used then `in` is implicitly used
* the actual method of passing the objects will be determined by the compiler
* `in` parameters
  * lighter objects may be passed by value
  * heavier objects may be passed by const reference
* `out` parameter
  * objects are always passed by reference
  * if object is not written to, a warning is emitted
* `inout` parameter
  * objects always passed by reference
  * if object is not written to, a warning is emitted
* however, this does produce a difference in observable behavior that's evident with multi-threaded code
  * in particular, when the program is multithreaded, a race condition may occur if another object accesses the 
    object which is passed by reference to the function being evaluated by the current thread 
  * this race condition does not occur when the object is passed by value
* one possible solution would be to simply present the observable behavior of passing by const reference as much as 
  possible, thereby requiring that if the user want the race condition to definitely not occur, an explicit copy 
  must be made

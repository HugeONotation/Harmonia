# Exceptions
* one problem with C++'s exceptions is that the support dynamic types
* one possible solution would be to constrain throwable types to a particular interface
* 
* when a try block in entered, a function pointer and typeid could be emplaced into a stack of handlers
* when an exception is thrown, a simple linear scan backwards through the stack could be used to identify the 
  appropriate handler
* there would also be a need to perform stack unwinding and return from functions however
* 
# Assumptions
A statement of the form `assume boolean-expression ;` is an assumption 
statement.

An assumption statement is a means to inform the implementation that it should 
assume that `boolean-expression` will always evaluate to `true` and optimize
accordingly.

If `boolean-expression` cannot be evaluated at compile time, then the 
implementation shall produce a compilation error.

## Program Behavior
If the implementation can determine that the provided expression does not 
evaluate to true, then the implementation is obligated to report a 
compilation warning. 

If the expression specified in an assumption statement is not true in practice, 
then the implementation is not required to ensure the correctness of the 
resulting program. However, the behavior of any portion of the 
program/subroutine where the assumption is irrelevant should be unaffected by 
the false assumption.

## Scope
The effects of an assumption declared in a trait shall affect all classes that 
implement the trait.

The effects of an assumption shall not escape any code block in which it may 
have been declared.

The effects of an assumption shall not escape the class in which it was 
declared.

The effects of an assumption shall not escape the module in which it was 
declared.

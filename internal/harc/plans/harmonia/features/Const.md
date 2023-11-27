# Const
Harmonia shall support three degrees of constness for its references and 
objects.

## Strong Const
Strong const references refer to values which are constant in the mathematical 
sense. These values do not change throughout the entire lifetime of the object.

Strong const may be applied to objects whose values are known at compile 
time or to objects which are initialized once, but whose bitwise representation 
are guaranteed to remain the same until they are destroyed.

Strong const object may be accessed from multiple threads without 
synchronization.

## Moderate Const
Moderate const references refer to values which are never modified by the 
subroutine. The reference shall not be used to perform any operation which 
emits a write operation that targets any bytes participating in the 
representation of the referenced object.

Moderate const may be applied to objects which .

Moderate const references may reference objects regardless of their inherent 
constness.

## Weak Const
Weak const references refer to values which may be .

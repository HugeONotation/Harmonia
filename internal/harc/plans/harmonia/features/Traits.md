# Traits
Traits are a means to create categories of interfaces to which classes may 
adhere.

Class may implement multiple traits so long as there is no conflict in the 
public interface which they present. 

Traits may extend from other traits.

## Standard Traits
## Convertable<T>

## Incrementable
## Decrementable

## Addable
## Subtractable

## Comparable

## Partially_ordered
* implies comparable
## Totally_ordered
* implies Ordered

## Functor
## Unary_predicate
## Binary_predicate
## 

## Arithmetic

### Integral
### Signed_integral
* implies Integral

### Unsigned_integral
* implies Unsigned_integral

### Fixed_point
### Floating_point

### Smart_pointer
### Pseudo_Reference

### Allocator

### Forward_iterator
* implies Incrementable
* `reference operator*(auto this)`
* 
### Bidirectional_iterator
* implies Decrementable

### Random_access_iterator
* implies subscriptable

### Forward_range
* 
### Bidirectional_range
* implies Forward_range
### Random_access_range
* implies Bidirectional_range

### Lockable
### Clock
# Type Augmentations
## Arrays
Contiguous allocations of multiple objects of the same type

## References


## View Pointers
## Owning Pointers
## View Spans
## Owning Spans
## Tuple
`[Type0, ...]` will evaluate to a tuple of the specified types
`[expression, expression]` will evaluate to a tuple of the specified objects
`*tuple_object` will expand the tuple, e.g. decay to `obj0, ...`
`tuple_object as Type[]` will transform the tuple into an array if the individual components can be converted to Type
`tuple_object<0>` will get the

## Optional
## Any
## Variant
## Expect
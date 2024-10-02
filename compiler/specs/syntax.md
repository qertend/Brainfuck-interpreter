# Brainfucked

C-like syntax, except types are not a thing, because everything is a byte(multi-byte types in the future, maybe)

### var
> var varName [= initialValue];

declare a new variable. Compiler should allocate a new cell for the variable
#const will not be a thing, because we have to temporarily modify the var to copy it to other cells
#therefore, it is the programmers responsibility to treat the var as a constant

### arithmetic
> [varA = ] a + b; a- b; a * b;

the result should be stored in a temporary variable until further use
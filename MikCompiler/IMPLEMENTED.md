# 1. Variables assignment and Use of variables in expressions
  Implemented simple variable assignment. Typecast and Advanced type checking are implemented.
  
  Arrays and Bounds as well as custom guards (a simple code block, that is executed, when the variable is changed) are NOT yet implemented

# 2. Expressions
Implemented expressions. Expressions support
	
    - Binary operators
    - Unary operators
	
## 2.1 Factors
A factor can either be:
	
	- A constant
		- strings ("a")
		- a character ('c')
		- integers (5)
		- floats (0.5)
	- Variables
		- singla (a)
		- array (a[0])
	- Function calls
		- funciton call like (foo() / foo(a,b,...))
	- Typecasts
		- (\<factor\>) ->  \<type\>: Expressions have to be in parenthesis
		- Note: the type converted to must have a defined type cast function from the type of factor to the type converted to
	
Everything but array acces is already implemented

# 3. Re-Assignment
Variables can now be reassigned!

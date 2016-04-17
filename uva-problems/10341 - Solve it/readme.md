# UVa 10341 Problem

## About the Implementation
The code includes Bisection Method and Secant Method's implementation to solve an equation following this form: f(x) = 0. 
Although I've used the second method, because it's faster than the first one, I leave both implementations in the code, so it's possible to compare the number of iterations needed to converge to the solution by using these two methods.
By the way, both were accepted by UVa.

## Comparing Bisection and Secant Methods
For the test, I used epsilon = 1e-7, X0 = 0 and X1 = 1 (Secant method).
For the provided input (in.in) I've got:

| Input	         | Output        | # Iterations Bisection | # Iterations Secant	   |
| -------------- |:-------------:|:----------------------:| ----------------------:|
| 0 0 0 0 -2 1   | 0.7071 		 | 24					  | 7					   |
| 1 0 0 0 -1 2	 | No solution   | --			 		  | --					   |
| 1 -1 1 -1 -1 1 | 0.7554 	     | 24 		 			  | 6					   |
| 0 0 0 0 -1 1	 | 1.0000 	     | 24 		 			  | 1					   |
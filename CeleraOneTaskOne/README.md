Exercise 1
==========

* Consider the following recursively defined function

- f(0) = 1
- f(1) = 1
- f(2n) = f(n)
- f(2n+1) = f(n) + f(n-1)

* Write a program in C++ that computes f(n) for a given n by directly
applying the recursion relation. Compute f(123456789012345678). Pay
attention to not doing integer overflows.
* Measure the wall-clock time it takes the program to run. Use e.g.
the command 'time'. On my machine when compiled with -O3, the program
takes around 13 secs.
* Optimize the code so that it runs faster. It's ok to make a reasonable
tradeoff with memory. The runtime goal should be in the millisecond
regime.

# Solution
## Observation
When replacing the value of n with an integer in the above listed functions, we get following results
- f(0) = 1
- f(1) = 1
- f(2) = f(1) = 1
- f(3) = f(1) + f(0) = 2
- f(4) = f(2) = 1
- f(5) = f(2) + f(1) = 2
- f(6) = 2
- f(7) = f(3) + f(2) = 3
- f(8) = f(4)  = 1
- f(9) = f(4) + f(3) = 3
- f(10) = f(5) = 2
- and so on ..

## Linux build
Steps to make the project
* cd project_dir
* make

# Notes
On building and running the project on my Linux machine the 120 - 200 microseconds with -O0. So wall-clock time is displayed in microseconds.












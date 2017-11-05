The objectives of this assignment are to write a program to compute the product of two dense
matrices, C = A × B, and to understand the computational performance of your program. You are
provided with a template source code that details the structure of the program. You should not
modify any of the function prototypes already provided, but you can definitely add some more to
help you organize your code even further. You can get information about how the program can
be run by simply running your executable without any command-line inputs.

1. Implement the function with the prototype
double **malloc_matrix(int n1, int n2);
This function creates a two-dimensional matrix using dynamic memory allocation (use
the built-in C function malloc() for this purpose) and returns a pointer to the structure
that was created. The created matrix has n1 rows and n2 columns. Each element of the
matrix is a floating point, double precision number. The matrix must be structured using
the array of pointers representation, i.e., the data for the two-dimensional matrix is stored
in a set of one-dimensional arrays, one array for each row of the matrix, and an
additional, separate one-dimensional array with each array element containing a pointer
to the data for a single row. The function returns NULL if the operation failed, e.g., due to
insufficient memory.

2. Implement the function with the prototype
void free_matrix (int n1, int n2, double **a);
Release the memory allocated for the matrix pointed to by a which has n1 rows and n2
columns. Use the built-in C function free() to release a block of memory.

3. Implement the function with the prototype
int matrix_multiply(int n1, int n2, int n3,
double **a, double **b, double **c);
The matrix A is stored in a and has dimensions n1 by n2, and the matrix B is stored in b
and has dimensions n2 by n3. When your function returns, the product C = A × B is
stored in matrix c. Your function should return 0 if the computation was successful, and
nonzero otherwise (e.g., n1 is negative, a==NULL, or any other invalid condition). From
the function prototype above, note that memory for the arrays must be allocated outside
the matrix_multiply function.

4. Implement the function with the prototype
void fill_matrix(int n1, int n2, double **a);
that fills the matrix a with random values between 0 and 100.

5. Implement the function with the prototype
void print_matrix(int n1, int n2, double **a);
that prints the matrix a in a readable format (i.e., columns are aligned).

6. Implement the function with the prototype
void matrix_test(int n1, int n2, int n3);
that calls the above three functions (use this to test your functions). In particular, choose
A as a 4 × 3 matrix, and B as a 3 × 2 matrix. For this case, print A, B, C and hand in your
results. Also hand in evidence that you checked that C is correct, e.g., a Matlab script that
shows the same computation and results.
This function will be called by running your program with the command line input “q6”
(see usage message).

7. Implement the function with the prototype
int get_avg_runtime(int n1, int n2, int n3, int
numberOfRepeats, double *avgRuntime);
that outputs the average time for computing one matrix multiply. The pseudocode for this
program should look like this:
matrix_fill_random(A)
matrix_fill_random(B)
 start timer
 loop a large number of times
 C = A*B
 endloop
 stop timer
 *avgRuntime = average time for one matrix multiply
The reason for the loop above is to average out any startup effects (i.e., this “warms up”
the caches). The function returns 0 if the computation is successful, and non-zero
otherwise.
This function will be called by running your program with the command line input “q7”
(see usage message).

8. Implement the function with the prototype
int runtime_vs_size(int n_min, int n_max, int n_step,
int numberOfRepeats);
that calls the get_avg_runtime function using square matrices, where the size along one
dimension (N) of the matrices increases to as large as your machine can handle. Plot the
average time as a function of N. Does the curve follow a shape that you expect? Provide
an explanation of your results.
This function will be called by running your program with the command line input “q8”
(see usage message).

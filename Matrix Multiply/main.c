//
//  main.c
//  CX-4641 Assignment1
//
//  Created by Karl Gemayel on 8/17/17.
//  Copyright © 2017 Karl Gemayel. All rights reserved.
//
//  Student name: Thomas Hervieu
//  Student username: thervieu3

#include <stdio.h>
#include <stdlib.h>     // for rand, srand
#include <time.h>       // for time, clock
#include <string.h>     // for strncmp

#define MODE_Q6 "q6"
#define MODE_Q7 "q7"
#define MODE_Q8 "q8"

// Function Prototypes: generic
void usage(const char *programName);
int get_avg_runtime(int n1, int n2, int n3, int numberOfTries, double *avgRuntime);

// Function Prototypes: mode specific
int run_mode(const char *mode, int argc, const char *argv[]);
int run_mode_q6(int argc, const char *argv[]);
int run_mode_q7(int argc, const char *argv[]);
int run_mode_q8(int argc, const char *argv[]);
int matrix_test(int n1, int n2, int n3);
int runtime_vs_size(int n_min, int n_max, int n_step, int numberOfRepeats);

// Function Prototypes: matrix specific
double**    malloc_matrix   (int n1, int n2);
void        free_matrix     (int n1, int n2, double **a);
int         matrix_multiply (int n1, int n2, int n3, double **a, double **b, double **c);
void        fill_matrix     (int n1, int n2, double **a);
void        print_matrix    (int n1, int n2, double **a);




// Main function
int main(int argc, const char * argv[]) {

    // Start by reading the input from the command line prompt.
    // Note: when no additional arguments are passed through the
    // the command prompt, argc equals 1, and argv[0] is the
    // name of our executable file.

    // In this case, the program takes in at least one additional
    // argument, which is the mode (i.e. what test will we be running)

    if (argc < 2) {
        usage(argv[0]);
        return 1;
    }

    const char *mode = argv[1];             // what mode the program will run in
    srand(time(NULL));
    int rv = run_mode(mode, argc, argv);

    printf("Program ran ");
    if (rv == 0)
        printf("successfully!\n\n");
    else
        printf("unsuccessfully!\n\n");

    return 0;

}

/**
 * Print out the usage message.
 *
 * @param programName the name of the executable file.
 */
void usage(const char *programName) {
    printf("usage: %s mode [OPTIONS]\n", programName);
    printf("  mode: this parameter defines the mode that the\n");
    printf("        program will run in.\n");
    printf("        The mode can take one of several values:\n");
    printf("            %s: part 6 of assignment\n", MODE_Q6);
    printf("            %s: part 7 of assignment\n", MODE_Q7);
    printf("            %s: part 8 of assignment\n", MODE_Q8);

    printf("\nUsage for %s:\n", MODE_Q6);
    printf("%s %s n1 n2 n3\n", programName, MODE_Q6);
    printf("  where:\n");
    printf("    n1      : number of rows in A\n");
    printf("    n2      : number of columns (rows) in A (B)\n");
    printf("    n3      : number of columns in B\n");

    printf("\nUsage for %s:\n", MODE_Q7);
    printf("%s %s n1 n2 n3 repeats\n", programName, MODE_Q7);
    printf("  where:\n");
    printf("    n1      : number of rows in A\n");
    printf("    n2      : number of columns (rows) in A (B)\n");
    printf("    n3      : number of columns in B\n");
    printf("    repeats : number of times multiplication is repeated (for averaging)\n");

    printf("\nUsage for %s:\n", MODE_Q8);
    printf("%s %s n-min n-max n-step repeats\n", programName, MODE_Q7);
    printf("  where:\n");
    printf("    n-min   : minimum square matrix dimensionality\n");
    printf("    n-max   : maximum square matrix dimensionality\n");
    printf("    n-step  : step-size between consecutive square matrix dimensionalities\n");
    printf("    repeats : number of times multiplication is repeated (for averaging)\n");

    printf("\n");
}

/**
 * Run the program in a certain mode. The modes that are allowed
 * are defined by the macros with prefix "MODE_"
 *
 * @param mode the requested mode
 * @param argv the arguments provided at runtime
 *
 * @return 0 for success; non-zero for fail
 */
int run_mode(const char *mode, int argc, const char *argv[]) {

    int return_value = 0;

    if (strncmp(mode, MODE_Q6, 100) == 0) {             // run mode MODE_Q6
        printf("Running mode %s:\n\n", mode);
        return_value = run_mode_q6(argc, argv);

    }
    else if (strncmp(mode, MODE_Q7, 100) == 0) {        // run mode MODE_Q6
        printf("Running mode %s:\n\n", mode);
        return_value = run_mode_q7(argc, argv);
    }
    else if (strncmp(mode, MODE_Q8, 100) == 0) {        // run mode MODE_Q6
        printf("Running mode %s:\n\n", mode);
        return_value = run_mode_q8(argc, argv);
    }
    else {                                              // mode is invalid
        printf("Error: Mode \"%s\" is invalid.\n", mode);
        return_value = 1;
    }

    return return_value;
}


/****** Matrix Specific Functions ******\
 *                                     *
 * These functions define what matrix  *
 * operations can be performed.        *
 *                                     *
 \***************************************/


/**
 * Allocate memory for a 2D matrix
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @return a pointer to the matrix
 */
double **malloc_matrix(int n1, int n2) {
    double **mat = NULL;       // pointer to the matrix


    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update the 'mat' variable

    //Checking for invalid inputs
    if (n1 <= 0 || n2 <= 0) {
    	printf("Invalid Inputs!");
    	return mat;
    }

    //creating array of pointers
    mat = (double**) malloc(sizeof(double*) * n1);

    //allocating memory for row of each pointer in pointer array
    for (int i =0; i < n1; i++) {
    	mat[i]= (double*) malloc(sizeof(double) * n2);
    }

    return mat;
}


/**
 * Free the space allocated for the matrix.
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void free_matrix(int n1, int n2, double **a) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!

	//checking for invalid inputs
	if (n1 <= 0 || n2 <= 0 || a == NULL) {
		printf("Invalid Inputs!");
	}

	//free up space for each row in RAM since desired results have been achieved
	for (int i = 0; i < n1; i++) {
		free(a[i]);
	}

	free(a); //free up space of pointer array in RAM
}

/**
 * Multiplies two matrices and puts the result in a third, i.e. C = A*B
 * @param n1 the number of rows in matrix A
 * @param n2 the number of columns in matrix A, and rows in matrix B
 * @param n3 the number of columns in matrix B
 * @param a the pointer to matrix A
 * @param b the pointer to matrix B
 * @param c the pointer to matrix C
 * @return zero if the computation was successfully, and nonzero otherwise
 */
int matrix_multiply(int n1, int n2, int n3, double **a, double **b, double **c) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update return value

	//checking for invalid inputs
	if(n1 <= 0 || n2 <= 0 || n3 <= 0 || a == NULL || b == NULL || c== NULL) {
		return 1;
	}


	int i,j,k;

	//for-loops through matrices and takes their dot- product for matrix multiplication
	for(k=0; k < n3; k++) {
		for (i = 0; i < n1; i++){
			c[i][k] = 0;
			for(j =0; j < n2; j++){  //an entire loop of this constitutes one entry in the new matrix
				c[i][k]+= a[i][j]*b[j][k];
			}
		}
	}

	return 0;
}

/**
 * Fill the matrix with random values between 0 and 100
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void fill_matrix(int n1, int n2, double **a) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!

	//checking for invalid inputs
	if(n1 <= 0 || n2 <= 0 || a == NULL){
		printf("Invalid Inputs!");
	}

	//assigning values to matrix
	int i, j;
	for(i = 0; i < n1; i++){
		for(j = 0; j < n2; j++){
			a[i][j] = rand() % 100; //assign random numbers 1-100
		}
	}
}

/**
 * Print the matrix to standard output
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @param a the pointer to the matrix
 */
void print_matrix(int n1, int n2, double **a) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!

	//checking for invalid inputs
	if ( n1 <= 0 || n2 <= 0) {
		printf("Invalid Inputs!");
	}

	//prints out each entry in a row
	int i, j;
	for(i = 0; i < n1; i++) {
		for(j = 0; j < n2; j++){
			printf("%f  ", a[i][j]);
		}
		puts(""); //break line after end of each row
	}
}


/****** Mode Specific Functions ******\
 *                                   *
 * These functions define what modes *
 * the program can run in.           *
 *                                   *
\*************************************/

/**
 * Run Q6 of the assignment. Do the following:
 * 1) Generate two random matrices A and B (of type float) where
 *    the matrix dimensions are defined as command-line arguments.
 * 2) Compute C = A x B
 * 3) Print A, B, and C
 *
 * @param argc the number of command-line arguments
 * @param argv the command-line arguments
 * @return 0 for success; non-zero for fail
 */
int run_mode_q6(int argc, const char *argv[]) {
	printf("Func: run_mode_q6");

    if (argc != 5) {
        printf("Error: Mode \"%s\" requires 3 additional input arguments.\n", MODE_Q6);
        return 1;
    }

    int rv = 0;                 // function return value
    // parse command-line-arguments
    int n1 = (int) strtol(argv[2], NULL, 10);      // convert n1 from string to int
    int n2 = (int) strtol(argv[3], NULL, 10);      // convert n2 from string to int
    int n3 = (int) strtol(argv[4], NULL, 10);      // convert n3 from string to int
    puts("");
    printf("Running Matrix Test!");
    puts("");
    rv = matrix_test(n1, n2, n3);

    return rv;
}

/**
 * Run Q7 of the assignment. Do the following:
 * 1) Generate two random matrices with user-specified dimensions.
 * 2) Compute the average runtime of their multiplication
 *
 * @param argc the number of command-line arguments
 * @param argv the command-line arguments
 * @return 0 for success; non-zero for fail
 */
int run_mode_q7(int argc, const char *argv[]) {
    if (argc != 6) {
        printf("Error: Mode \"%s\" requires 4 additional input arguments.\n", MODE_Q7);
        return 1;
    }

    int rv = 0;                 // function return value

    // parse command-line-arguments
    int n1 = (int) strtol(argv[2], NULL, 10);               // convert n1 from string to int
    int n2 = (int) strtol(argv[3], NULL, 10);               // convert n2 from string to int
    int n3 = (int) strtol(argv[4], NULL, 10);               // convert n3 from string to int
    int numberOfRepeats = (int) strtol(argv[5], NULL, 10);  // convert number-of-repeats from string to int

    double avgRuntime = 0;         // the average runtime
    rv = get_avg_runtime(n1, n2, n3, numberOfRepeats, &avgRuntime); // reference (&avgRuntime) is used so that this value can be filled by get_arg_runtime(...)

    // if run was successful
    if (rv == 0) {
        printf("The average runtime per matrix multiply is %.3f seconds\n", avgRuntime);
    }

    return rv;
}




/**
 * Run Q8 of the assignment. Do the following:
 * 1) Generate matrices of increasing dimensionality
 * 2) Compute the average runtime of each of their multiplication
 *
 * @param argc the number of command-line arguments
 * @param argv the command-line arguments
 * @return 0 for success; non-zero for fail
 */
int run_mode_q8(int argc, const char *argv[]) {
    if (argc != 6) {
        printf("Error: Mode \"%s\" requires 4 additional input arguments.\n", MODE_Q8);
        return 1;
    }

    int rv = 0;                 // function return value

    // parse command-line-arguments
    int n_min   = (int) strtol(argv[2], NULL, 10);               // convert n-min  from string to int
    int n_max   = (int) strtol(argv[3], NULL, 10);               // convert n-max  from string to int
    int n_step  = (int) strtol(argv[4], NULL, 10);               // convert n-step from string to int
    int numberOfRepeats = (int) strtol(argv[5], NULL, 10);       // convert number-of-repeats from string to int

    rv = runtime_vs_size(n_min, n_max, n_step, numberOfRepeats);

    return rv;
}



/**
 * Do the following:
 * 1) Generate two random matrices A and B (of type float) where
 *    the matrix dimensions are defined as command-line arguments.
 * 2) Compute C = A x B
 * 3) Print A, B, and C
 *
 * @param n1 the number of rows in matrix A
 * @param n2 the number of columns in matrix A, and rows in matrix B
 * @param n3 the number of columns in matrix B
 * @return zero if the computation was successful, and nonzero otherwise
 */
int matrix_test(int n1, int n2, int n3) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update the return value depending on success/failure
	//Generate two random matrices, A and B, respectively.

	//Checking for invalid inputs
	if(n1 <= 0 || n2 <= 0 || n3<=0) {
		printf("Invalid dimensions!");
		return 1;
	}

	//allocating memory for 3 matrices we are going to work with
	double** a = malloc_matrix(n1,n2);
	double** b = malloc_matrix(n2,n3);
	double** c = malloc_matrix(n1,n3);

	//fills a and b with values. c remains empty because it will be filled by matrix multiplication.
    fill_matrix(n1,n2,a);
    fill_matrix(n2,n3,b);

    //Matrix multiplication.
    matrix_multiply(n1,n2,n3,a,b,c);

    //Print matrices a,b, and c.
    printf("Matrix A");
    puts("");
    print_matrix(n1,n2,a);
    puts("");

    printf("Matrix B");
    puts("");
    print_matrix(n2,n3,b);
    puts("");

    printf("Matrix C");
    puts("");
    print_matrix(n1,n3,c);

    //free up the spaces occpied by each matrix because we ave achieved our desired result.
    free_matrix(n1,n2,a);
    free_matrix(n2,n3,b);
    free_matrix(n1,n3,c);

    return 0;
}



/**
 * Get the average runtime (in seconds) of the matrix multiplication C = AxB, repeated several times.
 *
 * @param n1 the number of rows in matrix A
 * @param n2 the number of columns in matrix A, and rows in matrix B
 * @param n3 the number of columns in matrix B
 * @param numberOfRepeats the number of times the matrix multiplication is repeated
 * @param avgRuntime an output variable to hold the average runtime (in seconds)
 * @return zero if the computation was successful, and nonzero otherwise
 */
int get_avg_runtime(int n1, int n2, int n3, int numberOfRepeats, double *avgRuntime) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update the return value depending on success/failure
    // - update the avgRuntime variable to account for the runtime

	//checking for invalid inputs
	if(n1 <= 0 || n2 <= 0 || n3 <=0 || numberOfRepeats <= 0 || avgRuntime <=0) {
		printf("Invalid Inputs!");
		return 1;
	}

	//initialize clock params
	clock_t begin;
	clock_t end;

	//allocate memory four our matrices a,b, and c in RAM
	double** a = malloc_matrix(n1,n2);
	double** b = malloc_matrix(n2,n3);
	double** c = malloc_matrix(n1,n3);

	//Fill up our matrices a and b with random values 1-100. c will be calculated from a and b.
	fill_matrix(n1,n2,a);
	fill_matrix(n2,n3,b);

	//Begin timer
	begin = clock();

	//Conduct Matrix Multiplications numberOfRepeats times while timer is on.
	for (int i = 0; i < numberOfRepeats; i++) {
		matrix_multiply(n1,n2,n3,a,b,c);
	}

	//End timer
	end = clock();

	//calculate average time for all matrix multiplications
	//CLOCKS_PER_SEC used to convert difference in time to seconds.
	*avgRuntime= (double) (end - begin)/(CLOCKS_PER_SEC * numberOfRepeats);

	//free up space used by the matrices in RAM.
	free_matrix(n1,n2,a);
	free_matrix(n2,n3,b);
	free_matrix(n1,n3,c);

    return 0;

}


/**
 * Benchmark matrix multiplication for different sized matrices
 * 1) Generate matrices of increasing dimensionality
 * 2) Compute the average runtime of each of their multiplication
 *
 * @param n_min minimum matrix dimension
 * @param n_max maximum matrix dimension
 * @param n_step step-size between matrix dimensions
 * @param numberOfRepeats the number of times a multiplication is run for each matrix size
 * @return 0 for success; non-zero for fail
 */

int runtime_vs_size(int n_min, int n_max, int n_step, int numberOfRepeats) {

    // TODO: Your code here. Don't forget to:
    // - check for invalid inputs!
    // - update the return value depending on success/failure
    // - Hint: look at the implementation for run_mode_q7

	//checking for invalid inputs
	if (n_min <= 0 || n_max <= 0 || n_step <= 0 || numberOfRepeats <= 0) {
		return 1;
	}

	//allocate memory to create a single array
	double* a = (double*) malloc(sizeof(double)*(n_max - n_min));

	//testing average run-times for matrices with changing dimensions
	int i;
	for (i = n_min; i < n_max; i += n_step){
		double avgRuntime = 0;
		get_avg_runtime(i, i, i, numberOfRepeats, &avgRuntime); //dimensions i,i,i increase
		a[i] = avgRuntime; //assigning the average runtime from function call to array a
		printf("%g", avgRuntime);
		puts(""); //line break between each step to distinguish different runtime for each matrix of changing size.
	}

    return 0;
}

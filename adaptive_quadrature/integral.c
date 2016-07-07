#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi/mpi.h>

#define STACK_SIZE 1024

// Partial integral strcuture.
struct partial_integral_s {
    double a; // Lower bound.
    double b; // Upper bound.
};
typedef struct partial_integral_s partial_t;

// Function to integrate.
double f(double x);

// Function to apply the Simpson's rule for approximation:
// (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b))
// Creates a parabolic curve.
// a = lower bound, b = upper bound, f = function.
double simpson_rule(double a, double b, double (*f)(double));

// Funcion to integrate a function with a specified precision.
// Implemented as a stack.
// a = lower bound, b = upper bound, f = function, e = error for result.
double integrate(double a, double b, double (*f)(double), double e);
// Funcion to integrate a function with a specified precision.
// Implemented recursively.
double integral_recursive(double a, double b, double (*f)(double), double e);

int main(int argc, char ** argv) {
    int N = 1;
    if (argc < 2 || argc > 5) return 1;
    // Number of threads needed
    N = atoi(argv[1]);
    // Number of processes and a current rank indicator
    int num_procs, my_rank;
    // Bounds, Error and a range for each of the processes
    double A = atof(argv[2]), B = atof(argv[3]), e = atof(argv[4]), dx = fabs(B - A) / N;
    // Result of integration
    double result = 0;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Find out rank, size
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    double partial_result = integrate(A + my_rank * dx, A + (my_rank + 1) * dx, f, e);
    // Master rank
    if (my_rank == 0) {
        result = partial_result;
	    int slave_rank;
	    for (slave_rank = 1; slave_rank < num_procs; slave_rank++) {
	        MPI_Recv(&partial_result, 1, MPI_DOUBLE, slave_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	        result += partial_result;
	    }
    // Slave rank
    } else {
        MPI_Send(&partial_result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double end = MPI_Wtime();

    // Destroy the MPI environment
    MPI_Finalize();

    if (my_rank == 0) {
	    printf("%d procs: \n", N);
        printf("Integral: %.16f\n", result);
	    printf("Duration: %.16f\n", end - start);
    }

    return 0;
}

double f(double x) {
   return sin(x) + 10;
   // return 4 / (1 + x * x); // Integrated in [0;INF) ~ 2*PI
   // return cos(x) + sin(50/(1 + x * x)) + 2;
}

double simpson_rule(double a, double b, double (*f)(double)) {
    return fabs(b - a) / 6 * (f(a) + 4 * f((b + a) / 2) + f(b));
}

double integrate(double a, double b, double (*f)(double), double e) {
    // Total integral sum
    double total_sum = 0;
    // Create a stack for calculations
    partial_t* stack = (partial_t*) malloc(STACK_SIZE * sizeof(partial_t));
    // Stack top pointer
    int stack_top = 0;

    // Push the initial state on stack
    stack[stack_top].a = a;
    stack[stack_top].b = b;
    stack_top++;

    // While there are elements on stack
    while (stack_top > 0) {
        // If the stack size is exceeded, reallocate
        if (stack_top % STACK_SIZE == STACK_SIZE - 1) {
            stack = (partial_t*) realloc(stack, STACK_SIZE * (stack_top + sizeof(partial_t)));
        }

        // Get the stack top and save this state as current
        stack_top--;
        a = stack[stack_top].a;
        b = stack[stack_top].b;

        // Calculate the middle point of a current state
        double c = (b + a) / 2;
        // Calculate the approximate area of a current state
        double shallow_estimate = simpson_rule(a, b, f);
        // Calcuate the approximate area of a state ahead
        double deepper_estimate = simpson_rule(a, c, f) + simpson_rule(c, b, f);

        // If the current state area and the next state area difference
        // is smaller than a specified error, the partial sum is done.
        if (fabs(shallow_estimate - deepper_estimate) < e) {
            total_sum += deepper_estimate;
        } else {
            // Push the next state with the interval divided into two
            stack[stack_top].a = a;
            stack[stack_top].b = c;
            stack_top++;

            // Push the next state with the interval divided into two
            stack[stack_top].a = c;
            stack[stack_top].b = b;
            stack_top++;
        }
    } // End of while
    return total_sum;
}

double integral_recursive(double a, double b, double (*f)(double), double e) {
    double c = fabs(b + a) / 2;
    double shallow_estimate = simpson_rule(a, b, f);
    double deepper_estimate = simpson_rule(a, c, f) + simpson_rule(c, b, f);

    if (fabs(shallow_estimate - deepper_estimate) < e) {
        return deepper_estimate;
    }

    return integral_recursive(a, c, f, e) + integral_recursive(c, b, f, e);
}

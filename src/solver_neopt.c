/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/* function that transposes a matrix */
double* transpose_matrix(double *A, int N) {
        double *C = malloc(N * N * sizeof(double));
        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        C[i * N + j] = A[j * N + i];
                }
        }
        return C;
}

/* function that transposes a matrix */
double* transpose_triangular_matrix(double *A, int N) {
        double *C = calloc(N * N, sizeof(double));
        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N - (N - i - 1); j++) {
                        C[i * N + j] = A[j * N + i];
                }
        }
        return C;
}

/*
 * function that multiplies two matrices
 * and the second one is a lower triangular one
 */
double* multiply_upper_triangular_matrix(double *A,
        double *B, int N) {
        double *C = malloc(N * N * sizeof(double));
        int i, j, k;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        C[i * N + j] = 0;
                        for (k = 0; k < N - (N - j - 1); k++) {
                                C[i * N + j] += A[i * N + k] * B[k * N + j];
                        }
                }
        }
        return C;
}

/*
 * function that multiplies two matrices
 * and the second one is an upper triangular one
 */
double* multiply_lower_triangular_matrix(double *A,
        double *B, int N) {
        double *C = malloc(N * N * sizeof(double));
        int i, j, k;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        C[i * N + j] = 0;
                        for (k = j; k < N; k++) {
                                C[i * N + j] += A[i * N + k] * B[k * N + j];
                        }
                }
        }
        return C;
}

/* function that multiplies two matrices */
double* multiply_matrix(double *A,
        double *B, int N) {
        double *C = malloc(N * N * sizeof(double));
        int i, j, k;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        C[i * N + j] = 0;
                        for (k = 0; k < N; k++) {
                                C[i * N + j] += A[i * N + k] * B[k * N + j];
                        }
                }
        }
        return C;
}

/* function that adds two matrices */
double* add_matrix(double *A, double *B, int N) {
        double *C = malloc(N * N * sizeof(double));
        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        C[i * N + j] = A[i * N + j] + B[i * N + j];
                }
        }
        return C;
}

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
        printf("NEOPT SOLVER\n");

        /* here I implement the operation C = B * A * At + Bt * B */
        double *C, *At, *Bt, *D, *E, *F;

        /* transpose A and B */
        At = transpose_triangular_matrix(A, N);
        Bt = transpose_matrix(B, N);

        /* I will write B * A * At as D */
        F = multiply_upper_triangular_matrix(B, A, N);
        D = multiply_lower_triangular_matrix(F, At, N);

        /* I will write B * A * At as D */
        E = multiply_matrix(Bt, B, N);

        // now to obtain the final result
        C = add_matrix(D, E, N);

        free(At);
        free(Bt);
        free(D);
        free(E);
        free(F);

        return C;
}
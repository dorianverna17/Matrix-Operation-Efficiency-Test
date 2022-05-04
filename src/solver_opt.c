/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/* function that transposes a matrix */
double* transpose_matrix(double *A, int N) {
        register double *C = malloc(N * N * sizeof(double));
        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j+=2) {
                        C[i * N + j] = A[j * N + i];
                        C[i * N + j + 1] = A[(j + 1) * N + i];
                }
        }
        return C;
}

/* function that transposes a matrix */
double* transpose_triangular_matrix(double *A, int N) {
        register double *C = calloc(N * N, sizeof(double));

        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < i + 1; j++) {
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
        register double *C = malloc(N * N * sizeof(double));
        register double aux = 0;
        int i, j, k;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        aux = 0;
                        register double *aux_A = &A[i * N];
                        register double *aux_B = &B[j];

                        for (k = 0; k < j + 1; k++) {
                                aux += *aux_A * *aux_B;
                                aux_A++;
                                aux_B += N;
                        }
                        C[i * N + j] = aux;
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
        register double *C = malloc(N * N * sizeof(double));
        register double aux = 0;
        int i, j, k;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        aux = 0;
                        register double *aux_A = &A[i * N + j];
                        register double *aux_B = &B[j * N + j];

                        for (k = j; k < N; k++) {
                                aux += *aux_A * *aux_B;
                                aux_A++;
                                aux_B += N;
                        }
                        C[i * N + j] = aux;
                }
        }
        return C;
}

/* function that multiplies two matrices */
double* multiply_matrix(double *A,
        double *B, int N) {
        register double *C = malloc(N * N * sizeof(double));
        register double aux = 0;
        int i, j, k;
        register double *aux_A = A, *aux_B;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        aux_B = B + j;
                        aux_A = A + i * N;
                        aux = 0;
                        for (k = 0; k < N; k += 1) {
                                aux += *aux_A * *aux_B;
                                aux_B += N;
                                aux_A++;
                        }
                        C[i * N + j] = aux;
                }
        }
        return C;
}

/* function that adds two matrices */
double* add_matrix(double *A, double *B, int N) {
        int i, j;

        for (i = 0; i < N; i++) {
                for (j = 0; j < N; j+=2) {
                        B[i * N + j] += A[i * N + j];
                        B[i * N + j + 1] += A[i * N + j + 1];
                }
        }
        return B;
}

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
        printf("OPT SOLVER\n");

        /* here I implement the operation C = B * A * At + Bt * B */
        register double *C;
        register double *At, *Bt, *D, *E, *F;

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
        free(F);

        return C;
}
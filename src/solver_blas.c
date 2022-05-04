/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include <cblas.h>
#include <string.h>

/*
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
        printf("BLAS SOLVER\n");

        /* here I implement the operation C = B * A * At + Bt * B */
        double *C;

        C = calloc(N * N, sizeof(double));
        memcpy(C, B, N * N * sizeof(double));

        /* B * A */
        cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, C, N);
        /* B * A * At - with the previous result */
        cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, C, N);
        /* Bt * B and add the result with the previous one */
        cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N, N, 1, B, N, B, N, 1, C, N);

        return C;
}

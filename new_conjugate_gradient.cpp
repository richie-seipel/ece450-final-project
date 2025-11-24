#include <hls_stream.h>
#include <math.h>
#include <stdio.h>

#define N 4               // Matrix dimension (4x4 )
//#define MAX_ITER 4//shoulbe equal to N
typedef float data_t;

void cg(data_t A[N][N], data_t b[N], data_t x[N], data_t tol) {

    data_t r[N], p[N], Ap[N];
    data_t rsold, rsnew, alpha, beta, pAp;

    // Initial residual r = b - A*x
    for (int i = 0; i < N; i++) {
        data_t sum = 0;
        for (int j = 0; j < N; j++) sum += A[i][j] * x[j];
        r[i] = b[i] - sum;
        p[i] = r[i];
    }

    // rsold = r^T r
    rsold = 0;
    for (int i = 0; i < N; i++) rsold += r[i] * r[i];

    cg_loop:
    for (int k = 0; k < N; k++) {
        // Ap = A * p
        for (int i = 0; i < N; i++) {
            data_t sum = 0;
            for (int j = 0; j < N; j++)
                sum += A[i][j] * p[j];
            Ap[i] = sum;
        }

        // pAp = p^T * Ap
        pAp = 0;
        for (int i = 0; i < N; i++) pAp += p[i] * Ap[i];

        alpha = rsold / pAp;

        // x = x + alpha * p
        // r = r - alpha * Ap
        for (int i = 0; i < N; i++) {
            x[i] = x[i] + alpha * p[i];
            r[i] = r[i] - alpha * Ap[i];
        }

        rsnew = 0;
        for (int i = 0; i < N; i++) rsnew += r[i] * r[i];

        if (sqrtf(rsnew) < tol) break;

        beta = rsnew / rsold;
        for (int i = 0; i < N; i++) p[i] = r[i] + beta * p[i];
        rsold = rsnew;
    }
}
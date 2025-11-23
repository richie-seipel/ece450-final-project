#include "conjugate_gradient.h"

double dot_product(double a[N], double b[N]){
	#pragma HLS INLINE
    double acc = 0;
    for (int i = 0; i < N; i++){
		//#pragma HLS UNROLL
        acc += a[i] * b[i];
    }
    return acc;
}

void matrixmul(double a[N][N], double b[N], double c[N]) {
    #pragma HLS INLINE
    for(int i = 0; i < N; i++) {
        double acc = 0;
        for(int j = 0; j < N; j++) {
            acc += a[i][j] * b[j];
        }
        c[i] = (double) acc;
    }
}

void scalar_matrixmul(double val, double A[N], double res[N]){
    #pragma HLS INLINE
    for(int i = 0; i < N; i++) {
        #pragma HLS UNROLL
        res[i] = A[i] * val;
    }
}

void add_mat(double a[N], double b[N], double res[N]){
    #pragma HLS INLINE
    for(int i = 0; i < N; i++){
        #pragma HLS UNROLL
        res[i] = a[i] + b[i];
    }
}

void sub_mat(double a[N], double b[N], double res[N]){
    #pragma HLS INLINE
    for(int i = 0; i < N; i++){
        #pragma HLS UNROLL
        res[i] = a[i] - b[i];
    }
}

void copy_mat(double a[N], double res[N]){
    #pragma HLS INLINE
    for(int i = 0; i < N; i++){
        #pragma HLS UNROLL
        res[i] = a[i];
    }
}

//main function
//p -> search direction
//r -> residual
void conjugate_gradient(double A[N][N], double b[N], double x[N]){
    #pragma HLS INLINE off
	#pragma HLS ARRAY_PARTITION variable=A complete dim=2
	#pragma HLS ARRAY_PARTITION variable=b complete
	#pragma HLS ARRAY_PARTITION variable=x complete
    #pragma HLS INTERFACE ap_none port=A
	#pragma HLS INTERFACE ap_none port=b
	#pragma HLS INTERFACE ap_none port=x
	#pragma HLS INTERFACE ap_ctrl_none port=return
    double Ax[N];
    matrixmul(A, x, Ax);
    double r[N];
    sub_mat(b, Ax, r);
    double p[N];
    copy_mat(r, p);
    double r_dot = dot_product(r, r);

    //iterations = order of matrix
    for(int index = 0; index < N; index++){
        double Ap[N];
        matrixmul(A, p, Ap);
        double alpha = r_dot/dot_product(p, Ap);

        //x(n+1) = x(n) + alpha(n)*p(n)
        double alphap[N];
        scalar_matrixmul(alpha, p, alphap);
        //reassign to x
        add_mat(x, alphap, x);
        double alphaAp[N];
        scalar_matrixmul(alpha, Ap, alphaAp);
        sub_mat(r, alphaAp, r);

        double new_r_dot = dot_product(r,r);

        double beta = new_r_dot/r_dot;

        double beta_p[N];
        scalar_matrixmul(beta, p, beta_p);
        add_mat(r, beta_p, p);

        r_dot = new_r_dot;
         
    }
}

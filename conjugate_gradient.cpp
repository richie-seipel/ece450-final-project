#include <iostream>
using namespace std;

const int N = 2;

//function to transpose a matrix
void transpose(double matrix[N][N], double ret_matrix[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ret_matrix[j][i] = matrix[i][j];
        }
    }
}

double dot_product(double a[N], double b[N]){
    double acc = 0;
    for (int i = 0; i < N; i++){
        acc += a[i] * b[i];
    }
    return acc;
}

void matrixmul(double a[N][N], double b[N], double c[N]) {
    for(int i = 0; i < N; i++) {
        double acc = 0;
        for(int j = 0; j < N; j++) {
            acc += a[i][j] * b[j];
        }
        c[i] = (double) acc;
    }
}

void scalar_matrixmul(double val, double A[N], double res[N]){
    for(int i = 0; i < N; i++) {
        res[i] = A[i] * val;
    }
}

void add_mat(double a[N], double b[N], double res[N]){
    for(int i = 0; i < N; i++){
        res[i] = a[i] + b[i];
    }
}

void sub_mat(double a[N], double b[N], double res[N]){
    for(int i = 0; i < N; i++){
        res[i] = a[i] - b[i];
    }
}

void copy_mat(double a[N], double res[N]){
    for(int i = 0; i < N; i++){
        res[i] = a[i];
    }
}

//main function
//p -> search direction
//r -> residual
void conjugate_gradient(double A[N][N], double b[N], double x[N]){
    double Ax[N];
    matrixmul(A, x, Ax);
    double r[N];
    sub_mat(b, Ax, r);
    double p[N];
    copy_mat(r, p);
    double r_dot = dot_product(r, r);

    //iterations = order of matrix
    for(int index = 0; index < N; index++){
        //double p_t[N][N];
        //transpose(p, p_t);
        double Ap[N];
        matrixmul(A, p, Ap);
        //double alpha_denom_mat[N][N];
        //matrixmul(p_t, Ap, alpha_denom_mat);
        //double alpha_denom = alpha_denom_mat[0][0];
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
        //transpose(r, new_r_t);
        //double new_r_tr_mat[N][N]; 
        //matrixmul(new_r_t, r, new_r_tr_mat);
        //double new_r_tr = new_r_tr_mat[0][0];
        double beta = new_r_dot/r_dot;

        double beta_p[N];
        scalar_matrixmul(beta, p, beta_p);
        add_mat(r, beta_p, p);

        //double r_tr_diffp[N][N];
        //scalar_matrixmul((new_r_tr/r_tr), p, r_tr_diffp);
        //double r_plus_r_tr_diffp[N][N];
        //add_mat(r, r_tr_diffp, r_plus_r_tr_diffp);
        //copy_mat(r_plus_r_tr_diffp, p);

        r_dot = new_r_dot;
         
    }

}

int main(){

    double matrix1[N][N] = {{4, 1}, {1, 3}};
    double matrix2[N] = {{1}, {2}};
    //initial guess
    double result[N] = {0, 0};

    conjugate_gradient(matrix1, matrix2, result);
    std::cout << "conjugate gradient" << endl;
    for (const auto& element : result) {
            std::cout << element << " ";
    }

    return 0;
}

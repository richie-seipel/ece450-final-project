#include <iostream>
using namespace std;

const int N = 2;

double dot_product(double a[N], double b[N]);
void scalar_matrixmul(double val, double A[N], double res[N]);
void add_mat(double a[N], double b[N], double res[N]);
void sub_mat(double a[N], double b[N], double res[N]);
void copy_mat(double a[N], double res[N]);

void matrixmul(double a[N][N], double b[N], double c[N]);

void conjugate_gradient(double A[N][N], double b[N], double x[N]);
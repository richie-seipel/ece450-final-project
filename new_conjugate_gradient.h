#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

#define N 4               // Matrix dimension (4x4 )
//#define MAX_ITER 4//shoulbe equal to N
typedef float data_t;

void conjugate_gradient(data_t A[N][N], data_t b[N], data_t x[N], data_t tol);
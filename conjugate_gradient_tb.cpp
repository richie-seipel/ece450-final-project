#include "new_conjugate_gradient.h"

int main(){
    float matrix1[N][N] = {{2, 1, 0, 0}, {1, 2, 1, 0}, {0, 1, 2, 1}, {0, 0, 1, 2}};
    float matrix2[N] = {3, 2, 6, 4};
    //initial guess
    float result[N] = {1, 1, 1, 1};

    conjugate_gradient(matrix1, matrix2, result, 0.001);
    std::cout << "conjugate gradient" << std::endl;
    for (int i = 0; i < N; i ++) {
        for(int j = 0; j < N; j ++){
            std::cout << matrix1[i][j] << " ";
        }
        std::cout << result[i] << " " << matrix2[i] << std::endl;
    }

    for (int i = 0; i < N; i ++) {
        float sum = 0;
        for(int j = 0; j < N; j ++){
            sum += matrix1[i][j] * result[j];
        }
        std::cout << (std::round(sum) == matrix2[i]) << std::endl;
    }

    return 0;
} 

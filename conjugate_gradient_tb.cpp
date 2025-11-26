#include "new_conjugate_gradient.h"

void generate_matrix(data_t A[N][N]) {
    //fill matrix
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            A[i][j] = 1 + (i+1)*(j+1);
        }
    }

    //make symmetric
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++){
            A[j][i] = A[i][j];
        }
    }

}

int main(){
    float matrix1[N][N];
    generate_matrix(matrix1);
    float matrix2[N];
    //initial guess
    float result[N];
    for(int i = 0; i < N; i++){
        matrix2[i] = i;
        result[i] = 1;
    }

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
        if (std::round(sum) == matrix2[i]){
            std::cout << "Value " << i << " correct" << std::endl;
        }
        else {
            std::cout << "Value " << i << " incorrect" << std::endl;
        }
    }

    return 0;
} 
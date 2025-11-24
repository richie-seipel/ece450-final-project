#include "new_conjugate_gradient.cpp"
#include <iostream>
#define N 4

int main(){
    float matrix1[N][N] = {{2, 1, 0, 0}, {1, 2, 1, 0}, {0, 1, 2, 1}, {0, 0, 1, 2}};
    float matrix2[N] = {1, 2, 3, 4};
    //initial guess
    float result[N] = {0, 0, 0, 0};

    conjugate_gradient(matrix1, matrix2, result, 0.001);
    std::cout << "conjugate gradient" << std::endl;
    for (const auto& element : result) {
        std::cout << element << " ";
    }

    return 0;
} 

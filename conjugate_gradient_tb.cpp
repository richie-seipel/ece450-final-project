#include "conjugate_gradient.cpp"

int main(){
    double matrix1[N][N] = {{4, 1}, {1, 3}};
    double matrix2[N] = {1, 2};
    //initial guess
    double result[N] = {0, 0};

    conjugate_gradient(matrix1, matrix2, result);
    std::cout << "conjugate gradient" << endl;
    for (const auto& element : result) {
        std::cout << element << " ";
    }

    return 0;
} 

#include <iostream>
#include <vector>
using namespace std;

//main function
void conjugate_gradient(vector<vector<int>> A, vector<vector<int>> b, vector<vector<int>> x){

}

//function to transpose a matrix
vector<vector<int>> transpose(vector<vector<int>> matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> ret_matrix(rows, vector<int>(cols, 0));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            ret_matrix[i][j] = matrix[j][i];
        }
    }
    return ret_matrix;
}

int main(){

    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (const auto& row : matrix) {
        // Iterate through each element in the current inner vector (column)
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl; // Newline after each row
    }

    vector<vector<int>> temp = transpose(matrix);
    for (const auto& row : temp) {
        // Iterate through each element in the current inner vector (column)
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl; // Newline after each row
    }

    return 0;
}
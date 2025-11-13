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

vector<vector<int>> matrixmul(vector<vector<int>> a, vector<vector<int>> b) {
    int a_rows = a.size();
    int a_cols = a[0].size();
    int b_rows = b.size();
    int b_cols = b[0].size();
    vector<vector<int>> res(a_rows, vector<int>(b_cols, 0));
    if(a_cols != b_rows){
        std::cout << "Incorrect matrice dimensions." << endl;
    }
    else {
        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < b_cols; j++) {
                long long acc = 0;
                for (int k = 0; k < a_cols; k++) { // same as b_rows
                    acc += a[i][k] * b[k][j];
                }
                res[i][j] = (int) acc;
            }
        }
    }
    return res;
}

int main(){

    vector<vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> matrix2 = {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}};

    vector<vector<int>> temp = matrixmul(matrix1, matrix2);
    for (const auto& row : temp) {
        // Iterate through each element in the current inner vector (column)
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl; // Newline after each row
    }

    return 0;
}
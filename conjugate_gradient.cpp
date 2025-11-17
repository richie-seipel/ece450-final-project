#include <iostream>
#include <vector>
using namespace std;

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
        for(int i = 0; i < a_rows; i++) {
            for(int j = 0; j < b_cols; j++) {
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

vector<vector<int>> scalar_matrixmul(int val, vector<vector<int>> A){
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> res(rows, vector<int>(cols, 0));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            res[i][j] = A[i][j] * val;
        }
    }
    return res;
}

vector<vector<int>> add_mat(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> res(a.size(), vector<int>(b[0].size(), 0));
    if((a.size() == b.size()) && (a[0].size() == b[0].size())){
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < a[0].size(); j++) {
                res[i][j] = a[i][j] + b[i][j];
            }
        }
    }
    return res;
}

vector<vector<int>> sub_mat(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> res(a.size(), vector<int>(b[0].size(), 0));
    if((a.size() == b.size()) && (a[0].size() == b[0].size())){
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < a[0].size(); j++) {
                res[i][j] = a[i][j] - b[i][j];
            }
        }
    }
    return res;
}

//main function
vector<vector<int>> conjugate_gradient(vector<vector<int>> A, vector<vector<int>> b){
    //add checking if sizes are correct
    int x_size = A.size();
    vector<vector<int>> x(x_size, vector<int>(1, 0));

    vector<vector<int>> Ax = matrixmul(A, x);
    vector<vector<int>> residual = sub_mat(b, Ax);
    vector<vector<int>> search_dir = residual;
    vector<vector<int>> residual_t = transpose(residual);
    int rt_r =  matrixmul(residual_t, residual)[0][0];

    //iterations = order of matrix
    for(int index = 0; index < A.size(); index++){
        vector<vector<int>> search_dir_t = transpose(search_dir);
        vector<vector<int>> search_dir_A = matrixmul(search_dir, A);
        int alpha_denom = matrixmul(search_dir_t, search_dir_A)[0][0];
        int alpha = rt_r/alpha_denom;

        //x(n+1) = x(n) + alpha(n)*search_dir(n)
        vector<vector<int>> alpha_times_sdir = scalar_matrixmul(alpha, search_dir);
        //reassign to x
        x = add_mat(x, alpha_times_sdir);
        vector<vector<int>> Aresidual = matrixmul(A, residual);
        vector<vector<int>> alpha_times_Aresidual = scalar_matrixmul(alpha, Aresidual);
        residual = sub_mat(residual, alpha_times_Aresidual);

        vector<vector<int>> new_residual_t = transpose(residual);
        int new_rt_r = matrixmul(new_residual_t, residual)[0][0];

        vector<vector<int>> rt_r_diffsearch_dir = scalar_matrixmul((new_rt_r/rt_r), search_dir);
        search_dir = add_mat(residual, rt_r_diffsearch_dir);

        rt_r = new_rt_r;
         
    }

    return x;

}

int main(){

    vector<vector<int>> matrix1 = {{3, -2}, {-2, 4}};
    vector<vector<int>> matrix2 = {{1}, {1}};

    vector<vector<int>> temp = conjugate_gradient(matrix1, matrix2);
    for (const auto& row : temp) {
        // Iterate through each element in the current inner vector (column)
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl; // Newline after each row
    }

    return 0;
}
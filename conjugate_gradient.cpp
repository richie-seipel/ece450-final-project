#include <iostream>
#include <vector>
using namespace std;

//function to transpose a matrix
vector<vector<int>> transpose(vector<vector<int>> matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> ret_matrix(cols, vector<int>(rows, 0));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            ret_matrix[j][i] = matrix[i][j];
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
//p -> search direction
//r -> residual
vector<vector<int>> conjugate_gradient(vector<vector<int>> A, vector<vector<int>> b){
    //add checking if sizes are correct
    int x_size = A.size();
    vector<vector<int>> x(x_size, vector<int>(1, 1));

    vector<vector<int>> Ax = matrixmul(A, x);
    vector<vector<int>> r = sub_mat(b, Ax);
    vector<vector<int>> p = r;
    vector<vector<int>> r_t = transpose(r);
    int r_tr =  matrixmul(r_t, r)[0][0];

    //iterations = order of matrix
    for(int index = 0; index < A.size(); index++){
        vector<vector<int>> p_t = transpose(p);
        vector<vector<int>> Ap = matrixmul(A, p);
        int alpha_denom = matrixmul(p_t, Ap)[0][0];
        int alpha = r_tr/alpha_denom;

        //x(n+1) = x(n) + alpha(n)*p(n)
        vector<vector<int>> alphap = scalar_matrixmul(alpha, p);
        //reassign to x
        x = add_mat(x, alphap);
        vector<vector<int>> alphaAp = scalar_matrixmul(alpha, Ap);
        r = sub_mat(r, alphaAp);

        vector<vector<int>> new_r_t = transpose(r);
        int new_r_tr = matrixmul(new_r_t, r)[0][0];

        vector<vector<int>> r_tr_diffp = scalar_matrixmul((new_r_tr/r_tr), p);
        p = add_mat(r, r_tr_diffp);

        r_tr = new_r_tr;
         
    }

    return x;

}

int main(){

    vector<vector<int>> matrix1 = {{4, 1}, {1, 3}};
    vector<vector<int>> matrix2 = {{1}, {2}};

    vector<vector<int>> temp = conjugate_gradient(matrix1, matrix2);
    std::cout << "conjugate gradient" << endl;
    for (const auto& row : temp) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
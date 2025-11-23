#include <iostream>
#include <vector>
using namespace std;

//function to transpose a matrix
vector<vector<double>> transpose(vector<vector<double>> matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<double>> ret_matrix(cols, vector<double>(rows, 0));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            ret_matrix[j][i] = matrix[i][j];
        }
    }
    return ret_matrix;
}

vector<vector<double>> matrixmul(vector<vector<double>> a, vector<vector<double>> b) {
    int a_rows = a.size();
    int a_cols = a[0].size();
    int b_rows = b.size();
    int b_cols = b[0].size();
    vector<vector<double>> res(a_rows, vector<double>(b_cols, 0));
    if(a_cols != b_rows){
        std::cout << "Incorrect matrice dimensions." << endl;
    }
    else {
        for(int i = 0; i < a_rows; i++) {
            for(int j = 0; j < b_cols; j++) {
                double acc = 0;
                for (int k = 0; k < a_cols; k++) { // same as b_rows
                    acc += a[i][k] * b[k][j];
                }
                res[i][j] = (double) acc;
            }
        }
    }
    return res;
}

vector<vector<double>> scalar_matrixmul(double val, vector<vector<double>> A){
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<double>> res(rows, vector<double>(cols, 0));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            res[i][j] = A[i][j] * val;
        }
    }
    return res;
}

vector<vector<double>> add_mat(vector<vector<double>> a, vector<vector<double>> b){
    vector<vector<double>> res(a.size(), vector<double>(b[0].size(), 0));
    if((a.size() == b.size()) && (a[0].size() == b[0].size())){
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < a[0].size(); j++) {
                res[i][j] = a[i][j] + b[i][j];
            }
        }
    }
    return res;
}

vector<vector<double>> sub_mat(vector<vector<double>> a, vector<vector<double>> b){
    vector<vector<double>> res(a.size(), vector<double>(b[0].size(), 0));
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
vector<vector<double>> conjugate_gradient(vector<vector<double>> A, vector<vector<double>> b){
    //add checking if sizes are correct
    double x_size = A.size();
    vector<vector<double>> x(x_size, vector<double>(1, 1));

    vector<vector<double>> Ax = matrixmul(A, x);
    vector<vector<double>> r = sub_mat(b, Ax);
    vector<vector<double>> p = r;
    vector<vector<double>> r_t = transpose(r);
    double r_tr =  matrixmul(r_t, r)[0][0];

    //iterations = order of matrix
    for(int index = 0; index < A.size(); index++){
        vector<vector<double>> p_t = transpose(p);
        vector<vector<double>> Ap = matrixmul(A, p);
        double alpha_denom = matrixmul(p_t, Ap)[0][0];
        double alpha = r_tr/alpha_denom;

        //x(n+1) = x(n) + alpha(n)*p(n)
        vector<vector<double>> alphap = scalar_matrixmul(alpha, p);
        //reassign to x
        x = add_mat(x, alphap);
        vector<vector<double>> alphaAp = scalar_matrixmul(alpha, Ap);
        r = sub_mat(r, alphaAp);

        vector<vector<double>> new_r_t = transpose(r);
        double new_r_tr = matrixmul(new_r_t, r)[0][0];

        vector<vector<double>> r_tr_diffp = scalar_matrixmul((new_r_tr/r_tr), p);
        p = add_mat(r, r_tr_diffp);

        r_tr = new_r_tr;
         
    }

    return x;

}

int main(){

    vector<vector<double>> matrix1 = {{4, 1}, {1, 3}};
    vector<vector<double>> matrix2 = {{1}, {2}};

    vector<vector<double>> temp = conjugate_gradient(matrix1, matrix2);
    std::cout << "conjugate gradient" << endl;
    for (const auto& row : temp) {
        for (double element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
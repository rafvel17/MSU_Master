#include "Matrix.h"

using namespace Matrix;
using namespace std;

int main()
{
    std::vector<double> matA = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
    };
    std::vector<double> freeTerms = {2, 3, 5};
    std::vector<double> x;
    std::vector<int> v;
    // matA.push_back(1.0);
    // matA.push_back(-2.0);
    // matA.push_back(2.0);
    // matA.push_back(1.0);
    int m = 3; 
    int n = 3;
    Matrix::Matrix A(m, n, matA);
    std::cout << A.get_columns_num() << std::endl << A.get_rows_num() << std::endl << A.at(0,0) << " " << A.at(0,1) << std::endl << A.at(1,0) << " " << A.at(1,1) << std::endl; 

    // freeTerms.push_back(0.0);
    // freeTerms.push_back(5.0);
    //Matrix::Matrix ofFreeTerms(m,1,freeTerms);
    Matrix::Matrix B = A.inv();
    A.solve(freeTerms, x);
    //std::cout << B.get_rows_num() << std::endl << B.get_columns_num() << std::endl;
    //for (int i = 0; i < m; ++i)
     //{
        std::cout << "Solution of the system" << std::endl;
        std::cout << x.at(0) << " " << x.at(1) << " " << x.at(2) << std::endl;
     //}

    //A = A * A;
    //A.swapRows(0, 1);
    //A.addRows(0, 1, 1.0);
    //Matrix::Matrix B(A-A);
    //double d = det(A);
    //v = A.gauss();
    //A = A.inv();
    //std::cout << A.get_columns_num() << std::endl << A.get_rows_num() << std::endl << A.at(0,0) << " " << A.at(0,1) << std::endl << A.at(1,0) << " " << A.at(1,1) << std::endl;
    //std::cout << B.get_columns_num() << std::endl << B.get_rows_num() << std::endl << B.at(0,0) << " " << B.at(0,1) << std::endl << B.at(1,0) << " " << B.at(1,1) << std::endl;
    //double d = det(A);
    //std::cout << v.at(0) << " " << v.at(1) << std::endl << d << std::endl;
    std::cout << "inverse matrix"<< std::endl;
    for (int i = 0; i < B.get_rows_num(); ++i)
    {
        for (int j = 0; j < B.get_columns_num(); ++j)
        {
            std::cout << B.at(i,j) << " ";
        }
        std::cout << std::endl;
    }








    // std::vector<double> matA (4);
    // std::vector<double> x (2,0);
    // std::vector<double> freeTerms (2,0);
    // matA.push_back(1.0);
    // matA.push_back(-2.0);
    // matA.push_back(2.0);
    // matA.push_back(1.0);

    // freeTerms.push_back(0.0);
    // freeTerms.push_back(5.0);
    // Matrix::Matrix A(2,2, matA);
    // A.solve(freeTerms, x);
    // for (int i = 0; i < 4; ++i)
    // {
    //     std::cout << x[i] << std::endl;
    // }


    return 0;
}
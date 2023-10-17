#ifndef MATRIX_H
#define MATRIX_H 1

#include <iostream>
#include <cmath>
#include <vector>

namespace Matrix 
{

    class Matrix;

    const double M_EPSILON = 1.0e-14;

    class Matrix 
    {
        private:
        int m;
        int n;
        std::vector<std::vector<double>> rows_arr;
        //static Matrix default_matrix;
        public:
        //default constructor
        Matrix(): 
            m(1.),
            n(1.),
            rows_arr({{0.}}) 
        {}

        Matrix(int mm, int nn, std::vector<std::vector<double>> rows_arr_rr):
            m(mm),
            n(nn),
            rows_arr(rows_arr_rr)
        {}

        //copy constructor
        Matrix(Matrix const & tt):
        m(tt.m),
        n(tt.n),
        rows_arr(tt.rows_arr)
        {}

        //destructor
        ~Matrix() {};

        //get the number of rows
        int get_rows_num() const
        {
            return m;
        }

        //get the number of columns
        int get_columns_num() const
        {
            return n;
        }

        //get the matrix itself
        std::vector<std::vector<double>> get_matrix() const
        {
            return rows_arr;
        }

        //addition
        Matrix operator+(const Matrix& t) const
        {
            std::vector<std::vector<double>> rows_arr_temp = rows_arr;
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    rows_arr_temp[i][j] += t.rows_arr[i][j];
                }
            }
            return Matrix(n, m, rows_arr_temp);
        }

        //subtraction
        Matrix operator-(const Matrix& t) const
        {
            std::vector<std::vector<double>> rows_arr_temp = rows_arr;
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    rows_arr_temp[i][j] -= t.rows_arr[i][j];
                }
            }
            return Matrix(n, m, rows_arr_temp);
        }

        //multiplication 
        Matrix operator*(const Matrix& t) const
        {
            //check if possible
            if (n != t.get_rows_num())
            {
                std::cerr << "Dimensions of the matrices do not meet the conditions of multiplication" << std::endl;
                exit(1);
            } 


            std::vector<std::vector<double>> rows_arr_temp(m, std::vector<double>(t.get_columns_num(), 0));
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < t.get_columns_num(); ++j)
                {
                    for (int k = 0; k < n; ++k)
                        rows_arr_temp[i][j] += rows_arr[i][k] * t.rows_arr[k][j];
                }
            }
            return Matrix(n, m, rows_arr_temp);
        }

        //Gauss method
        Matrix& gauss ()
        {
            for (int i = 0; (i < n) && (i < m); ++i)
            {
                int k = 0;
                while ((rows_arr[k][i] <= M_EPSILON) && (k < m)) //0
                    k++; 
                
                if (k < m)
                    {
                        
                        //swap rows
                        for (int p = 0; p < n; ++p)
                        {
                            double temp = 0.;
                            temp = rows_arr[k][p];
                            rows_arr[k][p] = rows_arr[i][p];
                            rows_arr[i][p] = temp;
                        }

                        //substraction of the rows
                        for (int p = 0; p < m; ++p)
                        {
                            for (int j = 0; j < n; ++j)
                            {
                                if (p != i)
                                { 
                                    double divider = rows_arr[i][i];
                                    rows_arr[p][j] -= (rows_arr[i][j] * rows_arr[p][i] / divider);
                                }
                            }
                        }
                    }
            }
            return *this;
        }

        int rank ()
        {
            Matrix mat = *this;
            int rk = 0;
            mat.gauss();
            for (int i = 0; (i < n) && (i < m); ++i)
            {
                rk += mat.get_matrix()[i][i];
            }
            return rk;
        }


    };

}


#endif
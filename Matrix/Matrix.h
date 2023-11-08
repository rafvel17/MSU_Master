#ifndef MATRIX_H
#define MATRIX_H 1

#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

namespace Matrix 
{

    class Matrix;

    const double M_EPSILON = 1.0e-8;

    class Matrix 
    {
        private:
        int m;
        int n;
        std::vector<double> elems;
        //static Matrix default_matrix;
        public:
        Matrix(int mm, int nn, std::vector<double> arr):
            m(mm),
            n(nn),
            elems(arr)
        {}

        //copy constructor
        Matrix(Matrix const & tt):
        m(tt.m),
        n(tt.n),
        elems(tt.elems)
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

        //get the elements
        double at (int i, int j) const
        {
            if ( i < 0 || i >= m || j < 0 || j >= n)
                throw std::out_of_range ("incorrect indices of matrix");
            return elems[i*n+j];
        }

        const double* operator[] (int i) const
        {
            if ( i < 0 || i >= m)
                throw std::out_of_range ("incorrect indices of matrix");
            return &elems.at(i*n);
        }

        //addition
        Matrix operator+(const Matrix& t) const
        {
            std::vector<double> arr_temp = elems;
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    arr_temp[i*n + j] += t.elems[i*n + j];
                }
            }
            return Matrix(n, m, arr_temp);
        }

        //subtraction
        Matrix operator-(const Matrix& t) const
        {
            std::vector<double> arr_temp = elems;
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    arr_temp[i*n + j] -= t.elems[i*n + j];
                }
            }
            return Matrix(n, m, arr_temp);
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
             
            std::vector<double> arr_temp(m*t.get_columns_num(), 0);
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < t.get_columns_num(); ++j)
                {
                    for (int k = 0; k < n; ++k)
                        arr_temp[i*t.get_columns_num() + j] += elems[i*n + k] * t.elems[k*t.get_columns_num() + j];
                }
            }
            return Matrix(m, t.get_columns_num(), arr_temp);
        }

        void swapRows(int i, int j) 
        {
            for (int p = 0; p < n; ++p)
                        {
                            double temp = 0.;
                            temp = elems[i*n + p];
                            elems[i*n + p] = elems[j*n + p];
                            elems[j*n + p] = temp;
                        }
        }

        void addRows(int i, int j, double coeff)
        {
            for (int p = 0; p < n; ++p)
            {
                elems[i*n + p] += elems[j*n + p] * coeff;
            }
        }

        void multByNum (int i, double coeff)
        {
            for (int p = 0; p < n; ++p)
                elems[i*n + p] *= coeff;
        }

        std::vector<int> gauss ();

        //double det() const;

        Matrix inv() const;

        void solve (const std::vector<double>& freeTerms, std::vector<double>& x);


    };

    double det(Matrix const &);

}


#endif
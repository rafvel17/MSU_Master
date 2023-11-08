#include "Matrix.h"

std::vector<int> Matrix::Matrix::gauss()
{
    int i = 0;
    int j = 0;
    int inv_count = 0;
    while ((i < m) && (j < n))
    {
        double maxelem = fabs(at(i,j));
        int imax = i;
        for (int k = i + 1; k < m; ++k)
        {
            if (fabs(at(k, j)) > maxelem)
            {
                maxelem = fabs(at(k,j));
                imax = k;
            }
        }
        if (maxelem <= M_EPSILON)
        {
            ++j;
            continue;
        }
        if (imax != i)
        {
            swapRows(i, imax);
            inv_count++;
        }
        double r = at(i, j);
        for (int k = i + 1; k < m; ++k)
        {
            addRows(k, i, -at(k, j)/r);
            assert(fabs(at(k, j)) <= M_EPSILON);
        }
        ++i;
        ++j;

    }
    return {i, inv_count};
}

double Matrix::det(Matrix const &mat) 
{
    Matrix tmp(mat);
    double determinant = 1.0;
    std::vector<int> rk_even = tmp.gauss();
    if (rk_even.at(0) == mat.get_rows_num())
    {
        for (int i = 0; i < mat.get_rows_num(); ++i)
        {
            determinant *= tmp.at(i, i); 
        }
        if(rk_even.at(1) % 2 != 0)
        determinant *= -1;
        return determinant;
    }
    else 
    {
        return 0;
    }
}

Matrix::Matrix Matrix::Matrix::inv () const 
{
    Matrix tmp(m, n, elems);
    std::vector<double> id_arr (m*n, 0.0);
    for (int i = 0; i < m; ++i)
    {
        id_arr[i+n*i] = 1.0;
    }
    Matrix id (m, n, id_arr);

    int i = 0;
    int j = 0;
    while (i < m)
    {
        double maxelem = fabs(tmp.at(i,j));
        int imax = i;
        for (int k = i + 1; k < m; ++k)
        {
            if (fabs(tmp.at(k, j)) > maxelem)
            {
                maxelem = fabs(tmp.at(k,j));
                imax = k;
            }
        }
        if (maxelem <= M_EPSILON)
        {
            ++j;
            continue;
        }
        if (imax != i)
        {
            id.swapRows(i, imax);
            tmp.swapRows(i, imax);
        }
        double r = tmp.at(i, j);
        for (int k = i + 1; k < m; ++k)
        {
            id.addRows(k, i, -tmp.at(k, j)/r);
            tmp.addRows(k, i, -tmp.at(k, j)/r);
        }
        ++i;
        ++j;

    }

    //reverse

    i = m - 1;
    j = m - 1;
    while (i != 0)
    {
        id.multByNum(i, 1/tmp.at(i,i));
        tmp.multByNum(i, 1/tmp.at(i,i));
        for (int k = i - 1; k >= 0; --k)
        {
            id.addRows(k, i, -tmp.at(k,j));
            tmp.addRows(k, i, -tmp.at(k,j));
        }
        --i;
        --j;
    }
    id.multByNum(i, 1/tmp.at(i,i));
    tmp.multByNum(i, 1/tmp.at(i,i));

    return id;
}

void Matrix::Matrix::solve(const std::vector<double> &freeTerms, std::vector<double> &x)
{
    Matrix ofFreeTerms (m, 1, freeTerms);
    std::vector<double> col (m, 0.0);
    Matrix solution (m, 1, col);
    Matrix reversed (inv());
    solution = reversed * ofFreeTerms;
    for (int i = 0; i < m; ++i)
    {
        x.push_back(solution.at(i,0));
    }

}


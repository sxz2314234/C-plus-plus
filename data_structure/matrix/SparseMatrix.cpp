/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-01 17:08:23
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-07 17:51:16
 * @FilePath: \C-plus-plus\data_structure\matrix\SparseMatrix.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "..\Linerlist\linerlist.cpp"
#include "tem_iterator.cpp"
#include <iostream>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;

const int example[4][8] = {{0, 0, 0, 2, 0, 0, 1, 0}, {0, 6, 0, 0, 7, 0, 0, 3}, {0, 0, 0, 9, 0, 8, 0, 0}, {0, 4, 5, 0, 0, 0, 0, 0}};

template <class T>
struct matrixTerm
{
    int row;
    int col;
    T value;
    matrixTerm(int r = 0, int c = 0, int v = 0) : row(r), col(c), value(v){};
    bool operator==(const matrixTerm<T> obj) { return value == obj.value; }
    bool operator!=(const matrixTerm<T> obj) { return value != obj.value; }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const matrixTerm<T> &obj)
{
    os << obj.value;
    return os;
}

template <class T>
class sparseMatrix
{
    int rows;
    int cols;
    arrayList<matrixTerm<T>> terms;

public:
    // constructor
    sparseMatrix(int r = 0, int c = 0) : rows(r), cols(c), terms(r * c){};

    // member function
    void transpose(sparseMatrix<T> &obj);
    sparseMatrix<T> operator+(sparseMatrix<T> &);

    template <class U>
    friend ostream &operator<<(ostream &, sparseMatrix<U> &);
    template <class U>
    friend istream &operator>>(istream &, sparseMatrix<U> &);
};
template <class T>
void sparseMatrix<T>::transpose(sparseMatrix<T> &obj)
{ // return the transposition of the obj
    // set the matrix feature of transposed matrix
    obj.rows = cols;
    obj.cols = rows;
    // obj.terms.reSet(terms.size());

    // initialize to realize the transposition
    int *colSize = new int[cols + 1];
    int *rowNext = new int[cols + 1];

    for (int i = 1; i <= cols; ++i)
        colSize[i] = 0;
    for (Iterator<matrixTerm<T>> i = terms.start(); i != terms.end(); ++i)
        colSize[(*i).col]++;

    // explore the begin each line in obj
    rowNext[1] = 0;
    for (int i = 2; i <= cols; ++i)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    matrixTerm<T> mTerm;
    for (Iterator<matrixTerm<T>> i = terms.start(); i != terms.end(); ++i)
    {
        int j = rowNext[(*i).col]++;
        mTerm.row = (*i).col;
        mTerm.col = (*i).row;
        mTerm.value = (*i).value;
        obj.terms.set(j, mTerm);
    }
}

template <class T>
ostream &operator<<(ostream &out, sparseMatrix<T> &op)
{
    // output the feature of the Matrix
    out << "rows = " << op.rows << " columns = "
        << op.cols << endl;

    // output the value of the Matrix
    // One value each Line.
    Iterator<matrixTerm<T>> i;
    for (i = op.terms.start(); i != op.terms.end(); ++i)
        cout << "matrix[" << (*i).row << ", " << (*i).col
             << "] = " << (*i).value << endl;
    return out;
}
template <class T>
istream &operator>>(istream &in, sparseMatrix<T> &op)
{
    // input the feature of the Matrix
    int numberOfTerms;
    cout << "Enter number of rows, columns and terms" << endl;
    // in >> op.rows >> op.cols >> numberOfTerms;
    op.rows = 4;
    op.cols = 8;
    numberOfTerms = 9;

    // set the size of x.terms,
    // ensure that we have enough capacity
    op.terms.reSet(numberOfTerms);

    matrixTerm<T> mTerm;
    // for (int i = 0; i < numberOfTerms; ++i)
    // {
    //     cout << "Enter row, columns and value of term "
    //          << (i + 1) << endl;
    //     in >> mTerm.row >> mTerm.col >> mTerm.value;

    //     op.terms.set(i, mTerm);
    // }
    int cSize = 0;
    for (int i = 0; i < op.rows; ++i)
        for (int j = 0; j < op.cols; ++j)
        {
            mTerm.row = i + 1;
            mTerm.col = j + 1;

            mTerm.value = example[i][j];
            op.terms.set(cSize++, mTerm);
        }
    return in;
}
template <class T>
sparseMatrix<T> sparseMatrix<T>::operator+(sparseMatrix<T> &obj)
{
    if ((obj.rows != rows) || (obj.cols != cols))
    {
        cout << "The matrixes' size mismatch." << endl;
        return sparseMatrix<T>();
    }
    // set the trait of the result matrix
    sparseMatrix<T> result(rows, cols);
    result.terms.clear();
    int rSize = 0;

    // define the iterators of *this and obj
    Iterator<matrixTerm<T>> it = terms.start();
    Iterator<matrixTerm<T>> itEnd = terms.end();
    Iterator<matrixTerm<T>> ib = obj.terms.start();
    Iterator<matrixTerm<T>> ibEnd = obj.terms.end();

    // iterate all objections of *this and obj
    // plus the relative objection
    while (it != itEnd && ib != ibEnd)
    {
        int tIndex = ((*it).row - 1) * cols + (*it).col;
        int bIndex = ((*ib).row - 1) * cols + (*ib).col;

        if (tIndex < bIndex)
        {
            result.terms.set(rSize++, (*it));
            ++it;
        }
        else if (tIndex > bIndex)
        {
            result.terms.set(rSize++, (*ib));
            ++ib;
        }
        else
        { // the two objections are in the same index
            // only when the result of the two objection plused
            // don't equal to zero
            if ((*it).value + (*ib).value != 0)
            {
                matrixTerm<T> mTerm;
                mTerm.row = rows;
                mTerm.col = cols;
                mTerm.value = (*it).value + (*ib).value;
                result.terms.set(rSize++, mTerm);
            }
            ++it;
            ++ib;
        }
        // duplicate the rest objection
        for (; it != itEnd; ++it)
            result.terms.set(rSize++, *it);
        for (; ib != ibEnd; ++ib)
            result.terms.set(rSize++, *ib);
    }
    return result;
}

// test
int main()
{
    sparseMatrix<int> matrix(3, 3);
    sparseMatrix<int> temp_matrix(4, 8);
    sparseMatrix<int> add_matrix;
    cin >> matrix;
    cout << matrix;
    matrix.transpose(temp_matrix);
    cout << temp_matrix;
    // add_matrix=matrix+temp_matrix;
    // cout<<add_matrix;
    return 0;
}
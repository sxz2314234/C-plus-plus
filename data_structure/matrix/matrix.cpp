#include <iostream>
#include <stdexcept>
#include<algorithm>

using std::copy;
using std::cout;
using std::endl;

template <class T>
class matrix
{
    int rows;
    int columns;
    T *elements;

public:
    matrix(int r = 0, int c = 0);
    matrix(const matrix<T> &);
    ~matrix() { delete elements; }
    matrix<T> operator+(const matrix<T> &) const;
    // matrix<T> operator+()const;
    // matrix<T> operator-()const;
    matrix<T> operator-(const matrix<T> &) const;
    matrix<T> operator=(const matrix<T> &) const;
    matrix<T> &operator+=(const T &) const;
    matrix<T> operator*(const matrix<T> &) const;
    matrix<T> transpose() const;
    void show(std::ostream &) const;

    template <class U>
    friend std::ostream &operator<<(std::ostream &, const matrix<U> &);

    int row() const { return rows; }
    int column() const { return columns; }
    T &operator()(int i, int j);
};
template <class T>
matrix<T> matrix<T>::transpose() const
{
    matrix<T> trs(columns, rows);
    for (int i = 0; i < columns; i++)
        for (int j = 0; j < rows; j++)
            trs.elements[i * trs.columns + j] = elements[j * trs.columns + i];
    return trs;
}

template <class T>
matrix<T>::matrix(int r, int c)
{
    if (r < 0 || c < 0)
        // throw illegalParameterValue("Rows and columns must be >=0");
        cout << "Rows and columns must be >=0" << endl;
    else if ((r == 0 || c == 0) && (r != 0 || c != 0))
        // throw illegalParameterValue("Either both  or neither rows and columns should be zero.");
        cout << "Either both  or neither rows and columns should be zero." << endl;
    else
    {
        elements = new T[r * c];
        rows = r;
        columns = c;
    }
}
template <class T>
matrix<T>::matrix(const matrix &obj)
{
    rows = obj.rows;
    columns = obj.columns;
    elements = new T[rows * columns];

    copy(obj.elements, obj.elements + rows * columns, elements);
}
template <class T>
T &matrix<T>::operator()(int i, int j)
{
    if ((i < 0 || i >= rows) || (j < 0 || j >= columns))
        // throw matrixIndexOutOfBounds();
        cout << "beyond the bounds of the matrix index." << endl;
    return elements[i * columns + j];
}
template <class T>
matrix<T> matrix<T>::operator=(const matrix<T> &obj) const
{
    if (this != &obj)
    {
        delete[] elements;
        rows = obj.rows;
        columns = obj.columns;
        elements = new T[rows * columns];
        copy(obj.elements, obj.elements + rows * columns, elements);
    }
    return *this;
}

template <class T>
matrix<T> &matrix<T>::operator+=(const T &obj) const
{
    for (int i = 0; i < rows * columns; ++i)
        elements[i] += obj;
    return *this;
}
template <class T>
matrix<T> matrix<T>::operator+(const matrix<T> &obj) const
{
    if (rows != obj.rows || columns != obj.columns)
        // throw matrixSizeMismatch();
        cout << "Mismatch with the matrix size." << endl;
    matrix<T> temp(rows, columns);
    for (int i = 0; i < rows * columns; ++i)
        temp.elements[i] = elements[i] + obj.elements[i];
    return temp;
}
template <class T>
matrix<T> matrix<T>::operator-(const matrix<T> &obj) const
{
    if (rows != obj.rows || columns != obj.columns)
        // throw matrixSizeMismatch();
        cout << "Mismatch with the matrix size." << endl;
    matrix<T> temp(rows, columns);
    for (int i = 0; i < rows * columns; ++i)
        temp.elements[i] = elements[i] - obj.elements[i];
    return temp;
}
template <class T>
matrix<T> matrix<T>::operator*(const matrix<T> &obj) const
{
    if (columns != obj.rows)
        // throw matrixSizeMismatch();
        cout << "Mismatch with the matrix size." << endl;

    matrix<T> factor(rows, obj.columns);
    int ct = 0, cm = 0, cw = 0;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < obj.columns; ++j)
        {
            T sum = elements[ct] * obj.elements[cm];
            for (int k = 1; k < columns; ++k)
            {
                ct++;
                cm += obj.columns;
                sum += elements[ct] * obj.elements[cm];
            }
            factor.elements[cw++] = sum;
            // from the beginning of the row and the next column
            ct -= columns - 1;
            cm = j;
        }
    }
    // renew from the next row and the first column
    ct += columns;
    cm = 0;
    return factor;
}
template <class T>
void matrix<T>::show(std::ostream &out) const
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            out << elements[i * columns + j] << " ";
        }
        cout << endl;
    }
}
template <class U>
std::ostream &operator<<(std::ostream &os, const matrix<U> &obj)
{
    obj.show(os);
    return os;
}

template <class T>
void initialize(matrix<T> &op)
{
    for (int i = 0; i < op.row(); ++i)
        for (int j = 0; j < op.column(); ++j)
            op(i, j) = i + j;
}

int main()
{
    matrix<int> op1(3, 3);
    matrix<int> op2(3, 3);
    initialize(op1);
    initialize(op2);
    cout << op1 << endl;
    cout << op2 << endl;
    cout << op1 + op2;
    cout << op1 * op2;
}
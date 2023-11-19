// vslice.cpp --using valarray slices
#include <iostream>
#include <valarray> // only dispose the number value
#include <cstdlib>
#include <iterator>
#include <algorithm>

const int size = 12;
using vint = std::valarray<int>;
void show(const vint &v, int cols);

int main()
{
    using std::cout;
    using std::slice;  // from from<valarray>
    vint valint(size); // think of as 4 rows of 3

    std::ostream_iterator<int> out(cout, " ");
    for (int i = 0; i < size; ++i)
        valint[i] = std::rand() % 10;
    cout << "Original array:\n";

    // std::copy(begin(valint),end(valint),out);
    show(valint, 3);
    vint vcol(valint[slice(1, 4, 3)]);
    cout << "Second column:\n";
    show(vcol, 1);
    vint vrow(valint[slice(3, 3, 1)]);
    cout << "Second row:\n";
    show(vrow, 3);
    valint[slice(2, 4, 3)] = 10;
    cout << "Set last column to 10:\n";
    show(valint, 3);
    cout << "Set first column to sum of next two:\n";
    // + not defined for slices, so convert to valarray<int>
    valint[slice(0, 4, 3)] = vint(valint[slice(1, 4, 3)]) + vint(valint[slice(2, 4, 3)]);
    show(valint, 3);
    return 0;
}

void show(const vint &v, int cols)
{
    using std::cout;
    using std::endl;

    int lim = v.size();
    for (int i = 0; i < lim; ++i)
    {
        cout.width(3);
        cout << v[i];
        if (i % cols == cols - 1)
            cout << endl;
        else
            cout << " ";
    }
    if (lim % cols != 0)
        cout << endl;
}
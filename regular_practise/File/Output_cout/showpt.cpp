// showpt.cpp --setting the precision, showing trailing point
#include <iostream>

using std::cout;
using std::ios_base;

int main()
{
    float price1 = 20.40;
    float price2 = 1.9 + 8.0 / 9.0;

    cout.setf(ios_base::showpoint);
    cout << "\"Furry Friends\"is $" << price1 << "!\n";
    cout << "\"Fiery Friends\"is $" << price2 << "!\n";

    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "\"Furry Friends\"is $" << price1 << "!\n";
    cout << "\"Fiery Friends\"is $" << price2 << "!\n";
}
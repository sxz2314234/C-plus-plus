// setf.cpp --using setf() to control formatting
#include <iostream>

int main()
{
    using std::cout;
    using std::endl;
    using std::ios_base;

    int tempture = 63;
    cout << "Today's water tempture: ";
    cout.setf(ios_base::showpos); // show plus sign
    cout << tempture << endl;

    cout << "For our programming friends, that's\n";
    cout << std::hex << tempture << endl; // use hex
    cout.setf(ios_base::uppercase);       // use uppercase in hex
    cout.setf(ios_base::showbase);        // use 0X prefix for hex
    cout << "or\n";
    cout << tempture << endl;
    cout << "How " << true << "! oops -- How ";
    cout.setf(ios_base::boolalpha);
    cout << true << "!\n";

    return 0;
}
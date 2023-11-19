// setf2.cpp -- using setf() with 2 arguments to control formatting
#include<iostream>
#include<cmath>

using namespace std;

int main()
{
    // use left justifaction, show the plus sign, show formatting
    // zeros, with precision of 3
    cout.setf(ios_base::left,ios_base::adjustfield);
    cout.setf(ios_base::showpos);
    cout.precision(3);
    // use e-notation and save old format setting
    ios_base::fmtflags old=cout.setf(ios_base::scientific,ios_base::floatfield);
    cout<<"Left Justification:\n";
    long n;
    for(n=1;n<=41;n+=10)
    {
        cout.width(4);
        cout<<n<<"|";
        cout.width(12);
        cout<<sqrt(double(n))<<"|\n";
    }

    // change to internal justification
    cout.setf(ios_base::internal,ios_base::adjustfield);
    // restore default floating-point display style
    cout.setf(old,ios_base::floatfield);

    cout<<"Internal justification:\n";
    for(n=1;n<=41;n+=10)
    {
        cout.width(4);
        cout<<n<<"|";
        cout.width(12);
        cout<<sqrt(double(n))<<"|\n";
    }
    
    // use right justification, fixed notation
    cout.setf(ios_base::right,ios_base::adjustfield);
    cout.setf(ios_base::fixed,ios_base::adjustfield);
    cout<<"Right justification:\n";
    for(n=1;n<=41;n+=10)
    {
        cout.width(4);
        cout<<n<<"|";
        cout.width(12);
        cout<<sqrt(double(n))<<"|\n";
    }

    return 0;
}
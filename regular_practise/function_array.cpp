// function pointer

#include <iostream>
using namespace std;
/*
the three declaration below is equivalent
const double *f1(const double ar[],int n);
const double *f2(const double *,int n);
const double *f3(const double [],int n);
*/

double betsy(int);
double pam(int);

int f1(int);
int f2(int);
int f3(int);

// second argument is pointer to type double function that
// takes a type int argument
void estimate(int lines, double (*pf)(int));
void function_array(int (*f1)(int a), int (*f2)(int b), int (*f3)(int c));

int main()
{
    int code;
    cout << "How many lines of code do you need? ";
    cin >> code;
    cout << "Here's Betsy's estimate:\n";
    estimate(code, betsy);
    cout << "Here's pam's estimate:\n";
    estimate(code, pam);
    function_array(f1, f2, f3);
    return 0;
}
double betsy(int ins)
{
    return 0.05 * ins;
}
double pam(int ins)
{
    return 0.03 * ins + 0.0004 * ins * ins;
}
void estimate(int lines, double (*pf)(int))
{
    cout << lines << " lines will take ";
    cout << pf(lines) << "hour(s)\n";
}
// the array of function pointers
// and the array pointer
void function_array(int (*f1)(int a), int (*f2)(int b), int (*f3)(int c))
{
    int (*farray[3])(int a) = {f1, f2, f3};
    int (*(*farray2)[3])(int a) = &farray; // the defination of the array pointer
    // one difference between farray and farray2
    //  **farray2==*farray==farray[0];
    auto farray3 = farray;
    for (int i = 0; i < 3; ++i)
        switch (i)
        {
        case 0:
            cout << "The result of the first function is " << farray[i](i)
                 << endl;
            break;
        case 1:
            cout << "The result of the second function is " << farray[i](i)
                 << endl;
            break;
        case 2:
            cout << "The result of the third funtion is " << farray[i](i)
                 << endl;
            break;
        default:
            break;
        }
}
int f1(int a)
{
    return a + 1;
}
int f2(int b)
{
    return b + 2;
}
int f3(int c)
{
    return c + 3;
}

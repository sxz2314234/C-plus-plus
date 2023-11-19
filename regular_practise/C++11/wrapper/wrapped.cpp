// wrapped.cpp -- using a function wrapped as an argument
#include "somedefs.h"
#include <iostream>
#include <functional>

double dub(double x) { return 2.0 * x; }
double square(double x) { return x * x; }

int main()
{
    using std::cout;
    using std::endl;
    using std::function;

    double y = 1.21;
    using fun = function<double(double)>;
    fun ef1 = dub;
    fun ef2 = square;
    fun ef3 = Fq(10.0);
    fun ef4 = Fp(10.0);
    fun ef5 = [](double u)
    { return u * u; };
    fun ef6 = [](double u)
    { return u + u / 2.0; };
    cout << "Function pointer dub:\n";
    cout << " " << use_function(y, ef1) << endl;

    cout << "Function pointer square:\n";
    cout << " " << use_function(y, ef2) << endl;

    cout << "Function object Fp:\n";
    cout << " " << use_function(y, ef3) << endl;

    cout << "Function object Fq:\n";
    cout << " " << use_function(y, ef4) << endl;
    cout << "Lambda expression 1:\n";
    cout << " " << use_function(y, ef5) << endl;
    cout << "Lambde expression 2:\n";
    cout << " " << use_function(y, ef6) << endl;

    return 0;
}

/*
some other ways

Annotate: the keyword function actually is a template class in headfile <functional>

1.We can construct a temporary function<double<double>> object:
using fdd=function<double<double>>;
cout<<"use_function(y,fdd(dub))"<<endl;
cout<<"use_function(y,fdd(square))"<<endl;

2.We make the second argument of function,use_function(), mate to the argument uploaded:
template<class T>
T use_function(T value,function<double(double)>fun)
{
    static int count=0;
    count++;
    std::cout<<" use_function count = "<<count
    <<", &count = "<<&count<<std::endl;
    return function(value);
}

Then we can invoke it in this way:
cout<<" "<<use_function<double>(y,dub)<<endl;

*/
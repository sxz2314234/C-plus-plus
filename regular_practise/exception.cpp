// exception.cpp --about some errors when in programming.
#include<iostream>
#include<string>
#include<new>
#include<cstdlib>  //for exit,EXIT_FALLURE

using std::cout;
using std::endl;
using std::string;

class exp1
{ 
    string exp;
    public:
    explicit exp1(const string&str):exp(str){cout<<"The exception1 has occured.\n";}

    void showExp()const;
};

inline void exp1::showExp()const
{
    cout<<exp<<endl;
}

class Exception
{
    public:
    virtual void showExp()const=0;
};

class Integer:public Exception
{
    public:
    Integer(){cout<<"The class Integer has been established."<<endl;}
    void showExp()const{cout<<"The positive-integer problem has occured."<<endl;}
};

class Big:public Exception
{
    public:
    Big(){cout<<"The class Big has been established."<<endl;}
    void showExp()const{cout<<"The Big problems has occured."<<endl;}
};

int main()
{
    int x,y;
    cout<<"Please enter two positive integers."<<endl;
    while(std::cin>>x>>y)
    try
    {
        if(x<0||y<0)
        throw Integer();
        else if(x<y)
        throw Big();
    }
    catch(const Exception& e)
    {
        e.showExp();
    }
}

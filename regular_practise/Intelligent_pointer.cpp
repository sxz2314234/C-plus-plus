// Intelligent_pointer.cpp 
// we use the intelligent pointer template, 
// which contain the explicit constructor,to automatically convert.
// annotation: auto_ptr<> has been deleted in C++11.
#include<iostream>
#include<string>
#include<memory>  // contain the definantion of the smart pointer template.

using namespace std;

unique_ptr<string> demo(const char*s);

class Report
{
    private:
    string str;
    public:
    Report(const string& s):str(s){cout<<"Objected created!\n";}
    ~Report(){cout<<"Objected deleted!\n";}

    void comment()const{cout<<str<<"\n";}
};

int main()
{
    // {
    //     shared_ptr<Report> ps(new Report("using shared_ptr"));
    //     ps->comment();
    // }
    // {
    //     unique_ptr<Report> pt(new Report("using unique_ptr"));
    //     pt->comment();
    // }

    // the unique_ptr allow that the right value of the equation is temporary.
    unique_ptr<string> str;
    str=demo("Hello world.");
    cout<<*str;
    return 0;
}

unique_ptr<string> demo(const char* s)
{
    unique_ptr<string> temp(new string(s));
    return temp;
}
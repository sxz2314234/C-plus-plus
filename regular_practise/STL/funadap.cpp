// funadap.cpp --using function adaptor,transform()
#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<functional>

using namespace std;

void Show(double);
const int LIM=6;

int main()
{
    double arr1[LIM]={28,29,30,35,38,59};
    double arr2[LIM]={63,65,69,75,80,99};

    vector<double> gr8(arr1,arr1+6);
    vector<double> m8(arr2,arr2+6);
    cout.setf(ios_base::fixed);
    cout.precision(1);
    cout<<"gr8:\t";
    for_each(gr8.begin(),gr8.end(),Show);
    cout<<endl;
    cout<<"m8:\t";
    for_each(m8.begin(),m8.end(),Show);
    cout<<endl;

    vector<double> sum(LIM);
    transform(gr8.begin(),gr8.end(),m8.begin(),sum.begin(),plus<double>());
    cout<<"sum:\t";
    for_each(sum.begin(),sum.end(),Show);
    cout<<endl;

    // caution:the adaptive functor bind1st has been disposed by C++11
    // So we replace it with bind.
    vector<double> prod(LIM);
    transform(gr8.begin(),gr8.end(),prod.begin(),bind(multiplies<double>(),placeholders::_1,2.5));
    cout<<"prod:\t";
    for_each(prod.begin(),prod.end(),Show);
    cout<<endl;

    return 0;
}

void Show(double v)
{
    cout.width(6);
    cout<<v<<' ';
}
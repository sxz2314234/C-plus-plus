// test.cpp --test the nested class, iterator
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include"Iterator.cpp"

using std::cout;
using std::endl;

int main()
{
    int count=0;
    my_vector<int> num(10);
    my_vector<int>::iterator pr;

    for(pr=num.begin();pr!=num.end();pr++)
    *pr=std::rand()%10;

    for(int i=0;i<10;++i)
    cout<<num[i]<<" ";
    cout<<endl;
    
    std::sort(num.begin(),num.end());
    for(auto x:num)
    cout<<x<<" ";
    cout<<endl;
}
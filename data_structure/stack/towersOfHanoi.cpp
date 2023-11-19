#include<iostream>

using std::cout;
using std::cin;
using std::endl;

void towersOfHanoi(int,char,char,char);

int main()
{
    int num=0;
    cout<<"Please enter the number of the block you want to move: ";
    cin>>num;
    char source='a';
    char target='b';
    char auxiliary='c';
    towersOfHanoi(num,source,target,auxiliary);
}

void towersOfHanoi(int n,char source,char target,char auxiliary)
{
    if(n>0)
    {
        towersOfHanoi(n-1,source,auxiliary,target);
        cout<<"Move the top disk from "<<source<<" to "<<target<<endl;
        towersOfHanoi(n-1,auxiliary,target,source);
    }
}

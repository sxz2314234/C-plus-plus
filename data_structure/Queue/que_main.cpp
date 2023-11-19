#include"queue.cpp"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

const int que_size=10;

int main()
{
    arrayQueue<int> queue(que_size);
    arrayQueue<int> queue2(que_size);
    int i=0;
    while(!queue.full())
    {
        cout<<"The "<<++i<<" enter the queue."<<endl;
        queue.push(i);
    }
    while(!queue2.full())
    {
        cout<<"The "<<++i<<" enter the queue."<<endl;
        queue2.push(i);
    }
    arrayQueue<int> queue3=queue+queue2;
    while(!queue3.empty())
    {
        queue3.pop(i);
        cout<<"The "<<i<<" exit the queue."<<endl;
    }
}  
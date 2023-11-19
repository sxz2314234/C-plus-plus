#include<iostream>
#include<thread>  // contains some definations of the class thread

using namespace std;

void say_Hello()
{
    cout<<"Hello Thread!!!"<<endl;
}

int main()
{
    thread t(say_Hello);
    t.join();
    return 0;
}
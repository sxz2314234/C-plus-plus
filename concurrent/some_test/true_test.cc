#include<iostream>
#include<future>
#include<thread>

using namespace std;

int mythread()
{
    cout<<"My thread is :"<<this_thread::get_id()<<endl;
    chrono::milliseconds dura(5000); // 定一个5秒的时间

    this_thread::sleep_for(dura);
    cout<<"My thread is "<<this_thread::get_id()<<endl;
    return 5;
}

int main()
{
    cout<<"My main thread is :"<<this_thread::get_id()<<endl;

    future<int> fut=async(mythread);
    cout<<"Continue......."<<endl;
    future_status status=fut.wait_for(std::chrono::seconds(1));

    // 使得原本的异步线程同步了;
    while(status!=future_status::ready)
    {
        cout<<"This thread has not been ready."<<endl;
        status=fut.wait_for(std::chrono::seconds(1));
    }

    cout<<"Now the thread is ready. And wait time is "<<fut.get();
}
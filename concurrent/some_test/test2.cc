#include <iostream>
#include <thread>
#include <future>
using namespace std;

int mythread() // 线程入口函数
{
    cout << "mythread start"
         << "threadid= " << std::this_thread::get_id() << endl; // 打印线程id

    std::chrono::milliseconds dura(5000); // 定一个5秒的时间
    std::this_thread::sleep_for(dura);    // 休息一定时常

    cout << "mythread end"
         << "threadid= " << std::this_thread::get_id() << endl; // 打印线程id

    return 5;
}
int main()
{
    cout << "main"
         << "threadid= " << std::this_thread::get_id() << endl;
    std::future<int> result = std::async(mythread); // 流程并不卡在这里
    cout << "continue....." << endl;

    // 枚举类型
    std::future_status status = result.wait_for(std::chrono::seconds(6)); // 等待一秒

    if (status == std::future_status::deferred)
    {
        // 线程被延迟执行了，系统资源紧张
        cout << result.get() << endl; // 此时采取调用mythread()
    }
    else if (status == std::future_status::timeout) //
    {
        // 超时：表示线程还没执行完；我想等待你1秒，希望你返回，你没有返回，那么 status = timeout
        // 线程还没执行完
        cout << "超时：表示线程还没执行完!" << endl;
    }
    else if (status == std::future_status::ready)
    {
        // 表示线程成功返回
        cout << "线程成功执行完毕，返回!" << endl;
        cout << result.get() << endl;
    }

    cout << "I love China!" << endl;
    return 0;
}
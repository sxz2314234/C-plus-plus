#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include<numeric>

// 启动线程的几种方式
// 1.default constructor

int do_something(int i = 0);
void do_something_else();
std::thread my_thread(do_something);

// 2.function object
class background_task
{
public:
    void operator()() const
    {
        // do_something();
        // do_something_else();
    }
};

background_task task;
std::thread mythread(task);

/*

note: std::thread my_thread(background());
It just defines one thread class,instead of starting one thread;

So we can start by this method:
std::thread my_thread((background())) or std::thread{(background())};

*/

// 3. lambda expression
std::thread my_thread([]
                      {do_something();do_something_else(); });

// If we start the thread, we should decide when to terminate it
class func
{
    int &i;

public:
    func(int &i_) : i(i_){};
    void operator()()
    {
        for (unsigned int j = 0; j < 10000; ++j)
        {
            do_something(i); // 1. 存在访问隐患：悬空引用；
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach(); // 2.不等待线程结束
} // 3.新线程可能还在运行

// 特殊情况下的等待；
// 1.避免应用被抛出的异常所终止：

void do_something_in_current_thread();

void function()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread mythread(my_func);

    try
    {
        /* code */
        do_something_in_current_thread();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        my_thread.join();
        throw;
    }
    my_thread.join();
}

// 2.如需确保线程在函数之前结束——查看是否因为线程函数使用了局部变量的引用，以及其他原因；
class thread_guard
{
    std::thread &my_thread;

public:
    thread_guard(std::thread &t_) : my_thread(t_){};
    ~thread_guard()
    {
        if (my_thread.joinable())
        {
            my_thread.join(); // 通过析构函数调用，确保thread在函数前执行完
        }
    }

    thread_guard(thread_guard const &) = delete;
    thread_guard &operator=(thread_guard const &) = delete;
};

// 后台运行线程
// 使用多个线程处理不同的文档
void open_document_and_display_gui(std::string const &);
bool done_editing();
class user_command;
user_command get_user_input();
void process_user_input(user_command);

void edit_document(std::string const &filename)
{
    open_document_and_display_gui(filename);
    while (!done_editing())
    {
        user_command cmd = get_user_input();
        if (cmd.type == open_new_document)
        {
            std::string const new_name = get_filename_from_user();
            std::thread t(edit_document, new_name); // 1
            t.detach();                             // 2
        }
        else
        {
            process_user_input(cmd);
        }
    }
}

// 向线程函数传递参数

void f(int i, std::string const &s);
std::thread t(f, 3, "hello"); // 静态变量的指针传参没有问题

// 但是传动态变量的指针可能会引发两个问题：
// 1.函数很有可能在字面值转化成std::string对象之前崩溃
// 2.std::thread的构造函数会复制提供的变量，就只复制了没有转换称期望类型的字符串字面值；
void f(int i, std::string const &s);
void oops(int some_param)
{
    char buffer[1024];
    sprintf(buffer, "%i", some_param);
    std::thread t(f, 3, buffer);
    // 使用std::string(buffer)显示转换，避免悬垂指针
    t.detach();
}

/*
当传递引用时，std::thread的构造函数会盲目拷贝，
传递给函数的参数是data变量内部拷贝的引用，而非数据本身的引用。
因此线程结束时，内部拷贝数据将会在数据更新阶段被销毁，并不影响函数的中变量；
可以用std::ref将参数转换成引用的形式，如下：
*/
void update_data_for_widget(widget_id w, widget_data &data);
std::thread my_thread(update_data_for_widget, w, std::ref(data));

// 可以传递一个成员函数指针作为线程函数，并提供一个合适的对象指针作为第一个参数：
class X
{
public:
    void do_lengthy_work();
};
X my_x;
std::thread t(&X::do_lengthy_work, &my_x);

// 当原对象是一个临时变量时，自动进行移动操作，但当原对象是一个命名变量
// 那么转移的时候就需要使用std::move()进行显示移动
// 以下将展示std::move是如何转移一个动态对象到一个线程中去：
void process_big_object(std::unique_ptr<big_object>);

std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t(process_big_object, std::move(p));

// 转移线程所有权
void some_function();
void some_other_function();
std::thread t1(some_function);         // 1
std::thread t2 = std::move(t1);        // 2
t1 = std::thread(some_other_function); // 3
std::thread t3;                        // 4
t3 = std::move(t2);                    // 5
t1 = std::move(t3);                    // 6 赋值操作将使程序崩溃

/*

注：当显式使用std::move()创建t2后②，t1的所有权就转移给了t2。之后，t1和执行线程已经没有关联了；执行some_function的函数现在与t2关联。

然后，与一个临时std::thread对象相关的线程启动了③。为什么不显式调用std::move()转移所有权呢？因为，所有者是一个临时对象——移动操作将会隐式的调用。

t3使用默认构造方式创建④，与任何执行线程都没有关联。调用std::move()将与t2关联线程的所有权转移到t3中⑤。因为t2是一个命名对象，需要显式的调用std::move()。

移动操作⑤完成后，t1与执行some_other_function的线程相关联，t2与任何线程都无关联，t3与执行some_function的线程相关联。

最后一个移动操作，将some_function线程的所有权转移⑥给t1。不过，t1已经有了一个关联的线程(执行some_other_function的线程)，所以这里系统直接调用std::terminate()终止程序继续运行。

终止操作将调用std::thread的析构函数，销毁所有对象(与C++中异常的处理方式很相似)。2.1.1节中，需要在线程对象被析构前，显式的等待线程完成，或者分离它；进行复制时也需要满足这些条件(说明：不能通过赋一个新值给std::thread对象的方式来"丢弃"一个线程)。

std::thread支持移动，就意味着线程的所有权可以在函数外进行转移，就如下面程序一样。

清单2.5 函数返回std::thread对象

*/

// std::thread支持移动，意味着下面代码成立：
std::thread f()
{
    void some_function();
    return std::thread(some_function);
}

std::thread g()
{
    void some_function();
    std::thread t(some_function);
    return t;
}

// 当主线程到达f()函数的末尾时，scoped_thread对象将会销毁，
// 然后加入③到的构造函数①创建的线程对象中去。

class scoped_thread
{
    std::thread t;

public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_)) // 1
    {
        if (!t.joinable()) // 2
            throw std::logic_error(“No thread”);
    }
    ~scoped_thread()
    {
        t.join(); // 3
    }
    scoped_thread(scoped_thread const &) = delete;
    scoped_thread &operator=(scoped_thread const &) = delete;
};

struct func; // 定义在清单2.1中

void f()
{
    int some_local_state;
    scoped_thread t(std::thread(func(some_local_state))); // 4
    do_something_in_current_thread();
}

// std::thread对象的容器，如果这个容器是移动敏感的(比如，标准中的std::vector<>)，
// 那么移动操作同样适用于这些容器。代码量产了一些线程，并且等待它们结束。

void do_work(unsigned int id);

void f()
{
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < 20; ++i)
    {
        threads.push_back(std::thread(do_work, i)); // 产生线程
    }
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join)); // 对每个线程调用join()
}

// 运行时决定线程数量

// std::thread::hardware_concurrency()在新版C++标准库中是一个很有用的函数。
// 这个函数将返回能同时并发在一个程序中的线程数量。
// 例如，多核系统中，返回值可以是CPU核芯的数量。返回值也仅仅是一个提示，当系统信息无法获取时，函数也会返回0。

// 两个标准函数：std::advance(),std::accumulate();
template <class It, class Distance>
constexpr void advance(It &it, Distance n)
{
    using category = typename std::iterator_traits<It>::iterator_category;
    static_assert(std::is_base_of_v<std::input_iterator_tag, category>);

    auto dist = typename std::iterator_traits<It>::difference_type(n);
    if constexpr (std::is_base_of_v<std::random_access_iterator_tag, category>)
        it += dist;
    else
    {
        while (dist > 0)
        {
            --dist;
            ++it;
        }
        if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, category>)
        {
            while (dist < 0)
            {
                ++dist;
                --it;
            }
        }
    }
}

// 注：被constexpr修饰的变量或者函数，在编译时期就运行
// if constexpr如果在编译时期确定表达式为true,就直接编译，为false就直接跳过；
// 若是if：则两者则都编译，运行时判断

template <class _InIt, class _Ty, class _Fn2>
inline _Ty _Accumulate(_InIt _First, _InIt _Last, _Ty _Val, _Fn2 _Func)
{ // return sum of _Val and all in [_First, _Last), using _Func
    for (; _First != _Last; ++_First)
        _Val = _Func(_Val, *_First);
    return (_Val);
}

template<class Iterator,class T>
class accumulate_block
{
    public:
    void operator()(Iterator first,Iterator last,T& result)
    {
        result=std::advance(first,last,result);
    }
}

template<class Iterator,class T>
T parallel_advance(Iterator first,Iterator last,T init)
{
    // 得到最小线程数
    unsigned long const length=std::distance(first,last);
    if(!length)
    return init;

    unsigned long const min_per_thread=25;
    unsigned long const max_threads=(length+min_per_thread-1)/min_per_thread;
    
    // 返回硬件所支持的线程数量，（称为超额认购）
    unsigned long const hard_ware=std::thread::hardware_concurrency();

    unsigned long const num_threads=min(hard_ware!=0?hard_ware:2,max_thread);

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    unsigned long const block_size=length/num_threads;

    Iterator block_start=first;

    // 由主线程调用的子线程
    for(int i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);

        threads[i]=std::thread(accumulate_block<Iterator,T>,block_start,
        block_end,std::ref(results[i]));

        block_start=block_end;
    }

    // 主线程
    accumulate_block<Iterator,T>()(block_start,last,results[num_threads-1]);

    // 确保每一个线程都join()
    std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(),results.end(),init);
}

// 识别线程
/*

一、线程的标识类型是: std::thread::id,可通过两种方式检索

    1. 调用std::thread对象的成员函数get_id()
    如果成员std::thread对象没有与任何执行线程相关联，
    则返回std::thread::type默认构造值。

    2. 在该线程中调用std::this_thread::get_id()(该函数定义在<thread>)

二、std::thread::id可以自由的拷贝对比。如果两个线程有相同的id,意味着两线程相同；

三、可将std::thread::id作为容器的键值，做排序，或做其他方式的比较。
按默认顺序比较不同值的std::thread::id，所以这个行为可预见的：当a<b，b<c时，得a<c，等等。
标准库也提供std::hash<std::thread::id>容器，所以std::thread::id也可以作为无序容器的键值。

*/

// std::thread::id实例常用作检测线程是否需要进行一些操作，
// 比如：当用线程来分割一项工作(如清单2.8)，主线程可能要做一些与其他线程不同的工作。
// 这种情况下，启动其他线程前，它可以将自己的线程ID通过std::this_thread::get_id()得到，并进行存储。
// 就是算法核心部分(所有线程都一样的),每个线程都要检查一下，其拥有的线程ID是否与初始线程的ID相同。

std::thread::id master_id;
void some_core_part_of_algorithm()
{
    if(std::this_thread::get_id()==master_id)
    {
        do_master_thread_work();
    }

    do_common_thread_work();
}
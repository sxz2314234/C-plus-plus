#include<list>
#include<string>
#include<mutex>
#include<algorithm>
#include<exception>
#include<memory>    // For std::shared_ptr<>
#include<stack>

// C++使用互斥量mutex
// std::lock_guard提供RAII语法模板，
// 类构造时上锁，析构时解锁 
std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex); 
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end(); 
}

// 精心组织代码来保护共享数据
// 将互斥量与所保护的数据封装成类

// 无意中传递了保护数据引用
class some_data
{
    int index;
    std::string chars;
    public:
    void do_something();
};

class data_wrapper
{
    some_data datas;
    std::mutex m;

    public:
    template<class Function>
    void process_data(Function function)
    {
        std::lock_guard<std::mutex> guard(m);
        function(datas);   // 1.传递“保护”数据给用户函数
    }
};

some_data* unprotected;

void malicious_func(some_data& protected_data)
{
    unprotected=&protected_data;
}

data_wrapper wrapper;
void foolish()
{
    wrapper.process_data(malicious_func);   // 2.传递一个用户函数
    unprotected->do_something();            // 3.在无保护的情况下访问保护函数
}

// 定义线程安全的堆栈
struct empty_stack:std::exception
{
    const char* what() const throw();  // ?
};

template<class T>
class threadsafe_stack
{
    public:
    threadsafe_stack();
    threadsafe_stack(const threadsafe_stack&);
    threadsafe_stack& operator=(const thread_local&)=delete;

    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T& value);
    bool empty()const;
};

// 扩充（线程安全）堆栈
struct empty_stack:std::exception
{
    const char* what() throw()
    {
        return "empty stack!";
    }
};

template<class T>
class threadsafe_stack
{
    private:
    std::stack<T> data;
    mutable std::mutex m;

    public:
    threadsafe_stack():data(std::stack<T>()){};
    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> guard(m);
        data=other.data;
    }

    threadsafe_stack& operator=(const threadsafe_stack&)=delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> guard(m);
        data.push(new_value);
    }

    // 注：使用make_shared<>申请内存一次：效率高；且异常安全
    // 其缺点就是：1.当所创建的类只有保护或者私有的构造函数则无法使用make_shared()；
    // 2.原本强引用减为0,就会调用析构，现在需要弱引用（依旧保留控制块）、强引用都减为0才能调用析构，延长了保留内存的时间。
    // 但使用new 分配内存需要两次分配内存，容易造成内存泄漏；
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> guard(m);
        if(data.empty())throw empty_stack();

        std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在堆栈修改前，分配出返回值
        data.pop();
        return res;
    }

    void pop(T& value)
    {
        if(data.empty())throw empty_stack();
        
        value=data.top();
        data.pop();
    }

    bool empty()const
    {
        std::lock_guard<std::mutex> guard(m);
        return data.empty();
    }
};

// 死锁及其解决方案
// 在参数交换之后,两个线程试图在相同的两个实例之间
// 进行数据交换,程序死锁.可使用std::lock解决.

// 这里的std::lock()需要包含<mutex>头文件
class some_big_object;
void swap(some_big_object& lhs,some_big_object& rhs);
class X
{
private:
  some_big_object some_detail;
  std::mutex m;
public:
  X(some_big_object const& sd):some_detail(sd){}

  friend void swap(X& lhs, X& rhs)
  {
    if(&lhs==&rhs)
      return;
    std::lock(lhs.m,rhs.m); // 1
    std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock); // 2
    std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock); // 3
    swap(lhs.some_detail,rhs.some_detail);
  }
};

// 避免死锁的进阶指导:
// 1.避免嵌套锁;
// 2.避免在持有锁时调用用户提供的代码;
// 3.使用固定顺序上锁;
// 4.使用锁的层级结构:

// 简单层级互斥量实现:
class hierarchical_mutex
{
    std::mutex internel_mutex;

    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;

    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation()
    {
        if(this_thread_hierarchy_value<=hierarchy_value)
        {
            throw logic_error("mutex hierarchy violated");
        }
    }

    void update_hierarchy_value()
    {
        previous_hierarchy_value=this_thread_hierarchy_value;
        this_thread_hierarchy_value=hierarchy_value;
    }

    public:
    explicit hierarchical_mutex(unsigned long value):hierarchy_value(value),
    previous_hierarchy_value(0){};

    void lock()
    {
        check_for_hierarchy_violation();
        internel_mutex.lock();
        update_hierarchy_value();
    }

    void unlock()
    {
        this_thread_hierarchy_value=previous_hierarchy_value;
        internel_mutex.unlock();
    }

    bool try_lock()
    {
        check_for_hierarchy_violation();
        if(!internel_mutex.try_lock())
        {
            return false;
        }
        update_hierarchy_value();
        return true;
    }
};

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);
/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-26 14:56:12
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-26 17:08:50
 * @FilePath: \C-plus-plus\data_structure\Tree\Stack.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef STACK_H_
#define STACK_H_

#include <iostream>

using namespace std;

template <class T>
class Stack
{
private:
    T **stack;
    int top;
    int stacksize;

public:
    Stack(int initialcapacity = 15);
    ~Stack();

    bool empty() const { return top == -1; }
    bool full() const { return top == stacksize - 1; }
    void push(T *);
    void pop(T **);
    T *gettop() const;
};

template <class T>
T *Stack<T>::gettop() const
{
    if (empty())
    {
        cout << "The stack has been empty." << endl;
        // return;
    }
    return stack[top];
}

template <class T>
Stack<T>::Stack(int initialcapacity)
{
    stacksize = initialcapacity;
    top = -1;
    stack = new T *[stacksize];
    for (int i = 0; i < stacksize; ++i)
        stack[i] = nullptr;
}
template <class T>
Stack<T>::~Stack()
{
    for (int i = 0; i < stacksize; ++i)
        delete stack[i];
    delete[] stack;
}

template <class T>
void Stack<T>::push(T *obj)
{
    if (full())
    {
        cout << "The stack has been full";
        return;
    }
    stack[++top] = obj;
}

template <class T>
void Stack<T>::pop(T **obj)
{
    if (empty())
    {
        cout << "The stack is empty" << endl;
        return;
    }
    *obj = stack[top--];
}

#endif
/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-07 17:22:03
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-09 19:34:13
 * @FilePath: \C-plus-plus\data_structure\stack\Stack.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "..\Linerlist\linerlist.cpp"
template <class T>
class Stack
{
public:
    virtual ~Stack(){};
    virtual void push(const T &) = 0;
    virtual void pop() = 0;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T &top() = 0; // return the top element
};

template <class T>
class derivedarraystack : public Stack<T>, private arrayList<T>
{
public:
    // invoke arrayList's constructor
    derivedarraystack(int initialCapacity) : arrayList<T>(initialCapacity){};
    bool empty() const { return arrayList<T>::empty(); }
    int size() const { return arrayList<T>::size(); }
    T &top();
    void pop();
    void push(const T &theElement) { insert(arrayList<T>::size(), theElement); };
};
template <class T>
T &derivedarraystack<T>::top()
{
    if (empty())
    {
        cout << "The stack is empty." << endl;
        return arrayList<T>::arrayList(0);
    }
    return get(arrayList<T>::size() - 1);
}
template <class T>
void derivedarraystack<T>::pop()
{
    if (empty())
    {
        cout << "The stack is empty." << endl;
        return;
    }
    erase(arrayList<T>::size() - 1);
}

// another method
template <class T>
class arrayStack : public Stack<T>
{
    int stacktop;
    T *stack;
    int arrayLenth;

    void changeLenth(T *, int, int);

public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack();

    bool empty() const { return stacktop == -1; }
    T &top();
    void push(const T &);
    void pop();
    int size() const { return arrayLenth; }
};
template <class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    arrayLenth = initialCapacity;
    stacktop = -1;
    stack = new T[initialCapacity];
}

template <class T>
arrayStack<T>::~arrayStack()
{
    delete[] stack;
}

template <class T>
T& arrayStack<T>::top() 
{
    if (stacktop == -1)
        return *(this->stack);
    return stack[stacktop];
}

template <class T>
void arrayStack<T>::push(const T &theElement)
{
    if (stacktop == arrayLenth - 1)
    {
        changeLenth(stack, arrayLenth, 2 * arrayLenth);
        arrayLenth *= 2;
    }
    stack[++stacktop] = theElement;
}

template <class T>
void arrayStack<T>::pop()
{
    if (stacktop == -1)
        return;
    stack[stacktop--].~T();
}

template <class T>
void arrayStack<T>::changeLenth(T *thearray, int current, int thenew)
{
    T *temp = new T[thenew];
    std::copy(thearray, thearray + current, temp);
    for (int i = 0; i < current; ++i)
        thearray[i].~T();
    thearray = temp;
}

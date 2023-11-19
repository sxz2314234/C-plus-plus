#include<iostream>

using std::cout;
using std::endl;

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

template<class T>
class linkedStack:Stack<T>
{
    private:
    // private scope defination
    struct Node
    {
        T item;
        Node* next;

        Node(const T& theElement)
        {
            item=theElement;
            next=nullptr;
        }
    };
    // private data member
    Node* stackTop;
    int stackSize;

    public:
    linkedStack();
    ~linkedStack();

    void push(const T&);
    void pop();
    bool empty()const;
    int size()const;
    T& top();
};

template<class T>
linkedStack<T>::linkedStack()
{
    stackSize=0;
    stackTop=nullptr;
}

template<class T>
linkedStack<T>::~linkedStack()
{
    while(stackTop!=nullptr)
    {//delete the top point of stack
        Node* temp=stackTop->next;
        delete stackTop;
        stackTop=temp;
    }
}

template<class T>
void linkedStack<T>::push(const T& theElement)
{
    if(empty())
    {
        stackSize++;
        stackTop=new Node(theElement);
    }
    Node* temp=new Node(theElement);
    temp->next=stackTop;
    stackTop=temp;
}

template<class T>
void linkedStack<T>::pop()
{
    if(empty())
    {
        cout<<"The stack has been empty."<<endl;
        return;
    }
    Node* temp=stackTop->next;
    delete stackTop;
    stackTop=temp;
    stackSize--;
}
template<class T>
T& linkedStack<T>::top()
{
    return stackTop->item;
}

template<class T>
int linkedStack<T>::size()const
{
    return stackSize;
}

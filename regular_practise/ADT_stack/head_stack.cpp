// stack.h --class defination for the stack ADT
#ifndef _STACK
#define _STACK

template<class T>
class stock
{
private:
    /* data */
    int top;  //index for top stack item
    enum {Max=10};  //constant specific to class
    T items[Max];  //holds stack items
public:
    stock(/* args */);
    bool ifempty()const{return top==-1;}
    bool iffull()const;
    bool push(const T);  //add item to stack
    bool pop(T&);  //pop top into item
};
#endif

template<class T>
stock<T>::stock()
{
    top=0;
}
template<class T>
bool stock<T>::iffull()const
{
    return top==Max;
}

template<class T>
bool stock<T>::push(const T item)
{
    if(iffull())return false;
    else
    {
        items[top++]=item;
        return true;
    }
}
template<class T>
bool stock<T>::pop(T& item)
{
    if(ifempty())return false;
    else
    {
        item=items[top--];
        return true;
    }
}
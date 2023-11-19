#include"head_stack.cpp"
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
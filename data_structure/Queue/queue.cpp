/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-09 20:43:49
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-10 17:16:18
 * @FilePath: \C-plus-plus\data_structure\stack\Queue\Queue.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include"virQueue.cpp"
#include<iostream>

template<class T>
class arrayQueue:public queue<T>
{
    T* queue;
    int que_Size;
    int que_Lenth;

    int front;
    int rear;

    void copy(T*,T*,T*);
    void changeSize();
    public:
    arrayQueue(int initialCapacity=10);
    arrayQueue(const arrayQueue&);
    ~arrayQueue();

    arrayQueue<T>& operator=(const arrayQueue<T>&);
    arrayQueue<T> operator+(const arrayQueue<T>&)const;
    int size()const{return que_Size;}
    bool empty()const{return que_Lenth==0;}
    bool full()const{return que_Lenth==que_Size-1;}
    void pop(T&);
    void push(const T&);
};

template<class T>
arrayQueue<T>::arrayQueue(int initalCapacity)
{
    que_Size=initalCapacity;
    que_Lenth=0;
    front=-1;
    rear=-1;
    queue=new T[initalCapacity];
}

template<class T>
arrayQueue<T>::arrayQueue(const arrayQueue<T>& thedup)
{
    que_Size=thedup.que_Size;
    que_Lenth=thedup.que_Lenth;
    queue=new T[que_Size];
    copy(thedup.queue,thedup.queue+thedup.que_Lenth,queue);
}
template<class T>
arrayQueue<T>::~arrayQueue()
{
    delete[] queue;
}

template<class T>
void arrayQueue<T>::pop(T &thepop)
{
    if(empty())
    {
        std::cout<<"The queue is empty."<<std::endl;
        return;
    }
    thepop=queue[front];
    front=(front+1)%que_Size;
    que_Lenth--;
}

template<class T>
void arrayQueue<T>::push(const T&theElement)
{
    if(full())
    {
        std::cout<<"The queue is full."<<std::endl;
        return;
    }
    if(front==-1)front++;
    rear=(rear+1)%que_Size;
    queue[rear]=theElement;
    que_Lenth++;
}

template<class T>
arrayQueue<T> arrayQueue<T>::operator+(const arrayQueue<T>& theque)const
{
    arrayQueue<T> temp(que_Size+theque.que_Size);
    int i=0;
    int j=front;
    while(i++<que_Lenth)
    {
        T obj=queue[j];
        temp.push(obj);
        j=(j+1)%que_Size;
    }
    i=0;
    j=theque.front;
    while (i++<theque.que_Lenth)
    {
        /* code */
        T obj=theque.queue[j];
        temp.push(obj);
        j=(j+1)%theque.que_Size;
    }
    return temp;
}

template<class T>
arrayQueue<T>& arrayQueue<T>::operator=(const arrayQueue<T>&thedup)
{
    if(&thedup==this)return *this;
    delete[] queue;
    que_Lenth=thedup.que_Lenth;
    que_Size=thedup.que_Size;
    front=thedup.front;
    rear=thedup.rear;
    queue=new T[que_Size];
    copy(thedup.queue,thedup.queue+thedup.que_Lenth,queue);
}

template<class T>
void arrayQueue<T>::copy(T* start,T* end,T* target)
{
    T* pointer=start;
    while(pointer!=end)
    {
        *target=*pointer;
        target++;
        pointer++;
    }
}

template<class T>
void arrayQueue<T>::changeSize()
{
    T* thenew=new T[2*que_Size];

    if(front<rear)
    copy(queue,queue+que_Lenth,thenew);
    else
    {
        copy(queue+front,queue+que_Size,thenew);
        copy(queue,queue+rear,thenew+que_Size-front+1);
    }

    front=0;
    rear=que_Lenth;
    que_Lenth*=2;
    delete[] queue;
    queue=thenew;
}
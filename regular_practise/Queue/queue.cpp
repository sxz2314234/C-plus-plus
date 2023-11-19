#include <iostream>

using std::cout;
using std::endl;

template <class T>
class queue
{
public:
    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual int queuecount() const = 0;
    virtual bool enqueue(const T &) = 0;
    virtual bool dequeue(T &) = 0;
    virtual ~queue() = 0;
};

template <class T>
class linkedqueue : queue<T>
{
private:
    // class scope defination
    struct Node
    {
        T item;
        Node *next;

        Node(const T &theElement)
        {
            item = theElement;
            next = nullptr;
        }
    };
    enum
    {
        Q_size = 10
    };
    // private class members
    Node *front;
    Node *rear;
    int items;
    const int qsize;

public:
    linkedqueue(int quesize = Q_size);
    ~linkedqueue();
    bool empty() const;
    bool full() const;
    bool dequeue(T &);
    bool enqueue(const T &);
    int queuecount() const;
};
template <class T>
// the const member must use initial list to initialize it
// the same to the reference
linkedqueue<T>::linkedqueue(int quesize) : qsize(quesize)
{
    items = 0;
    front = rear = nullptr;
}

template <class T>
int linkedqueue<T>::queuecount() const
{
    if (rear == nullptr)
        return 0;
    Node *pointer = front;
    int count = 1;
    while (pointer != rear)
    {
        pointer = pointer->next;
        ++count;
    }
    return count;
    // return items;
}
template <class T>
bool linkedqueue<T>::empty() const
{
    return front == rear;
    // return items==0
}
template <class T>
bool linkedqueue<T>::full() const
{
    return queuecount() == qsize;
}
template <class T>
bool linkedqueue<T>::dequeue(T &deport)
{
    if (empty())
    {
        cout << "There is no node." << endl;
        return false;
    }
    Node *temp = front;
    deport = front->item;
    front = front->next;
    delete temp;
    // items--;
    return true;
}
template <class T>
bool linkedqueue<T>::enqueue(const T &theElement)
{
    if (full())
    {
        cout << "The queue has been full." << endl;
        return false;
    }
    if (empty())
        front = rear = new Node(theElement);
    else
    {
        Node *thenew = new Node(theElement);
        rear->next = thenew;
        rear = rear->next;
    }
    // items++;
    return true;
}

// the destructor ensure to be destroyed when it come to deadline.
template<class T>
linkedqueue<T>::~linkedqueue()
{
    while(front!=nullptr)
    {
        Node* temp=front;
        front=front->next;
        delete temp;
    }
}
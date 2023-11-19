#include <iostream>
#include "linerlist.cpp"

using std::cout;

template <class T>
struct chainNode
{
    // data member
    T element;
    chainNode<T> *next;
    // constructor
    chainNode(T e, chainNode<T> *n=nullptr) : element(e), next(n){};
};

template <class T>
class chain : linerlist<T>
{
protected:
    int listsize;
    chainNode<T> *head;

public:
    chain(int initialcapacity=10);
    chain(const chain &);
    ~chain();
    // overload the derived
    bool empty() const { return listsize == 0; }
    int size() const { return listsize; }
    T &get(int theIndex) const;
    int indexof(const T &theelement) const;
    void erase(int theindex);
    void insert(int theindex, const T &theelement);
    void output(ostream &out) const;
    // void binSort(int range);
};

template <class T>
chain<T>::chain(int initialcapacity)
{
    if (initialcapacity < 1)
    {
        // // throw out the problem
        // ostringstream s;
        // s << "Initial capacity = " << initialcapacity << " Must be > 0.";
        // throw illegalParameterValue(s.str());
        cout<<"InitialCapacity must be > 0.";
    }
    listsize = 0;
    head = nullptr;
}
template <class T>
chain<T>::chain(const chain<T> &theList)
{
    listsize = theList.listsize;
    if (listsize = 0)
        head = nullptr;
    else
    {
        chainNode<T> *source = theList.head;
        chainNode<T> *firstnode = new chainNode<T>(source->element);
        chainNode<T> *targetnode = firstnode;
        source = source->next;
        while (source != nullptr)
        {
            targetnode->next = new chainNode<T>(source->element);
            targetnode = targetnode->next;
            source = source->next;
        }
        targetnode->next = nullptr;
    }
}
template <class T>
chain<T>::~chain()
{
    chainNode<T> *current = head;
    while (head != nullptr)
    {
        current = current->next;
        delete head;
        head = current;
    }
}

template <class T>
T &chain<T>::get(int theIndex) const
{
    if (theIndex > listsize)
    {
        cout << "The chain has not the index.";
        return head->element;
    }
    chainNode<T> *currentnode = head;
    for (int i = 0; i < theIndex; ++i)
        currentnode = currentnode->next;
    return currentnode->element;
}
template <class T>
int chain<T>::indexof(const T &theelement) const
{
    chainNode<T> *firstnode = head->next;
    int index = 1;
    while (firstnode != nullptr && firstnode->element != theelement.element)
    {
        firstnode = firstnode->next;
        ++index;
    }
    if (firstnode == nullptr)
        return -1;
    else
        return index;
}
template <class T>
void chain<T>::erase(int theindex)
{
    chainNode<T> *currentnode = head->next;
    if (theindex > listsize)
    {
        cout << "The chain has not the chainNode.";
        return;
    }
    int i = 0;
    while (i != theindex - 1)
        currentnode = currentnode->next;
    chainNode<T> *deletenode = currentnode->next;
    currentnode->next = currentnode->next->next;
    delete deletenode;
    listsize--;
}
template <class T>
void chain<T>::insert(int theindex, const T &theelement)
{
    chainNode<T> *currentnode = head->next;
    int index = 1;
    while (index != theindex - 1)
    {
        currentnode = currentnode->next;
        ++index;
    }
    chainNode<T> *insertnode = new chainNode<T>(theelement);
    insertnode->element = theelement;
    insertnode->next = currentnode->next;
    currentnode->next = insertnode->next;
}
template <class T>
void chain<T>::output(ostream &out) const
{
    for (chainNode<T> *currentnode = head->next; currentnode != nullptr; currentnode = currentnode->next)
        out << currentnode->element << " ";
}
template <class T>
ostream &operator<<(ostream &out, const chain<T> &node)
{
    node.output(cout);
    return out;
}

/*
template<class T>
void chain<T>::binSort(int range)
{
    chainNode<T>** bottom,**top;
    bottom=new chainNode<T>*[range+1];
    top=new chainNode<T>*[range+1];

    //initial the list bottom
    for(int i=0;i<=range;++i)
    bottom[i]=null;
    for(;firstnode!=null;firstnode=firstnode->next)
    {
        int thebin=firstnode->element;
        // thebin is empty
        if(bottom[thebin]==null)
        bottom[thebin]=top[thebin]=firstnode;
        else
        {
            top[thebin]->next=firstnode;
            top[thebin]=firstnode;
        }
    }

    // range the chaoic rank from the bin
    chainNode<T>*y=null;
    for(int thebin=0;thebin<=range;++thebin)
    {
        if(bottom[thebin]!=null)
        {
            if(y==null)               //this is the first no-empty bin
            firstnode=bottom[thebin];
            else
            y->next=bottom[thebin];
            y=top[thebin];
        }
    }
    if(y!=null)
    y->next=null;
    delete []bottom;
    delete []top;
}
*/
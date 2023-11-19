/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-15 16:16:22
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-07-15 20:41:35
 * @FilePath: \C-plus-plus\data_structure\doublychain.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include "linerlist.cpp"
using std::cout;

template <class T>
struct chainNode
{
    chainNode<T> *previous;
    chainNode<T> *next;
    T element;

    chainNode(T e, chainNode<T> *p, chainNode<T> *n) : previous(p), next(n), element(3){};
    chainNode(const chainNode<T> &duplication)
    {
        previous = duplication->previous;
        next = duplication->next;
        element = duplication;
    }
    chainNode(const T &duplication) { element = duplication; }
};

template <class T>
class doublychain : linerlist<T>
{
    chainNode<T> *first;
    chainNode<T> *last;

public:
    doublychain(chainNode<T> *f = null, chainNode<T> *l=null) : first(f), last(l){};
    doublychain(const doublychain<T> &);
    ~doublychain(){};

    bool empty() const;
    int size() const;
    T &get(int theindex) const;
    int indexof(const T &theelement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T &);
    void output(ostream &out)const;
};
template <class T>
doublychain<T>::doublychain(const doublychain<T> &dup)
{
    if (dup.last == null)
        first = last = null;
    else
    {
        chainNode<T> *current = new chainNode<T>(dup.first->element);
        chainNode<T> *dup_first = dup.first;
        first = current;
        current->previous = current;
        while (current->element != dup.last->element)
        {
            dup_first = dup_first->next;
            chainNode<T> *next = new chainNode<T>(dup_first->element);
            current->next = next;
            next->previous = current;
            current = current->next;
        }
    }
    current->next = current;
    last = current;
}
template <class T>
bool doublychain<T>::empty() const
{
    if (last == null)
        return true;
    else
        return false;
}
template <class T>
int doublychain<T>::size() const
{
    if (empty())
        return -1;
    int count = 1;
    while (first != last)
    {
        first = first->next;
        count++;
    }
    return count;
}
template <class T>
int doublychain<T>::indexof(const T &theElement) const
{
    if (empty())
        return -1;
    int index = 1;
    int Size = size();
    chainNode<T> *current = first;
    while ((index <= Size) && current->element != theElement)
        index++;
    if (index > Size)
        return -1;
    else
        return index;
}
template <class T>
T &doublychain<T>::get(int theIndex) const
{
    int chainsize = size();
    if (theIndex < 0 || theIndex > chainsize)
    {
        cout << "There is no such the index.";
        return *this;
    }
    int index;
    chainNode<T> *current = null;
    if (theIndex < chainsize)
    {
        current = first;
        for (index = 1; index < theIndex; ++index)
            current = current->next;
    }
    else
    {
        current = last;
        for (index = chainsize; index > theIndex; --index)
            current = current->previous;
    }
    return *current;
}
template <class T>
void doublychain<T>::erase(int theindex)
{
    int chainsize = size();
    if (theIndex < 0 || theIndex > chainsize)
    {
        cout << "There is no such the index.";
        return *this;
    }
    chainNode<T> *deletenode = &(get(theindex));
    chainNode<T> *prenode = deletenode->previous;
    chainNode<T> *denode = deletenode->next;
    prenode->next = denode;
    denode->previous = prenode;
    delete deletenode;
}
template <class T>
void doublychain<T>::insert(int theIndex, const T &theElement)
{
    int chainsize = size();
    if (theIndex < 0 || theIndex > chainsize)
    {
        cout << "There is no such the index.";
        return *this;
    }
    chainNode<T> *current = &get(theIndex);
    chainNode<T> *prenode = current->previous;
    chainNode<T> *copy = new chainNode<T>(theElement);
    prenode->next = copy;
    copy->previous = prenode;
    copy->next = current;
}
template <class T>
ostream &operator<<(ostream &out, const doublychain<T> &x)
{
    x.output(out);
    return out;
}
template <class T>
void doublychain<T>::output(ostream &out)const
{
    chainNode<T> *current = first;
    while (current != last)
        out << current->element << " ";
}

int main()
{
    doublychain<int> thechain;
}
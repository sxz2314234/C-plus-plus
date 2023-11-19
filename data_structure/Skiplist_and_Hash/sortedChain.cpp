/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-14 17:20:51
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-23 10:27:05
 * @FilePath: \C-plus-plus\data_structure\Skiplist_and_Hash\sortedChain.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%A
 */

/*
If we want to use the special template 
to dispose some special data type,instead of using normal template,
we can specialize the template to overrid the template.
for example:
template<class K,E>
class chain<pair<K,E>>
{
    // the  concret data lines;
}
*/ 

#include<iostream>
#include "ABC_Dictionary.cpp"
#include <utility>
#include<string>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::pair;

template<class T>
struct chainNode
{
    /* data */
    T element;
    chainNode<T>* next;
    chainNode(T& e,chainNode<T>* n=nullptr):element(e),next(n){};
};

// overrid the class chain
template<class K,class E>
class chain
{
    protected:
    int listsize;
    chainNode<pair<K,E>>* head;

    public:
    chain();
    chain(const chain<K,E>&);
    ~chain();
    bool empty()const{return listsize==0;}
    bool size()const{return listsize;}
    void insert(pair<K,E>&);
    void erase(const K&);
    void chainput()const;
};
template<class K,class E>
chain<K,E>::chain()
{
    listsize=0;
    head=nullptr;
}

template<class K,class E>
chain<K,E>::chain(const chain<K,E>&thechain)
{
    listsize=thechain.listsize;
    if(thechain.empty())head=nullptr;
    else
    {
        head=new chainNode<pair<K,E>>(thechain.head->element);
        chainNode<pair<K,E>>*pointer=thechain.head->next;
        chainNode<pair<K,E>>*np=head;
        while(pointer!=nullptr)
        {
            chainNode<pair<K,E>>*thenext=new chainNode<pair<K,E>>(pointer->element);
            np->next=thenext;
            np=np->next;
            pointer=pointer->next;
        }
    }
}

template<class K,class E>
void chain<K,E>::insert(pair<K,E>&thepair)
{
    chainNode<pair<K,E>>*pointer=head;
    while(pointer!=nullptr)
    {
        if(pointer->element.first==thepair.first)
        {
            pointer->element.second=thepair.second;
            return;
        }
        pointer=pointer->next;
    }
    pointer=new chainNode(thepair,head);
    head=pointer;
    listsize++;
}

template<class K,class E>
void chain<K,E>::erase(const K&thekey)
{
    // the chain is empty.
    if(empty())return;

    //the pointer to be deleted is in the first 
    if(head->element.first==thekey)
    {
        chainNode<pair<K,E>>*thedelete=head;
        head=head->next;
        delete thedelete;
        listsize--;
        return;
    }

    chainNode<pair<K,E>>*pointer=head->next;
    chainNode<pair<K,E>>*prepointer=head;
    while(pointer!=nullptr)
    {
        if(pointer->element.first==thekey)
        {
            prepointer->next=pointer->next;
            delete pointer;
            listsize--;
            return;
        }
        prepointer=pointer;
        pointer=pointer->next;
    }
}

template<class K,class E>
void chain<K,E>::chainput()const
{
    chainNode<pair<K,E>>* pointer=head;
    while(pointer!=nullptr)
    {
        cout<<"Thekey: "<<pointer->element.first<<endl
        <<"Thevalue: "<<pointer->element.second<<endl;
        pointer=pointer->next;
    }
}

template<class K,class E>
chain<K,E>::~chain()
{
    if(listsize!=0)
    {
        chainNode<pair<K,E>>*pointer=head;
        pointer=pointer->next;
        delete head;
        listsize--;
        while(listsize!=0)
    {
        chainNode<pair<K,E>>* pnext=pointer;
        pointer=pointer->next;
        delete pnext;
        listsize--;
    }
    }
}

// the inheritance expample
template <class K, class E>
class sortedChain : public chain<K, E>
{
public:
    sortedChain(){};
    sortedChain(const sortedChain<K,E> &schain) : chain<K, E>::chain(schain){};
};

int lim = 4;

int main()
{
    sortedChain<string, int> schain;
    for (int i = 0; i < lim; ++i)
    {
        cout << "Please enter the employee's name: ";
        string name;
        cin >> name;
        pair<string, int> thepair(name, i);
        schain.insert(thepair);
    }
    schain.chainput();
}
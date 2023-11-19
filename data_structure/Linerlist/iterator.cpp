/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-13 17:22:51
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-03 14:11:32
 * @FilePath: \C-plus-plus\data_structure\Linerlist\iterator.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<iostream>
#include<string>

using namespace std;

class Rank
{
    string name;
    int score;
    // constructor
    public:
    Rank(string n,int s):name(n),score(s){};
    void show(){cout<<name;}
};

template<class T>
class Iterator
{
    T* iterator;

    public:
    // constructor
    Iterator(T* initial=NULL):iterator(initial){};

    //member function
    T& operator*(){return *iterator;}
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    T& operator[](int i){return iterator[i];}
    bool operator==(const Iterator<T>& op){return iterator==op.iterator;}
    bool operator!=(const Iterator<T>& op){return iterator!=op.iterator;}

    template<class U>
    friend ostream& operator<<(ostream&,Iterator<U>&);
};

template<class T>
Iterator<T>& Iterator<T>::operator++()
{
    ++iterator;
    return *this;
}
template<class T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> old=*this;
    ++iterator;
    return old;
}

template<class T>
Iterator<T>& Iterator<T>::operator--()
{
    --iterator;
    return *this;
}
template<class T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator<T>temp=*this;
    ++iterator;
    return temp;
}
template<class U>
ostream& operator<<(ostream& out,Iterator<U>&obj)
{
    obj.iterator->show();
    return out;
}

int main()
{
    Rank class_1[]={{"sxz",100},{"glp",99},{"sxf",98}};
    Iterator<Rank> IT(class_1);
    // const Iterator<Rank> Lim(class_1+3);
    for(;IT!=(class_1+3);++IT)
    cout<<IT;
}
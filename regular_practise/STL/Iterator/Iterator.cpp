/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-30 10:25:35
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-09-03 16:25:45
 * @FilePath: \C-plus-plus\regular_practise\STL\Iterator\Iterator.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// Iterator.cpp --realize my_vector class containing an nested iterator class
#include<iostream>
#include<algorithm>
#include<iterator>

using std::begin;
using std::end;

template<class T>
class my_vector
{
    private:
    // private member
    int vector_size;
    int array_size;
    T* array;

    public:
    // nested class
    class iterator
    {
        private:
        T* pt;
        public:
        iterator(T*p=nullptr):pt(p){};
        
        iterator& operator++()
        {
            ++pt;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            pt++;
            return temp;
        }
        T& operator*();
        iterator& operator=(const iterator&);
        bool operator!=(const iterator&)const;
    };

    // memeber method
    my_vector(int size=10);
    ~my_vector();

    void push_back(const T&);
    void erase(int);
    T operator[](int);
    T* begin()const;
    T* end()const;
};

template<class T>
using mv_iter=typename my_vector<T>::iterator;

template<class T>
T my_vector<T>::operator[](int i)
{
    return array[i];
}

template<class T>
my_vector<T>::my_vector(int size)
{
    vector_size=size;
    array_size=0;
    array=new T[vector_size];
}

template<class T>
my_vector<T>::~my_vector()
{
    delete[] array;
}

template<class T>
void my_vector<T>::push_back(const T&obj)
{
    if(array_size==vector_size)
    {
        std::cout<<"The vector has been full.\n";
        return;
    }

    array[array_size++]=obj;
}

template<class T>
void my_vector<T>::erase(int i)
{
    if(i<0||i>array_size-1)
    throw "Out of bundary.";

    std::copy(array[i],array[i]+array_size,array[i-1]);
    array_size--;
}

template<class T>
T* my_vector<T>::begin()const
{
    return &array[0];
}

template<class T>
T* my_vector<T>::end()const
{
    return &array[vector_size];
}

// template<class T>
// mv_iter<T>& my_vector<T>::iterator::operator++()
// {
//     ++pt;
//     return *this;
// }

// template<class T>
// mv_iter<T> my_vector<T>::iterator::operator++(int)
// {
//     iterator* temp(pt);
//     pt++;
//     return pt;
// }

template<class T>
T& my_vector<T>::iterator::operator*()
{
    return *pt;
}

template<class T>
typename my_vector<T>::iterator& my_vector<T>::iterator::operator=(const iterator&obj)
{
    pt=obj.pt;
    return *this;
}

template<class T>
bool my_vector<T>::iterator::operator!=(const iterator&obj)const
{
    return pt!=obj.pt;
}

// template<class T>
// std::ostream& operator<<(std::ostream&out,const T&obj)
// {
//     out<<obj;
//     return out;
// }
/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-16 08:59:16
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-22 16:14:16
 * @FilePath: \C-plus-plus\data_structure\Skiplist_and_Hash\Hash.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include "ABC_Dictionary.cpp"
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::hash;
using std::ostream;
using std::pair;
using std::string;

template <class K, class E>
class hashTable : public dictionary<K, E>
{
    pair<const K, E> **table; // Hash Table
    int dSize;                // size of the hash table
    int divisior;             // divisior in hash table
protected:
    int search(const K &key);
    int stringToint(const string &str);

public:
    hashTable(int divisior);
    ~hashTable() { delete[] table; }
    int size() const { return dSize; }
    bool empty() const { return dSize == 0; }
    bool full() const { return dSize == divisior; }
    pair<const K, E> *find(const K &);
    void erase(const K &);
    void insert(pair<const K, E> &);

    template <class M, class N>
    friend ostream &operator<<(ostream &out, const hashTable<M, N> &thash);
};

template <class K, class E>
int hashTable<K, E>::stringToint(const string &str)
{
    int Length = (int)str.length();
    int answer = 0;
    if (Length % 2 != 0)
    {
        answer = str.at(Length - 1);
        Length--;
    }
    for (int i = 0; i < Length; i += 2)
    {
        answer += str.at(i);
        answer += ((int)str.at(i + 1)) << 8;
    }
    return answer < 0 ? -answer : answer;
}

template <class K, class E>
int hashTable<K, E>::search(const K &key)
{
    int i = stringToint(key);
    i %= divisior;
    int j = i;

    do
    {
        /* code */
        if (table[j] != nullptr && table[j]->first == key)
            return j;
        j = (j + 1) % divisior;
    } while (j != i);
    return j;
}

template <class K, class E>
hashTable<K, E>::hashTable(int div)
{
    divisior = div;
    dSize = 0;

    table = new pair<const K, E> *[divisior];
    for (int i = 0; i < divisior; ++i)
        table[i] = nullptr;
}

template <class K, class E>
pair<const K, E> *hashTable<K, E>::find(const K &key)
{
    int i = search(key);

    if (table[i] == nullptr && table[i]->first != key)
        return nullptr;
    else
        return table[i];
}

template <class K, class E>
void hashTable<K, E>::erase(const K &key)
{
    int i = search(key);
    pair<const K, E> *thedelete = nullptr;
    if (table[i] != nullptr && table[i]->first == key)
    {
        delete table[i];
        dSize--;
    }
}

template <class K, class E>
void hashTable<K, E>::insert(pair<const K, E> &thepair)
{
    int j = search(thepair.first);
    if (table[j] == nullptr)
    {
        table[j] = new pair<const K, E>(thepair);
        dSize++;
    }
    else if (table[j]->first == thepair.first)
    {
        table[j]->second = thepair.second;
    }
    else
        cout << "The hash table is full.";
}

int lim = 4;

int main()
{
    hashTable<string, int> schain(lim);
    for (int i = 0; i < lim; ++i)
    {
        cout << "Please enter the employee's name: ";
        string name;
        cin >> name;
        pair<const string, int> thepair(name, i);
        schain.insert(thepair);
    }
    cout << schain;
}

template <class M, class N>
ostream &operator<<(ostream &out, const hashTable<M, N> &thash)
{
    pair<const M, N> **pointer = thash.table;
    for (int i = 0; i < lim; ++i)
    {
        if (pointer[i] == nullptr)
            continue;
        out << pointer[i]->first << ": "
            << pointer[i]->second << std::endl;
    }
    return out;
}
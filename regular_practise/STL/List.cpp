// List.cpp --using a list
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

void outint(int n) { cout << n << " "; }

int main()
{
    list<int> one(5, 2); // list of 5 2s
    int stuff[5] = {1, 2, 4, 8, 6};
    list<int> two;
    two.insert(two.begin(), stuff, stuff + 5);
    int more[6] = {6, 4, 2, 4, 6, 5};
    list<int> three(two);
    three.insert(three.end(), more, more + 6);

    cout << "List one: ";
    for_each(one.begin(), one.end(), outint);
    cout << endl
         << "List two: ";
    for_each(two.begin(), two.end(), outint);
    cout << endl
         << "List three: ";
    for_each(three.begin(), three.end(), outint);

    // the remove function prototype:
    // void remove(const T&val)
    three.remove(2);
    cout << endl
         << "List three minus 2s: ";
    for_each(three.begin(), three.end(), outint);

    // the splice function prototype:
    // void splice(iterator pos,list<T,Alloc>x)
    // insert the x before the pos,then x is empty
    three.splice(three.begin(), one);
    cout << endl
         << "List three after spclice: ";
    for_each(three.begin(), three.end(), outint);
    cout << endl
         << "List one: ";
    for_each(one.begin(), one.end(), outint);

    // the unique function prototype:
    // void unique();
    //
    three.unique();
    cout << endl
         << "List three after unique: ";
    for (auto x : three)
        cout << x << " ";

    // the sort function prototype:
    // void sort();
    // sort according to operator<
    three.sort();
    three.unique();
    cout << endl
         << "List three after sort & unique: ";
    for (auto pt = three.begin(); pt != three.end(); pt++)
        cout << *pt << " ";
    two.sort();

    // the merge function prototype:
    // void merge(list<T,Alloc>&x)
    // the two list must be sorted.
    // After merging, the x is empty and the object which invokes two is in order.
    three.merge(two);
    cout << endl
         << "Sorted two merged into three: ";
    for (auto x : three)
        cout << x << " ";
    cout << endl;

    return 0;
}
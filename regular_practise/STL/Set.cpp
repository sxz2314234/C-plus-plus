/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-09-03 19:50:32
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-09-03 20:28:36
 * @FilePath: \C-plus-plus\regular_practise\STL\Set.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// set.cpp --some set operations
// the set itself can sort.
#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<iterator>

using namespace std;

int main()
{
    const int N=6;
    string s1[N]={"buffoon","thinkers","for","heavy","can","for"};
    string s2[N]={"metal","any","food","elegant","deliver","for"};

    set<string> A(s1,s1+N);
    set<string> B(s2,s2+N);

    ostream_iterator<string, char> out(cout," ");
    cout<<"Set A:";
    copy(A.begin(),A.end(),out);
    cout<<endl;
    cout<<"Union of A and B:\n";
    set_union(A.begin(),A.end(),B.begin(),B.end(),out);
    cout<<endl;

    cout<<"Intersection of A and B:\n";
    set_intersection(A.begin(),A.end(),B.begin(),B.end(),out);
    cout<<endl;

    set<string> C;
    cout<<"Set C:\n";
    set_union(A.begin(),A.end(),B.begin(),B.end(),insert_iterator<set<string>>(C,C.begin()));
    // the function set_difference() is same to it.
    copy(C.begin(),C.end(),out);
    cout<<endl;

    string s3("grungy");
    C.insert(s3);
    cout<<"Set C after insertion:\n";
    copy(C.begin(),C.end(),out);
    cout<<endl;

    cout<<"Showing a range:\n";
    copy(C.lower_bound("ghost"),C.upper_bound("spook"),out);
    cout<<endl;

    return 0;
}
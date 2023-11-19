/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-04 15:28:55
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-07 17:50:59
 * @FilePath: \C-plus-plus\regular_practise\String_folder\String_main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// test--sxz string

#include <iostream>
#include "String.cpp"

using std::cout;
using sxz::String;

void callname(String &);

int main()
{
    String name1("Hello World");
    String name2;
    cin >> name2;
    cout << name1 + name2;
    // cout<<name1<<endl;
    // callname(name2);
    // cout<<String::num_strings;
}
void callname(String &name)
{
    cout << name << endl;
}
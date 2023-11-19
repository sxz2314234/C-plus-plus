/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-06-17 14:01:16
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-09-06 19:29:14
 * @FilePath: \C++d:\gitee\test_c\test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
using namespace std;
int main()
{
    char ch;
    int count = 0;
    // 通过while循环识别文本
    while (cin.get(ch))
    {
        cout << ch;
        count++;
    }
    /*
    并且可通过重定向运算符从文本输入
    cin.get(ch);
    while(cin.fail()==false)  cin.fail()函数判断是否到文章末尾
    {
        cout<<ch;
        count++;
        cin.get(ch);
    }
    */
    cout << endl
         << count << "characters reader\n";
    return 0;
}

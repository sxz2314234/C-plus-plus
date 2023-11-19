/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-08 17:36:11
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-09 10:27:23
 * @FilePath: \C-plus-plus\data_structure\stack\simplifiedcomputer.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <cstring>
#include "Stack.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

const int stackLIM = 15;

arrayStack<char> str(stackLIM);
arrayStack<int> number(stackLIM);

int count(string);

int main()
{
    cout << "Please enter the caculation problem: " << endl;
    string caculation;
    cin >> caculation;
    cout << "The result is: ";
    cout << count(caculation);
}

int count(string obj)
{
    int result = 0;
    int i = 0;
    char ch;
    char top;
    while (obj[i] != '\0')
    {
        ch = obj[i];
        if ('0' <= ch && ch <= '9')
            number.push(int(ch-'0'));
        else
        {
            switch (ch)
            {
            case '*':
            case '/':
                str.push(ch);
                break;
            case '+':
            case '-':
                top = str.top();
                if (top == '*' || top == '\\')
                {
                    str.pop();
                    int num1 = number.top();
                    number.pop();
                    int num2 = number.top();
                    number.pop();
                    number.push(num1 + num2);
                }
                str.push(ch);
                break;
            case '(':
                str.push(ch);
                break;
            case ')':
                while (str.top() != '(')
                {
                    top=str.top();
                    str.pop();
                    int num1 = number.top();
                    number.pop();
                    int num2 = number.top();
                    number.pop();
                    switch (top)
                    {
                    case '+':
                        number.push(num1 + num2);
                        break;
                    case '-':
                        number.push(num2 - num1);
                        break;
                    case '*':
                        number.push(num1 * num2);
                        break;
                    case '/':
                        number.push(num2 / num1);
                        break;
                    }
                }
                str.pop();
                break;
            default:
                break;
            }
        }
        i++;
    }
    while (!str.empty())
    {
        top = str.top();
        str.pop();
        int num1 = number.top();
        number.pop();
        int num2 = number.top();
        number.pop();
        switch (top)
        {
        case '+':
            number.push(num1 + num2);
            break;
        case '-':
            number.push(num2 - num1);
            break;
        case '*':
            number.push(num1 * num2);
            break;
        case '/':
            number.push(num2 / num1);
            break;
        }
    }
    return number.top();
}
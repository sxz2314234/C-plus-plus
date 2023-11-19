/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-09-09 09:42:06
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-09-09 11:01:21
 * @FilePath: \C-plus-plus\regular_practise\File\File_inorout\py_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// py_test.cpp --use cpp to out the python data
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;
const int Size = 50;

int main()
{
    string filename;
    cout << "Enter name for new file: ";
    cin >> filename;

    // creat output stream object for new file and call it fin
    ofstream fout(filename.c_str());
    string data;
    // Enter the python code you want
    while(getline(cin,data)&&data!="#")
    fout<<data;
    fout.close();

    // creat input stream object for new file and call it cin
    ifstream fin(filename.c_str());
    cout << "Here are the contents of " << filename << ":\n";
    char ch;
    while (fin.get(ch))
        cout << ch;
    fin.close();
    cout << "Done!\n";

    return 0;
}
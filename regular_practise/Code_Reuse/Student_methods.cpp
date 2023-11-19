/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-15 14:33:20
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-15 15:55:43
 * @FilePath: \C-plus-plus\regular_practise\Code_Reuse\student_methods.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

// Student_methods.cpp --Student class using containment
#include <iostream>
#include "Student.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

ostream &Student::arr_out(ostream &out) const
{
    int lim = scores.size();
    if (lim > 0)
    {
        for (int i = 0; i < lim; ++i)
        {
            out << scores[i] << " ";
            if (i % 5 == 4)
                out << endl;
        }
        if (i % 5 != 0)
            out << endl;
    }
    else
        cout << "empty array.";
    return out;
}

double Student::Average() const
{
    if (scores.size() > 0)
        return scores.sum() / scores.size();
    else
        return 0;
}

const string &Student::Name() const
{
    return name;
}

istream &operator>>(istream &in, Student &stu)
{
    cout << "The student'name is: ";
    in >> stu.name;
    return in;
}

ostream &operator<<(ostream &out, const Student &stu)
{
    out << "The student'name is: " << stu.name << endl;
    stu.arr_out(out);
    return out;
}

double newStudent::Average() const
{
    if (ArrayDb::size() > 0)
        return ArrayDb::sum() / ArrayDb::size();
    else
        return 0;
}

istream &operator>>(istream &in, newStudent &stu)
{
    in >> (string &)stu;
    return in;
}

const string &newStudent::Name() const
{
    // After type conversion,the result is member,string.
    return (const string &)*this;
}

ostream &newStudent::arr_out(ostream &out)
{
    int lim = ArrayDb::size();
    if (lim > 0)
    {
        for (int i = 0; i < lim; ++i)
        {
            out << ArrayDb::operator[](i) << " ";
            if (i % 5 == 4)
                out << endl;
        }
        if (i % 5 != 0)
            out << endl;
    }
    else
        out << "empty array.";
    return out;
}

ostream &operator<<(ostream &out, const newStudent &stu)
{
    out << "The student's name is: " << (string &)stu << endl;
    stu.arr_out(out);
    return out;
}
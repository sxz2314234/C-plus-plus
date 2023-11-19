/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-10 15:51:44
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-07-28 16:01:27
 * @FilePath: \data_structure\test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// Radix Sort
#include <iostream>

const int Lim = 10;

struct radix
{
    /* data */
    int score;
    radix *next;
    radix()
    {
        score = 0;
        next = NULL;
    }
    radix(int s)
    {
        score = s;
        next = NULL;
    }
};

bool checkindex(int x, radix *first);
void radix_sort(radix *, int, int);
int get(int, int);
void insert(int, radix &, radix *);
void erase(int);
int Period(radix *);
int exponentiation(int radix, int p);

int main()
{
    int list[10] = {8, 93, 27, 461, 298, 739, 38, 46, 981, 100};
    radix *first = new radix(8);
    radix *head = first;
    for (int i = 1; i < 10; ++i)
    {
        radix *next = new radix(list[i]);
        first->next = next;
        first = first->next;
    }
    first = head;
    radix_sort(first, 10, 10);
    first = head;
    while (first != NULL)
    {
        std::cout << first->score << ' ';
        first = first->next;
    }
    first = head;
    radix *next = head->next;
    while (next != NULL)
    {
        delete first;
        first = next;
        next = next->next;
    }
    delete first;
    return 0;
}

bool checkindex(int n, radix *first)
{
    int i = 1;
    radix *temp = first;
    if (temp == NULL)
        return false;
    while (i++ < n)
    {
        temp = temp->next;
        if (temp == NULL)
            return false;
    }
    return true;
}

void insert(int n, radix &obj, radix *first)
{
    if (!checkindex(n, first))
        return;
    int i = 1;
    radix *temp = first;
    while (i++ < n - 1)
        temp = temp->next;
    obj.next = temp->next;
    temp->next = &obj;
}

int Period(radix *obj)
{
    int Max = obj->score;
    radix *head = obj->next;
    while (head != NULL)
    {
        if (Max < head->score)
            Max = head->score;
        head = head->next;
    }
    int count = 1;
    while (Max)
    {
        Max /= 10;
        if (Max)
            count++;
    }
    return count;
}

void erase(int n, radix *&first)
{
    if (!checkindex(n, first))
        return;
    radix *head = first;
    if (n == 1)
    {
        first = first->next;
        return;
    }
    int index=1;
    while(index<n-1)
    {
        head=head->next;
        index++;
    }
    radix* temp=head->next;
    head->next=temp->next;
    delete temp;
}

int get(int x, int radix)
{
    int number[3] = {0};
    for (int i = 0; i < 3; ++i)
    {
        int temp = x / 10;
        number[i] = x - temp * 10;
        x /= 10;
    }
    switch (radix)
    {
    case 10:
        return number[0];
    case 100:
        return number[1];
    case 1000:
        return number[2];
    default:
        return -1;
    }
}

int exponentiation(int radix, int p)
{
    int period = 3;
    int dup_radix = radix;
    p = period - p - 1;
    while (p--)
        radix = dup_radix * radix;
    return radix;
}

void radix_sort(radix *arr, int _radix, int n)
{
    radix **bottom = new radix *[_radix];
    radix **top = new radix *[_radix];
    radix *connect = NULL;
    int exp = 0;
    int index = 0;
    int period = Period(arr);
    while (period--)
    {
        exp = exponentiation(_radix, period);
        for (int i = 0; i < n; i++)
        {
            top[i] = NULL;
            bottom[i] = NULL;
        }
        for (int i = 0; i < n; ++i)
        {
            index = get(arr->score, exp);
            if (top[index] == NULL)
            {
                top[index] = bottom[index] = arr;
                erase(1, arr);
            }
            else
            {
                bottom[index]->next = arr;
                bottom[index] = arr;
                erase(1, arr);
            }
        }
        connect = NULL;
        for (int theBin = 0; theBin <= _radix; ++theBin)
        {
            if (top[theBin] != NULL)
            {
                if (connect == NULL)
                    arr = top[theBin];
                else
                    connect->next = top[theBin];
                connect = bottom[theBin];
            }
        }
    }
   
    delete[] bottom;
    delete[] top;
}
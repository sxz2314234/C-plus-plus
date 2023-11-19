#include <iostream>
using namespace std;

const int Size = 10;

int *Rank(int *, int size);
void output(int *a, int size);
void s_sort(int *a, int size);

int main()
{
    int a[Size] = {8, 2, 37, 4, 89, 1, 38, 9, 3, 10};
    int *ranked = new int[Size];
    int *sorted = new int[Size];
    s_sort(a, Size);
    ranked = Rank(a, Size);
    cout << endl;
    for (int i = 0; i < Size; ++i)
        sorted[ranked[i]] = a[i];
    cout << "The original premutation is ";
    output(a, Size);
    cout << endl;
    cout << "Now,it has been sorted: ";
    output(sorted, Size);
}
// ranking sort
int *Rank(int *a, int size)
{
    int *temp = new int[size];
    for (int i = 0; i < size; ++i)
        temp[i] = 0;
    for (int i = 1; i < size; ++i)
        for (int j = 0; j < i; ++j)
            if (a[j] <= a[i])
                temp[i]++;
            else
                temp[j]++;
    return temp;
}
void output(int *a, int size)
{
    for (int i = 0; i < size; ++i)
        cout << a[i] << ' ';
}
// in-place rearrangement
void rearrange(int *a, int *ranked, int size)
{
    for (int i = 0; i < size; ++i)
        while (ranked[i] != i)
        {
            int temp = ranked[i];
            swap(a[i], a[temp]);
            swap(ranked[i], ranked[temp]);
        }
}
// selection sort
void s_sort(int *a, int size)
{
    bool is_sorted = false;
    for (int i = size-1; !is_sorted&&(i > 0); --i)
    {
        int indexofmax = 0;
        is_sorted = true;
        for (int j = 1; j <= i; j++)
            if (a[indexofmax] <= a[j])
                indexofmax = j;
            else
                is_sorted = false;
        swap(a[indexofmax], a[i]);
    }
    output(a, size);
}

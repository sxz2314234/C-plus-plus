#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void build_maxPriorityqueue(vector<int> &, vector<int> &);
void insert(int, vector<int> &);
inline void show_queue(const int point)
{
    cout << point << " ";
}

int main()
{
    vector<int> init{-1, 20, 12, 35, 15, 10, 80, 30, 17, 2, 1};
    vector<int> max_PriorityQueue(init.size());

    build_maxPriorityqueue(init, max_PriorityQueue);
    for_each(max_PriorityQueue.begin(), max_PriorityQueue.end(), show_queue);
}

void build_maxPriorityqueue(vector<int> &init, vector<int> &queue)
{
    for (auto p = init.begin() + 1; p != init.end(); ++p)
    {
        insert(*p, queue);
    }
}

void insert(int value, vector<int> &queue)
{
    int count = 1;
    while (queue[count] != 0)
        count++;
    queue[count] = value;

    if (count == 1)
        return;

    while (count != 1 && queue[count / 2] < value)
    {
        queue[count] = queue[count / 2];
        count /= 2;
    }
    queue[count] = value;
}
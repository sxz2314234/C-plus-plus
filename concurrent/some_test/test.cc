<<<<<<< HEAD
// parallel accumulate
=======
// parallel add calculation
>>>>>>> 61ee45c200824df34102d32447d667def8ada964

#include <iostream>
#include <thread>
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>

using namespace std;

template <class Iterator, class T>
class block_accumulate
{
public:
    void operator()(Iterator first, Iterator last, T &result)
    {
        result = accumulate(first, last, result);
    }
};

template <class Iterator, class T>
T parallel_advance(Iterator first, Iterator last, T init)
{
    unsigned long const length = distance(first, last);
    if (!length)
        return init;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length - 1 + min_per_thread) / min_per_thread;

    unsigned long const hard_ware = thread::hardware_concurrency();
    unsigned long const num_threads = min(hard_ware != 0 ? hard_ware : 2, max_threads);

    vector<T> results(num_threads);
    vector<thread> threads(num_threads - 1);

    unsigned long const block_size = length / num_threads;

    Iterator block_start = first;
    for (int i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        advance(block_end, block_size);

        threads[i] = thread(block_accumulate<Iterator, T>(), block_start, block_end, ref(results[i]));

        block_start = block_end;
    }

    block_accumulate<Iterator, T>()(block_start, last, ref(results[num_threads - 1]));

    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    return accumulate(results.begin(), results.end(), init);
}

int main()
{
    vector<int> add = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto x : add)
        cout << x << " ";
    cout << endl;

    cout << parallel_advance<vector<int>::iterator, int>(add.begin(), add.end(), 0);
}

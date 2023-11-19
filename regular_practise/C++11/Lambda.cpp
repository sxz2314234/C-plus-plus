// Lambda.cpp --use captured variables
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

const long Size = 390000L;

int main()
{
    using std::cout;
    std::vector<int> number(Size);

    std::srand(std::time(0));
    std::generate(number.begin(), number.end(), std::rand);
    cout << "Sample size = " << Size << '\n';

    // using lambdas
    int count3 = std::count_if(number.begin(), number.end(), [](int x)
                               { return x % 3 == 0; });
    cout << "Count of numbers divisible by 3: " << count3 << '\n';
    int count13 = 0;
    std::for_each(number.begin(), number.end(), [&count13](int x)
                  { count13 += x % 13 == 0; });
    cout << "Count of numbers divisible by 3: " << count3 << '\n';
    cout << "Count of numbers divisible by 13: " << count13 << '\n';
    return 0;
}
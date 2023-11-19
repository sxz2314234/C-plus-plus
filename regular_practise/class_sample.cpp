#include <iostream>
#include <string>
using namespace std;

class loop
{
    string name;
    int radius;

public:
    loop(string n = "empty", int r = 0) : radius(r), name(n){};
    // function overloading
    void reset(int r) { radius = r; }
    void reset(string new_name) { name = new_name; }
    int get_radius() { return radius; }
};

int main()
{
    loop loop1{"sxz", 20};
    loop *loop2 = new loop("sxz2", 30);
    cout << loop1.get_radius() << endl;
    cout << loop2->get_radius() << endl;
}

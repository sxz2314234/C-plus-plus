// stdmove.cpp -- using std::move()
#include <iostream>
#include <utility>

// interface
class Useless
{
private:
    int n;         // number of elements
    char *pc;      // pointer of data
    static int ct; // number of objects
    void ShowObject() const;

public:
    Useless();
    explicit Useless(int);
    Useless(int, char);
    Useless(const Useless &); // regular copy constructor
    Useless(Useless &&);      // move constructor
    ~Useless();
    Useless operator+(const Useless &) const;
    Useless &operator=(const Useless &); // copy assignment
    Useless &operator=(Useless &&);      // move assignment
    void ShowData() const;
};

// implementation
int Useless::ct = 0;

Useless::Useless()
{
    ++ct;
    n = 0;
    pc = nullptr;
}

Useless::Useless(int k) : n(k)
{
    ct++;
    pc = new char[n];
}

Useless::Useless(int k, char ch) : n(k)
{
    ++ct;
    pc = new char[n];
    for (int i = 0; i < n; ++i)
        pc[i] = ch;
}

Useless::Useless(const Useless &us) : n(us.n)
{
    ct++;
    pc = new char[n];
    for (int i = 0; i < n; ++i)
        pc[i] = us.pc[i];
}

Useless::Useless(Useless &&us) : n(us.n)
{
    ++ct;
    pc = us.pc; // steal address
    us.n = 0;
    us.pc = nullptr; // give old object nothing in return
}

Useless::~Useless()
{
    delete[] pc;
}

Useless &Useless::operator=(const Useless &us)
{
    std::cout << "copy assignment operator called:\n";
    if (this == &us)
        return *this;
    delete[] pc;
    n = us.n;
    pc = new char[n];
    for (int i = 0; i < n; ++i)
        pc[i] = us.pc[i];
    return *this;
}

Useless &Useless::operator=(Useless &&us) // move assignment
{
    std::cout << "move assignment operator called:\n";
    if (this == &us)
        return *this;
    delete[] pc;
    n = us.n;
    pc = us.pc;
    us.n = 0;
    us.pc = nullptr;
    return *this;
}

Useless Useless::operator+(const Useless &f) const
{
    Useless temp = Useless(n + f.n);
    for (int i = 0; i < n; ++i)
        temp.pc[i] = pc[i];
    for (int i = n; i < temp.n; ++i)
        temp.pc[i] = f.pc[i - n];
    return temp;
}

void Useless::ShowObject() const
{
    std::cout << "Number of elements: " << n;
    std::cout << " Data address: " << (void *)pc << std::endl;
}

void Useless::ShowData() const
{
    if (n == 0)
        std::cout << "(Object empty)";
    else
        for (int i = 0; i < n; i++)
            std::cout << pc[i];
    std::cout << std::endl;
}

// application
int main()
{
    using std::cout;
    {
        Useless one(10, 'x');
        Useless two(one); // calls move constructor
        cout << "Object one: ";
        one.ShowData();
        Useless three, four;
        cout << "three = one\n";
        three = one; // automatic copy assignment
        cout << "now object three = ";
        one.ShowData();
        cout << "four = one + two\n";
        four = one + two; // automatic move assignment
        cout << "now object four = ";
        four.ShowData();
        cout << "four = std::move(one)\n";
        four = std::move(one); // forced move assignment
        cout << "now object four = ";
        four.ShowData();
        cout << "and object one = ";
        one.ShowData();
    }
}
template <class T>
class Iterator
{
public:
    T *iterator;

    // constructor
    Iterator(T *initial = NULL) : iterator(initial){};

    // member function
    T &operator*() { return *iterator; }
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
    T &operator[](int i) { return iterator[i]; }
    bool operator==(const Iterator<T> op) { return iterator == op.iterator; }
    bool operator!=(Iterator<T> op) { return iterator != op.iterator; }

    template <class U>
    friend ostream &operator<<(ostream &, U &);
};

template <class T>
Iterator<T> &Iterator<T>::operator++()
{
    ++iterator;
    return *this;
}
template <class T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> old = *this;
    ++iterator;
    return old;
}

template <class T>
Iterator<T> &Iterator<T>::operator--()
{
    --iterator;
    return *this;
}
template <class T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator<T> temp = *this;
    ++iterator;
    return temp;
}

// template<class U>
// ostream& operator<<(ostream&out,U&obj)
// {

// }
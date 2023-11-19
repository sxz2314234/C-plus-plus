#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::hash;
using std::ostream;
using std::pair;
using std::string;

template <class K, class E>
class Hashchains
{
    // the nested class
    class Node
    {
    public:
        pair<const K, E> element;
        Node *next;
        Node(pair<const K, E> &e, Node *n = nullptr) : element(e), next(n){};
    };

    Node **table;
    int divisior;
    int hashsize;

    int stringToint(const string &str);

public:
    Hashchains(int d = 5);
    Hashchains(const Hashchains<K, E> &);
    ~Hashchains();

    int size() const { return hashsize; }
    bool empty() const { return hashsize == 0; }
    pair<const K, E> *find(const K &);
    void erase(const K &);
    void insert(pair<const K, E> &);

    template<class U,class V>
    friend ostream& operator<<(ostream&out,const Hashchains<U,V>&hashchain);
};
template <class K, class E>
Hashchains<K, E>::Hashchains(int d)
{
    divisior = d;
    hashsize = 0;
    table = new Node *[divisior];
    for (int i = 0; i < divisior; ++i)
        table[i] = nullptr;
}

template <class K, class E>
Hashchains<K, E>::Hashchains(const Hashchains<K, E> &hchain)
{
    divisior = hchain.divisior;
    hashsize = hchain.hashsize;
    table = new Node *[divisior];
    Node *point = nullptr;
    Node *tpoint = nullptr;
    for (int i = 0; i < divisior; i++)
    {
        if (hchain.table[i] == nullptr)
            continue;
        point = hchain.table[i];
        tpoint = table[i];
        while (point != nullptr)
        {
            if (tpoint == nullptr)
                tpoint = new Node(point->element);

            tpoint->next = new Node(point->element);
            tpoint = tpoint->next;
            point = point->next;
        }
    }
}
template <class K, class E>
Hashchains<K, E>::~Hashchains()
{
    for (int i = 0; i < divisior; ++i)
    {
        if (table[i] == nullptr)
            continue;
        Node *point = table[i];
        Node *prepoint = nullptr;
        while (point != nullptr)
        {
            prepoint = point;
            point = point->next;
            delete prepoint;
        }
    }
    delete[] table;
}

template <class K, class E>
int Hashchains<K, E>::stringToint(const string &str)
{
    int Length = (int)str.length();
    int answer = 0;
    if (Length % 2 != 0)
    {
        answer = str.at(Length - 1);
        Length--;
    }
    for (int i = 0; i < Length; i += 2)
    {
        answer += str.at(i);
        answer += ((int)str.at(i + 1)) << 8;
    }
    return answer < 0 ? -answer : answer;
}

template <class K, class E>
pair<const K, E> *Hashchains<K, E>::find(const K &thekey)
{
    int intkey = stringToint(thekey)%divisior;
    Node *target = table[thekey];
    while (target != nullptr)
    {
        if (target->element.first == thekey)
            return target;
        target = target->next;
    }
    cout << "The hash hasn't the pair." << endl;
    return nullptr;
}

template <class K, class E>
void Hashchains<K, E>::insert(pair<const K, E> &thepair)
{
    int intkey = stringToint(thepair.first)%divisior;
    if (table[intkey] == nullptr)
    {
        table[intkey] = new Node(thepair);
        hashsize++;
        return;
    }
    else
    {
        Node *point = table[intkey];
        while (point != nullptr && point->element.first != thepair.first)
            point = point->next;
        if (point != nullptr && point->element.first == thepair.first)
            point->element.second = thepair.second;
        else
            table[intkey]->next = new Node(thepair, table[intkey]->next);
        hashsize++;
    }
}

template <class K, class E>
void Hashchains<K, E>::erase(const K &thekey)
{
    int intkey = stringToint(thekey)%divisior;
    Node *target = table[intkey];
    if (target == nullptr)
        return;
    else if (target->element.first == thekey)
    {
        table[intkey] = table[intkey]->next;
        delete target;
        hashsize--;
    }
    else
    {
        Node *pretarget = nullptr;
        while (target != nullptr)
        {
            pretarget = target;
            target = target->next;
            if (target->element.first == thekey)
                pretarget->next = target->next;
            delete target;
            hashsize--;
        }
    }
}

int lim = 4;

int main()
{
    Hashchains<string, int> schain(lim);
    for (int i = 0; i < lim; ++i)
    {
        cout << "Please enter the employee's name: ";
        string name;
        cin >> name;
        pair<const string, int> thepair(name, i);
        schain.insert(thepair);
    }
    cout << schain;
}

template<class U,class V>
ostream& operator<<(ostream&out,const Hashchains<U,V>&hashchain)
{
    for(int i=0;i<hashchain.divisior;++i)
    {
        if(hashchain.table[i]==nullptr)continue;
        typename Hashchains<U,V>::Node* point=hashchain.table[i];
        while (point!=nullptr)
        {
            /* code */
            cout<<"The pair'key is: "<<point->element.first<<endl
            <<"The pair'value is: "<<point->element.second<<endl;
            point=point->next;
        }
    }
    return out;
}
// RTTI.cpp --Runtime type identification
// using dynamic_cast,typeid,and type_info
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<typeinfo>

using namespace std;

class Grand
{
    int hold;
    public:
    Grand(int h=0):hold(h){};

    virtual void speak()const{cout<<"I am a grand class.\n";}
    virtual int Value()const{return hold;}
};

class Superb:public Grand
{
    public:
    Superb(int h=0):Grand(h){};
    void speak()const{cout<<"I am a superb class.\n";}
    virtual void say()const{cout<<"I hold the superb value of "<<Value()<<"!\n";}
};

class Magnificant:public Superb
{
    char ch;
    public:
    Magnificant(int h=0,char cv='A'):Superb(h),ch(cv){};

    void speak()const{cout<<"I am a magnificant class.\n";}
    void say()const{cout<<"I hold the character "<<ch<<" and the integer "<<Value()<<"!\n";}
};

Grand* GetOne();

int main()
{
    srand(time(0));
    Grand* pg;
    Superb* ps;

    for(int i=0;i<4;++i)
    {
        pg=GetOne();
        cout<<"Now processing type "<<typeid(*pg).name()<<".\n";
        pg->speak();
        if(ps=dynamic_cast<Superb*>(pg))
        ps->say();
        if(typeid(Magnificant)==typeid(*pg))
        cout<<"Yes,you're really magnificant.\n";
    }
}

Grand* GetOne()
{
    Grand*p;
    switch(rand()%3)
    {
        case 0:
        p=new Grand(rand()%100);
        break;
        case 1:
        p=new Superb(rand()%100);
        break;
        case 2:
        p=new Magnificant(rand()%100);
        break;
    }
    return p;
}
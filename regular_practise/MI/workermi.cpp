// workermi.cpp --working class methods with MI
#include"workwemi.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;
// worker methods
// protected methods
void worker::Data()const
{
    cout<<"Name: "<<fullname<<endl;
    cout<<"Employee ID: "<<id<<endl;
}

void worker::Set()
{
    getline(cin,fullname);
    cout<<endl;
    cout<<"Employee's id: ";
    cin>>id;
    while(cin.get()!='\n')
    continue;
}

// waiter methods
void waiter::Set()
{
    cout<<"Enter waiter's name: ";
    worker::Get();
    Get();
}

void waiter::Show()const
{
    cout<<"Catagory:Waiter\n";
    worker::Data();
    Data();
}

// protected methods
void waiter::Data()const
{
    cout<<"Panache rating: "<<panache<<endl;
}

void waiter::Get()
{
    cout<<"Enter waiter's panache rating: ";
    cin>>panache;
    while(cin.get()!='\n')continue;
}

char* singer::pv[singer::Vtypes]={"other","alto","contralto","soprano","bass","baritone","tenor"};

// singer methods
void singer::Show()const
{
    cout<<"Catagory: Singer\n";
    worker::Data();
    Data();
}

void singer::Set()
{
    cout<<"Enter the singer's name: ";
    worker::Get();
    Get();
}
// protected methods
void singer::Data()const
{
    cout<<"Vocal range: "<<pv[voice]<<endl;
}

void singer::Get()
{
    cout<<"Enter number for singer's vocal range:\n";
    int i=0;
    for(;i<Vtypes;++i)
    {
        cout<<i<<": "<<pv[i]<<" ";
        if(i%4==3)cout<<endl;
    }
    if(i%4!=0)cout<<'\n';
    cin>>voice;
    while(cin.get()!='\n')continue;
}

// singingwaiter methods
void singingwaiter::Set()
{
    cout<<"Enter singing waiter's name: ";
    worker::Get();
    Get();
}
void singingwaiter::Get()
{
    waiter::Get();
    singer::Get();
}

void singingwaiter::Data()const
{
    waiter::Data();
    singer::Data();
}

void singingwaiter::Show()const
{
    cout<<"Catagory: Singing waiter\n";
    worker::Data();
    Data();
}
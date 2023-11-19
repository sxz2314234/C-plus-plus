// bank accout class methods

#include<iostream>
#include"acctabc.h"

using std::cout;
using std::ios_base;
using std::endl;
using std::string;

// Abstract Base Class
AcctABC::AcctABC(const string&s,long an,double bal)
{
    fullname=s;
    acctNum=an;
    balance=bal;
}

void AcctABC::Deposit(double atm)
{
    if(atm<0)
    cout<<"Negative deposit not allowed; "
    <<"deposit is cancelled.\n";
    else 
    balance+=atm;
}

void AcctABC::Withdraw(double atm)
{
    balance-=atm;
}
// protected methods for formatting
AcctABC::Formatting AcctABC::SetFormat()const
{
    //set up ###.## format
    Formatting f;
    f.flag=cout.setf(ios_base::fixed,ios_base::floatfield);
    f.pr=cout.precision(2);
    return f;
}

void AcctABC::Restore(Formatting&f)const
{
    cout.setf(f.flag,ios_base::floatfield);
    cout.precision(f.pr);
}

// Brass methods
void Brass::Withdraw(double atm)
{
    if(atm<0)
    cout<<"Withdrawal amount must be positive; "
    <<"Withdrawal cancelled.\n";
    else if(atm<=Balance())
    AcctABC::Withdraw(atm);
    else
    cout<<"Withdrawal amount of $"<<atm
    <<" exceed your balance.\n"
    <<"Withdrawal cancelled.\n";
}

void Brass::ViewAcct()const
{
    Formatting f=SetFormat();
    cout<<"Brass Client: "<<FullName()<<endl;
    cout<<"Account Number: "<<AcctNum()<<endl;
    cout<<"Balance: $"<<Balance()<<endl;
    Restore(f);
}

// BrassPlus class methods
BrassPlus::BrassPlus(const Brass& ba,double ml,double r):AcctABC(ba)//use implict copy constructor
{
    maxLoan=ml;
    oweBank=0.0;
    rate=r;
}

BrassPlus::BrassPlus(const string& s,long an,double bal,double ml,double r):AcctABC(s,an,bal)
{
    maxLoan=ml;
    oweBank=0.0;
    rate=r;
}

void BrassPlus::ViewAcct()const
{
    Formatting f=SetFormat();
    cout<<"BrassPlus Client: "<<FullName<<endl;
    cout<<"Account Number: "<<AcctNum()<<endl;
    cout<<"Balance: $"<<Balance()<<endl;
    cout<<"Maxminum Loan: $"<<maxLoan<<endl;
    cout<<"Owed to Bank: $"<<oweBank<<endl;
    cout<<"Loan Rate: "<<100*rate<<endl;
    Restore(f);
}

void BrassPlus::Withdraw(double atm)
{
    Formatting f=SetFormat();

    double bal=Balance();
    if(atm<=bal)
    AcctABC::Withdraw(atm);
    else if(atm<=bal+maxLoan-oweBank)
    {
        double advance=atm-bal;
        oweBank+=advance*(1.0+rate);
        cout<<"Bank Advance: $"<<advance<<endl;
        cout<<"Finance charge: $"<<advance*rate<<endl;
        Deposit(advance);
        AcctABC::Withdraw(atm);
    }
    else
    cout<<"Credit limit exceeded. Transaction cancelled.\n";
    Restore(f);
}
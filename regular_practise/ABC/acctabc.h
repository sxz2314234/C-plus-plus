/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-11 15:39:59
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-09-07 19:20:51
 * @FilePath: \C-plus-plus\regular_practise\ABC\acctabc.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// ABC --Abstract Base Class
// bank accout classes
#ifndef ACCTABC_H_
#define ACCTABC_H_

#include <iostream>
#include <string>

// Abstract base class
class AcctABC
{
    std::string fullname;
    long acctNum;
    double balance;

protected:
    struct Formatting
    {
        /* data */
        std::ios_base::fmtflags flag;
        std::streamsize pr;
    };
    const std::string &FullName() const { return fullname; }
    long AcctNum() const { return acctNum; }
    Formatting SetFormat() const;
    void Restore(Formatting &f) const;

public:
    AcctABC(const std::string &s = "Nullbody", long an = -1, double bal = 0.0);
    void Deposit(double amt);
    virtual void Withdraw(double amt) = 0; // pure virtual function
    double Balance() const { return balance; }
    virtual void ViewAcct() const = 0;
    virtual ~AcctABC(){};
};

// Brass Account class
class Brass : public AcctABC
{
public:
    Brass(const std::string &s = "Nullbody", long an = -1, double bal = 0.0) : AcctABC(s, an, bal){};
    virtual void Withdraw(double atm);
    virtual void ViewAcct() const;
    virtual ~Brass();
};

// Brass Plus accout class
class BrassPlus : public AcctABC
{
    double maxLoan;
    double rate;
    double oweBank;

public:
    BrassPlus(const std::string &s = "Nullbody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.10);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.10);
    virtual void ViewAcct() const;
    virtual void Withdraw(double);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; }
    void ResetOwes() { oweBank = 0; }
};
#endif
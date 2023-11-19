/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-17 14:27:39
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-09-07 19:21:37
 * @FilePath: \C-plus-plus\regular_practise\MI\workwemi.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// workermi.h --working classes with MI
#ifndef WORKER_H_
#define WORKER_H_

#include <string>

using std::string;

class worker // an abstract base class
{
private:
    string fullname;
    long id;

protected:
    virtual void Data() const;
    virtual void Get();

public:
    worker() : fullname("no one"), id(0L){};
    worker(const string &s, long n) : fullname(s), id(n){};
    virtual ~worker() = 0 {}; // pure virtual function
    virtual void Show() const = 0;
    virtual void Set() = 0;
};

class waiter : public virtual worker
{
private:
    int panache;

protected:
    void Data() const;
    void Get();

public:
    waiter() : worker(), panache(0){};
    waiter(const string &s, long i, int pa) : worker(s, i), panache(pa){};
    waiter(const worker &wo, int pa) : worker(wo), panache(pa){};
    void Set();
    void Show() const;
};

class singer : virtual public worker
{
protected:
    enum
    {
        other,
        alto,
        contralto,
        soprano,
        bass,
        baritone,
        tenor
    };
    enum
    {
        Vtypes = 7
    };
    void Data() const;
    void Get();

private:
    static char *pv[Vtypes]; // string equives of voice types
    int voice;

public:
    singer() : worker(), voice(0){};
    singer(const string &s, long i, int v = other) : worker(s, i), voice(v){};
    singer(const worker &wo, int v = other) : worker(wo), voice(v){};
    void Show() const;
    void Set();
};

// multiple inheritance
class singingwaiter : public singer, public waiter
{
protected:
    void Data() const;
    void Get();

public:
    singingwaiter(){};
    singingwaiter(const string &s, long i, int p = 0, int v = other) : worker(s, i), waiter(s, i, p), singer(s, i, v){};
    singingwaiter(const worker &wk, int p = 0, int v = other) : worker(wk), waiter(wk, p), singer(wk, v){};
    singingwaiter(const singer &s, int p) : worker(s), singer(s), waiter(s, p){};
    singingwaiter(const waiter &s, int v) : worker(s), singer(s, v), waiter(s){};
    void Set();
    void Show() const;
};

#endif
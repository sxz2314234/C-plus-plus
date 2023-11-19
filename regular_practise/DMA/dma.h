// DMA,--inheritence and dynamic memory alloction

#ifndef DMA_H_
#define DMA_H_
#include<iostream>
using std::cout;
using std::endl;
using std::ostream;

// Base Class Using DMA
class baseDMA
{
    char* label;
    int rating;
    public:
    baseDMA(const char*l="null",int r=0);
    baseDMA(const baseDMA&);
    virtual ~baseDMA();
    baseDMA& operator=(const baseDMA&);
    friend ostream& operator<<(ostream&,const baseDMA&);
};

/*
derived class without DMA
no destructor needed
uses implicit copy constructor
using implicit assignment operator
*/
class lacksDMA:public baseDMA
{
    enum{COL_LEN=40};
    char color[COL_LEN];
    public:
    lacksDMA(const char*c="black",const char* l="null",int r=0);
    lacksDMA(const baseDMA&,const char* c="black");
    friend ostream& operator<<(ostream&,const lacksDMA&);
};

// derived from DMA
class hasDMA:public baseDMA
{
    char* style;
    public:
    hasDMA(const char* s="none",const char*l="null",int r=0);
    hasDMA(const hasDMA&);
    ~hasDMA();
    hasDMA& operator=(const hasDMA&);
    friend ostream& operator<<(ostream&,const hasDMA&);
};
#endif
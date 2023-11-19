// dma.cpp --dma class methods
#include"dma.h"
#include<cstring>

// baseDMA methods
baseDMA::baseDMA(const char*l,int r)
{
    label=new char[strlen(l)+1];
    strcpy(label,l);
    rating=r;
}

baseDMA::baseDMA(const baseDMA& bm)
{
    label=new char[strlen(bm.label)+1];
    strcpy(label,bm.label);
    rating=bm.rating;
}

baseDMA::~baseDMA()
{
    delete[] label;
}
baseDMA& baseDMA::operator=(const baseDMA&bm)
{
    if(this==&bm)return *this;
    delete[] label;
    label=new char[strlen(bm.label)+1];
    strcpy(label,bm.label);
}

ostream& operator<<(ostream& out,const baseDMA& bm)
{
    out<<"Label: "<<bm.label<<endl
    <<"Rating: "<<bm.rating<<endl;
    return out;
}

// derived class without DMA
lacksDMA::lacksDMA(const char*c,const char*l,int r):baseDMA(l,r)
{
    strcpy(color,c);
}

lacksDMA::lacksDMA(const baseDMA& bm,const char*c):baseDMA(bm)
{
    strcpy(color,c);
}

ostream& operator<<(ostream& out,const lacksDMA&lm)
{
    out<<(const baseDMA&)lm
    <<"Color: "<<lm.color<<endl;
    return out;
}
hasDMA::hasDMA(const char*s,const char*l,int r):baseDMA(l,r)
{
    style=new char[strlen(s)+1];
    strcpy(style,s);
}

// invoke the constructor of the base
// Then,we use the duplicate of the base to convert
// baseDMA from the hasDMA
hasDMA::hasDMA(const hasDMA& hm):baseDMA(hm)
{
    style=new char[strlen(hm.style)+1];
    strcpy(style,hm.style);
}

hasDMA::~hasDMA()
{
    delete[] style;
}
hasDMA& hasDMA::operator=(const hasDMA&hm)
{
    if(this==&hm)return *this;
    baseDMA::operator=(hm);  //invoke the operator=()emplicitly 
    style=new char[strlen(hm.style)+1];
    strcpy(style,hm.style);
    return *this;
}

ostream& operator<<(ostream& out,const hasDMA&hm)
{
    out<<(const baseDMA&)hm
    <<"Style: "<<hm.style<<endl;
}
// use a class--Time,show the friend function traits

#include<iostream>

// the declartion of class Time 
class Time
{
    int hours;
    int minutes;
    public:
    Time(int h=0,int m=0):hours(h),minutes(m){};
    void addMin(int m);
    void addHou(int h);
    void reset(int h,int m);
    Time operator+(const Time&)const;
    void show()const;
    Time operator*(double)const;
    friend Time operator*(double,Time&);
    friend std::ostream& operator<<(std::ostream&,const Time&);
};

// the member function of class Time
void Time::addHou(int h)
{
    hours+=h;
}
void Time::addMin(int m)
{
    minutes+=m;
    hours+=minutes/60;
    minutes%=60;
}
void Time::reset(int h,int min)
{
    hours=h;
    minutes=min;
}
Time Time::operator+(const Time&temp)const
{
    Time obj;
    int min=minutes+temp.minutes;
    int h=hours+temp.hours+min/60;
    min%=60;
    obj.hours=h;
    obj.minutes=min;
    return obj;
}
Time Time::operator*(double factor)const
{
    Time obj;
    long min=hours*factor*60+minutes*factor;
    obj.hours=min/60;
    obj.minutes=min%60;
    return obj;
}
Time operator*(double factor,const Time& obj)
{
    return obj*factor;
}
void Time::show()const
{
    std::cout<<"Now, The time is "<<hours<<" hours, "
    <<minutes<<"minutes"<<std::endl;
}

std::ostream& operator<<(std::ostream& os,const Time& obj)
{
    os<<obj.hours<<" hours, "<<obj.minutes<<"minutes."; 
    return os;
}
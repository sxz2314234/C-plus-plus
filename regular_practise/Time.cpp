// design a Time system,which can shift from two types

#include<iostream>

using std::cout;
using std::endl;
using std::ostream;
using std::cin;

class Time
{
    public:
    //this is a button,
    // that can shift from one mode to another mode
    enum Mode{hform,mform};  
private:
    // data
    int hours;
    int minutes;
    Mode mode;

    // method
    // output the Timeclass data
    float out_h()const{return float(hours)+float(minutes/60.0);}
    int out_m()const{return hours*60+minutes;}
    // input the Timeclass data
    void in_h(float);
    void in_m(int);

public:
    //constructor 
    Time(int h=0,int m=0,Mode mo=hform):hours(h),minutes(m),mode(mo){};

    // member function
    void resetMode(Mode m){mode=m;}

    Time operator+(const Time&)const;
    Time operator-(const Time&)const;
    explicit operator int(){return out_m();}
    explicit operator double(){return out_h();}

    // friend funtion
    friend ostream& operator<<(ostream&,const Time&);
    friend std::istream& operator>>(std::istream&,Time&);
};

void Time::in_h(float hour)
{
    hours=hour;
    minutes=(hour-hours)*60;
}

void Time::in_m(int min)
{
    hours=min/60;
    minutes=min%60;
}

Time Time::operator+(const Time&t)const
{
    if(t.mode!=mode)
    {
        cout<<"Please choose the unified time mode.";
        return 0;
    }
    Time time;
    int min=minutes+t.minutes;
    time.hours=hours+t.hours+min/60;
    time.minutes=min%60;
    time.mode=mode;
    return time;
}
Time Time::operator-(const Time&t)const
{
    if(t.mode!=mode)
    {
        cout<<"Please choose the unified time mode.";
        return 0;
    }
    Time time;
    int min1=out_m();
    int min2=t.out_m();
    int min0;
    min0=std::max(min1,min1)-std::min(min1,min2);
    time.hours=min0/60;
    time.minutes=min0%60;
    time.mode=mode;
    return time;
}

//There are two different mode to output
ostream& operator<<(ostream& out,const Time& time)
{
    if(time.mode==Time::hform)
    {
        float hour=time.out_h();
        out<<"This is "<<hour<<" hours"<<endl;
    }
    else
    {
        int min=time.out_m();
        out<<"This is "<<min<<" minutes."<<endl;
    }
    return out;
}
std::istream& operator>>(std::istream&in,Time& time)
{
    if(time.mode==Time::hform)
    {
        cout<<"Please enter a float representing hours: ";
        float hours;
        in>>hours;
        time.in_h(hours);
    }
    else 
    {
        cout<<"Please enter an integer representing minutes: ";
        int min;
        in>>min;
        time.in_m(min);
    }
    return in;
}

// // test
// int main()
// {
//     Time t1;
//     Time t2(2,30);
//     Time t3;
//     cin>>t3;
//     cout<<t1+t2;
//     t2.resetMode(Time::mform);
//     t3.resetMode(Time::mform);
//     cout<<t3+t2;
// }
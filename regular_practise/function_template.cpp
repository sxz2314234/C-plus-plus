//funtion template
#include<iostream>
#include<string>
using namespace std;

const int lim=5;

struct job
{
    string name;
    double salary;
    int floor;
};

//exchanging template
template <typename T>
void Swap(T &a,T &b);

//overload the Swap function above
template <typename T>
void Swap(T *,T *,int);

//explicit specialization
template<>void Swap(job& ,job&);

void show(int *,int);

int main()
{
    int i=10;
    int j=20;
    cout<<"i,j="<<i<<","<<j<<endl;
    Swap(i,j);
    cout<<"Now,i,j="<<i<<","<<j<<endl;
    
    float n=1.3;
    float m=1.4;
    cout<<"n,m="<<n<<","<<m<<endl;
    Swap(n,m);
    cout<<"Now,n,m="<<n<<","<<m<<endl;

    int arr[lim]={1,2,3,4,5}; 
    int arr1[lim]={6,7,8,9,10};
    cout<<"The first array is ";
    show(arr,lim);
    cout<<endl;
    cout<<"The second array is ";
    show(arr1,lim);
    cout<<endl;
    Swap(arr,arr1,lim);
    cout<<"The first array is ";
    show(arr,lim);
    cout<<endl;
    cout<<"The second array is ";
    show(arr1,lim);
    cout<<endl;

}
template <typename T>
void Swap(T &a,T &b)
{
    T temp;
    temp=a;
    a=b;
    b=temp;
} 
template <typename T>
void Swap(T *a,T *b,int n)
{
    int temp;
    for(int i=0;i<n;++i)
    {
        temp=a[i];
        a[i]=b[i];
        b[i]=temp;
    }
}

//swap just the salary and floor fields of a job structure 
template<> void Swap(job& j1,job& j2)
{
    int t1;
    double t2;
    t1=j1.floor;
    j1.floor=j2.floor;
    j2.floor=t1;
    t2=j1.salary;
    j1.salary=j2.salary;
    j2.salary=t2;
}

void show(int a[],int size)
{
    for(int i=0;i<size;++i)
    cout<<a[i]<<" ";
}
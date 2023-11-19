/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-05 16:25:01
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-07-05 17:08:37
 * @FilePath: \C-plus-plus\recursive_function.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

int Fabonacii(int num);
int factorial(int num);
void permutation(char list[],int k,int m);
#include<iostream>
#include<iterator>
using namespace std;
int main()
{
    int number;
    char list[3]={'a','b','c'};
    cout<<"please enter the number ";
    cin>>number;
    cout<<Fabonacii(number)<<endl;
    cout<<factorial(number)<<endl;
    permutation(list,0,2);
}
int Fabonacii(int num)
{
    if(num<3)
    {
        if(num==1)return 0;
        if(num==2)return 1;
    }
    return Fabonacii(num-1)+Fabonacii(num-2);
}
int factorial(int num)
{
    if(num==1||num==0)return 1;
    return num*factorial(num-1);
}
void permutation(char list[],int k,int m)
{//生成list[k:m]的所有排序
   if(k==m)
   {
       //list[k:m]仅有一个排列，输出它
       copy(list,list+m+1,ostream_iterator<char>(cout,""));
       cout<<endl;
   }
   else   //list[k:m]有多于一个的排列，递归地生成这些排列 
   for(int i=k;i<=m;++i)
   {
       swap(list[k],list[i]);
       permutation(list,k+1,m);
       swap(list[k],list[i]);
   }
}

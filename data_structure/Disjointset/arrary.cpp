/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-29 15:57:00
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-07-29 16:05:51
 * @FilePath: \C-plus-plus\data_structure\Disjointset\arrary.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//Algorithm implemented by array
int *equivClass;
int n;
void initialize(int numberOfElements)
{
    n=numberOfElements;
    equivClass=new int[n+1];
    for(int i=1;i<=n;++i)
    equivClass[i]=i;
}
void unite(int ClassA,int ClassB)
{
    //unite the ClassA and the ClassB
    // And we assume the ClassA is not equal to the ClassB
    for(int i=1;i<n;++i)
    if(equivClass[i]==ClassB)equivClass[i]=ClassA;
}
int find(int ClassA)
{
    return equivClass[ClassA];
}
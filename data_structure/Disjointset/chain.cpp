/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-29 16:06:16
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-11 16:51:07
 * @FilePath: \C-plus-plus\data_structure\Disjointset\chain.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//Algorithm implemented by chain
struct equivNode
{
    /* data */
    int equivnode;
    int size;
    int next;
};
int n;
equivNode *node;
void initialize(int numberOfElements)
{
    n = numberOfElements;
    node = new equivNode[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        node[i].equivnode = i;
        node[i].next = 0;
        node[i].size = 1;
    }
}
template <class T>
void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
void unite(int ClassA, int ClassB)
{
    // unite the ClassA and the ClassB
    // And we assume the ClassA is not equal to the ClassB

    // We make the ClassA the minium one
    int k;
    if (node[ClassA].size > node[ClassB].size)
        swap(ClassA, ClassB);
    for (k = ClassA; node[k].next != 0; k = node[k].next)
        node[k].equivnode = ClassB;
    node[k].equivnode = ClassB;

    // modify the size of new chain
    node[ClassB].size += node[ClassA].size;
    node[k].next = node[ClassB].next;
    node[ClassB].next = ClassA;
}
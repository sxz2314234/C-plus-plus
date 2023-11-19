/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-26 16:47:44
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-07-26 17:13:44
 * @FilePath: \C-plus-plus\data_structure\Bin_Sort\binsort.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// binsort.cpp
#include <iostream>
#include "binsort.h"
#include <string>

struct binsort
{
    /* data */
    int score;
    string *name;
    int operator!=(const studentRecord &x) const { return score != x.score; }
    operator int() const { return score; }
};

ostream &operator<<(ostream &out, const studentRecord &x)
{
    out << x.score << ' ' << *x.name << std::endl;
    return out;
}
void binSort(chain<studentRecord> &theChain, int range)
{
    chain<studentRecord> *bin = new chain<studentRecord>[range + 1];
    int numbersize = theChain.size();
    // take out the studentrecord from the chain,put them in the bin
    for (int i = 0; i < range; ++i)
    {
        studentRecord x = theChain.get(0);
        theChain.erase(0);
        bin[x.score].insert(0, x);
    }
    for (int i = range; i >= 0; --i)
        while (!bin[i].empty())
        {
            studentRecord x = bin[i].get(0);
            bin[i].erase(0);
            theChain.insert(0, x);
        }
    delete[] bin;
}
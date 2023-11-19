/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-07-26 16:41:09
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-14 16:31:03
 * @FilePath: \C-plus-plus\data_structure\Bin_Sort\binsort.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// binsort.h
#include"../Linerlist/ChainNode.cpp"
#include <string>
#include <iostream>

using std::ostream;
using std::string;

#ifndef STUDENTRECORD
#define STUDENTRECORD
struct studentRecord
{
    /* data */
    int score;
    string *name;

    int operator!=(const studentRecord &x) const;
    operator int() const;
};
#endif
ostream &operator<<(ostream &out, const studentRecord &x);
void binSort(chain<studentRecord>& theChain,int range);
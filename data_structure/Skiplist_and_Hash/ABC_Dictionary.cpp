/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-14 16:48:41
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-18 10:38:15
 * @FilePath: \C-plus-plus\data_structure\Skiplist_and_Hash\ABC_Dictionary.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// Abtract Base Class
#include<utility>
using std::pair;

template<class K,class E>
class dictionary
{
    public:
    virtual bool empty()const=0;
    virtual ~dictionary(){};
    virtual int size()const=0;
    virtual pair<const K,E>* find(const K&)=0;
    virtual void erase(const K&)=0;
    virtual void insert(pair<const K,E>&)=0;
};
/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-25 17:46:55
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-26 17:37:43
 * @FilePath: \C-plus-plus\data_structure\Tree\Build_tree.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// Build_tree.cpp --according to the set rule,build one tree.
#include <string>
#include "Stack.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <class T>
struct Treenode
{
    /* data */
    T element;
    Treenode *lchild;
    Treenode *rchild;

    Treenode(T &e) : element(e), lchild(nullptr), rchild(nullptr){};
    Treenode() : lchild(nullptr), rchild(nullptr){};
    Treenode(T &e, Treenode *l, Treenode *r) : element(e), lchild(l), rchild(r){};
};

void equal(const char a, const char b, int &k1, int &k2);
template <class T>
void output(const Treenode<T> *);

template <class T>
Treenode<T>* build_tree(Treenode<T> *root, const string &str)
{
    Stack<Treenode<T>> figure;
    Stack<Treenode<T>> sign;
    int i = 0;
    while (str[i] != '\0')
    {
        char ch = str[i];
        if ((0 <= (ch - 'a')) && ((ch - 'a') <= 25))
        {
            Treenode<T> *alph = new Treenode<T>(ch);
            figure.push(alph);
        }
        else if (sign.empty())
        {
            Treenode<T> *sign_obj = new Treenode<T>(ch);
            sign.push(sign_obj);
        }
        else
        {
            Treenode<T> *prech = nullptr;
            prech=sign.gettop();
            Treenode<T> *ch1 = nullptr;
            Treenode<T> *ch2 = nullptr;
            Treenode<T> *sign_obj = new Treenode<T>(ch);
            int k1, k2;
            equal(ch, prech->element, k1, k2);
            if (k1 == k2)
            {
                figure.pop(&ch1);
                figure.pop(&ch2);
                sign.pop(&prech);
                prech->lchild = ch2;
                prech->rchild = ch1;
                figure.push(prech);
            }
            else if (k1 < k2)

                while (sign.empty())
                {
                    sign.pop(&prech);
                    figure.pop(&ch1);
                    figure.pop(&ch2);
                    prech->lchild = ch2;
                    prech->rchild = ch1;
                    figure.push(prech);
                }

            sign.push(sign_obj);
        }
        ++i;
    }

    Treenode<T> *ch1 = nullptr;
    Treenode<T> *ch2 = nullptr;
    while(!sign.empty())
    {
        sign.pop(&root);
        figure.pop(&ch1);
        figure.pop(&ch2);
        root->lchild=ch2;
        root->rchild=ch1;
        figure.push(root);
    }
    return root;
}
int main()
{
    string str;
    cout << "Please enter the expression you want to caculate: ";
    cin >> str;
    cout << endl;
    Treenode<char>* root=new Treenode<char>;
    root=build_tree(root, str);
    output(root);
}

template <class T>
void output(const Treenode<T>* root)
{
    if(root==nullptr)return;
    output(root->lchild);
    cout << root->element << " ";
    output(root->rchild);
}

void equal(const char a, const char b, int &k1, int &k2)
{
    switch (a)
    {
    case '-':
        k1 = 1;
        break;
    case '+':
        k1 = 1;
        break;
    case '*':
        k1 = 2;
        break;
    case '/':
        k1 = 2;
        break;
    }
    switch (b)
    {
    case '-':
        k2 = 1;
        break;
    case '+':
        k2 = 1;
        break;
    case '*':
        k2 = 2;
        break;
    case '/':
        k2 = 2;
        break;
    }
}
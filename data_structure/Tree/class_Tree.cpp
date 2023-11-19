/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-26 17:30:30
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-29 16:12:23
 * @FilePath: \C-plus-plus\data_structure\Tree\class_Tree.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

// this is one binary tree.
#include "Stack.cpp"
#include <vector>

using std::vector;

template <class T>
struct TreeNode
{
    /* data */
    T element;
    TreeNode *lchild;
    TreeNode *rchild;

    TreeNode(T &e, TreeNode<T> *l = nullptr, TreeNode<T> *r = nullptr) : element(e), lchild(l), rchild(r){};
};

template <class T>
class tree
{
    TreeNode<T> *root;

    void visit(const TreeNode<T> *) const;
    void preorder(const TreeNode<T> *) const;
    void midorder(const TreeNode<T> *) const;
    void postorder(const TreeNode<T> *) const;
    int gethigh(const TreeNode<T> *, int) const;
    int getsize(const TreeNode<T> *) const;

public:
    tree(TreeNode<T> *r = nullptr) : root(r){};
    tree(T);
    ~tree();
    tree(const tree &);

    void creat(); // according to the rule,you can creat one tree you want.
    void pre_visit() const { preorder(root); }
    void mid_visit() const { midorder(root); }
    void post_visit() const { postorder(root); }
    // void level_visit()const;
    int size() const { return getsize(root); }
    int high() const { return gethigh(root, 0); }
};

template <class T>
tree<T>::~tree()
{
    if (root != nullptr)
    {
        Stack<TreeNode<T>> zhan;
        TreeNode<T> *pt = root;
        TreeNode<T> *ppt = nullptr;
        do
        {
            if (pt->rchild != nullptr)
                zhan.push(pt->rchild);
            if (pt->lchild != nullptr)
            {
                ppt = pt;
                pt = pt->lchild;
                delete ppt;
            }
            if (pt->lchild == nullptr && pt->rchild == nullptr)
            {
                delete pt;
                if (!zhan.empty())
                    zhan.pop(&pt);
            }
        } while (pt != nullptr || !zhan.empty());
    }
}

template <class T>
tree<T>::tree(T ch)
{
    root = new TreeNode<T>(ch);
}

template <class T>
tree<T>::tree(const tree &tr)
{
    if (tr.root == nullptr)
        root = nullptr;
    else
    {
        TreeNode<T> *dup_tr = tr.root;
        root = new TreeNode<T>(tr.root);
        TreeNode<T> *pt = root;
        Stack<T> obj;
        do
        {
            if (dup_tr->rchild != nullptr)
            {
                obj.push(pt);
                obj.push(dup_tr);
            }
            if (dup_tr->lchild != nullptr)
            {
                pt->lchild = new TreeNode(dup_tr->lchild);
                dup_tr = dup_tr->lchild;
                pt = pt->lchild;
            }
            else
            {
                obj.pop(&dup_tr);
                obj.pop(&pt);
                pt->rchild = new TreeNode<T>(dup_tr->rchild);
                pt = pt->rchild;
                dup_tr = dup_tr->rchild;
            }
        } while (!obj.empty());
    }
}

/*
Now we prescribe the rule to creat this tree.
For example,A(B,C):
Then, A is root of the tree,B is left child and C is right child.
*/

template <class T>
void tree<T>::creat()
{
    cout << "Please enter the expression to articulate the tree: " << endl;
    string str;
    cin >> str;
    Stack<TreeNode<T>> zhan;
    int i = 0;
    int k = 0;
    char ch = str[i++];
    root->element = ch;
    TreeNode<T> *pt = root;
    do
    {
        /* code */
        ch = str[i];
        switch (ch)
        {
        case '(':
            zhan.push(pt);
            k = 0;
            break;
        case ')':
            zhan.pop(&pt);
            break;
        case ',':
            k = 1;
            break;
        default:
            switch (k)
            {
            case 0:
                pt->lchild = new TreeNode<T>(ch);
                if (str[i + 1] == '(')
                    pt = pt->lchild;
                break;
            case 1:
                pt->rchild = new TreeNode<T>(ch);
                if (str[i + 1] == '(')
                    pt = pt->rchild;
                break;
            }
            break;
        }
        i++;
    } while (!zhan.empty());
}

template <class T>
void tree<T>::visit(const TreeNode<T> *obj) const
{
    cout << obj->element;
}

template <class T>
void tree<T>::preorder(const TreeNode<T> *obj) const
{
    if (obj != nullptr)
    {
        visit(obj);
        preorder(obj->lchild);
        preorder(obj->rchild);
    }
}

template <class T>
void tree<T>::midorder(const TreeNode<T> *obj) const
{
    if (obj != nullptr)
    {
        midorder(obj->lchild);
        visit(obj);
        midorder(obj->rchild);
    }
}

template <class T>
void tree<T>::postorder(const TreeNode<T> *obj) const
{
    if (obj != nullptr)
    {
        postorder(obj->lchild);
        visit(obj);
        postorder(obj->rchild);
    }
}

template <class T>
int tree<T>::getsize(const TreeNode<T> *pr) const
{
    if (pr != nullptr)
    {
        static int count = 0;
        count++;
        getsize(pr->lchild);
        getsize(pr->rchild);
        return count;
    }
}

template <class T>
int tree<T>::gethigh(const TreeNode<T> *pr, int depth) const
{
    static int max = 0;

    if (pr != nullptr)
    {
        depth++;
        if (max < depth)
            max = depth;
        gethigh(pr->lchild, depth, max);
        gethigh(pr->rchild, depth, max);
        return max;
    }
}
/*
the second way to get the height of the tree

template <class T>
int height(const TreeNode<T> &pr)
{
    if (pr == nullptr)
        return 0;
    int h1 = height(pr->lchild);
    int h2 = height(pr->rchild);
    if (h1 > h2)
        return ++h1;
    else
        return ++h2;
}

*/
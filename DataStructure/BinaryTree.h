//
// Created by fuwuchen on 18-10-14.
//

#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include <iostream>
#include <stdlib.h>
#include <cassert>
#include "Stack.h"
#include "Queue.h"

using namespace std;

template<typename T>
struct BinTreeNode {
    T data;
    BinTreeNode<T> *leftChild, *rightChild;
    BinTreeNode(): leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
        : data(x), leftChild(l), rightChild(r){}
};

template<typename T>
struct stkNode {                                //在遍历时所用栈结点类定义
    BinTreeNode<T> *ptr;                        //指向树节点的指针
    enum tag {L, R};                            //该节点退栈标记
    stkNode(BinTreeNode<T> *N = NULL): ptr(N), tag(L){}
};

template<typename T>
class BinaryTree {                              //对象:结点的有限集合,二叉树是有序数
public:
    BinaryTree(): root(NULL){}
    BinaryTree(T value): RefValue(value), root(NULL) {}
    BinaryTree(BinaryTree<T>& s) {              //复制构造函数
        if ( this != &s ) {
            root = Copy(s.root);
        }
    }
    ~BinaryTree() {
        destroy(root);
    }
    bool IsEmpty() {
        return (root == NULL);
    }
    BinTreeNode<T> *Parent(BinTreeNode<T> *current) {
        return ( root == NULL || root == current ) ? NULL : Parent(root, current);
    }
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current) {
        return ( current != NULL ) ? current->leftChild : NULL;
    }
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current) {
        return ( current != NULL ) ? current->rightChild : NULL;
    }
    int Height() {
        return Height(root);
    }
    int Size() {
        return Size(root);
    }
    void PreOrder(void(* visit)(BinTreeNode<T> *p)) {
        PreOrder(root, visit);
    }
    void InOrder(void(* visit)(BinTreeNode<T> *p)) {
        InOrder(root, visit);
    }
    void PostOrder(void(* visit)(BinTreeNode<T> *p)) {
        PostOrder(root, visit);
    }
    void LevelOrder(void(* visit)(BinTreeNode<T> *p));
    bool Insert(T item) {
        return Insert(root, item);
    }
    bool *Find(const T& item)const;
//    BinTreeNode<T> *getRoot()const;
//    bool getData(const T& item)const;
//    bool Remove(T item);
protected:
    BinTreeNode<T> *root;                                         //根指针
    T RefValue;                                                   //二叉树输入停止标志
    void CreateBinTree(istream& in, BinTreeNode<T> *&subTree);    //从文件读入建树
    BinTreeNode<T> *CreateBinaryTree(T *VLR, T *LVR, int n);      //利用前序序列和中序序列构造二叉树
    bool Insert(BinTreeNode<T> *&subTree, const T& x);            //插入
    void destroy(BinTreeNode<T> *&subTree);                       //删除
    bool Find(BinTreeNode<T> *&subTree, const T& x)const;         //查找
    BinTreeNode<T> *Copy(BinTreeNode<T> *orignode);               //复制
    int Height(BinTreeNode<T> *subTree);                          //返回树高度
    int Size(BinTreeNode<T> *subTree);                            //返回结点树
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree,
            BinTreeNode<T> *current);                             //返回父结点
    BinTreeNode<T> *Find(BinTreeNode<T> *subTree, const T& x);    //搜寻x
    void PrintBTree(BinTreeNode<T> *BT);
    void Traverse(BinTreeNode<T> *subTree, ostream& out);         //前序遍历输出
    void PreOrder(BinTreeNode<T>& subTree,
            void(* visit)(BinTreeNode<T> *p));                    //前序遍历
    void InOrder(BinTreeNode<T>& subTree,
                  void(* visit)(BinTreeNode<T> *p));              //中序遍历
    void PostOrder(BinTreeNode<T>& subTree,
                  void(* visit)(BinTreeNode<T> *p));              //后序遍历
    void PreOrder1(void (*visit) (BinTreeNode<T> *t));            //前序遍历非递归算法
    void PreOrder2(void (*visit) (BinTreeNode<T> *t));            //前序遍历非递归算法
    void InOrder1(void (*visit) (BinTreeNode<T> *t));             //中序遍历非递归算法
    void PostOrder1(void (*visit) (BinTreeNode<T> *t));           //后序遍历非递归算法
    friend istream&operator>>(istream& in, BinaryTree<T>& Tree);  //重载操作:输入
    friend ostream&operator<<(ostream& out, BinaryTree<T>& Tree); //重载操作:输出
    friend int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t);
    friend bool equal(BinTreeNode<T> *a, BinTreeNode<T> *b);
};

template<typename T>
void BinaryTree<T>::destroy(BinTreeNode<T> *&subTree) {
    //私有函数:若指针subTree不为空,则删除根为subTree的子树
    if ( subTree != NULL ) {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
    }
}

template<typename T>
BinTreeNode<T> *BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current) {
    //私有函数:从结点subTree开始,搜索结点current的父结点.若找到结点current
    //的父结点,则函数返回父结点地址,否则函数返回NULL
    if ( subTree == NULL )
        return NULL;
    if ( subTree->leftChild == current || subTree->rightChild == current )
        return subTree;
    BinTreeNode <T> *p;
    if ( ( p = Parent(subTree->leftChild, current) != NULL ) )
        return p;
    else
        return Parent(subTree->rightChild, current);
}

template<typename T>
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream &out) {
    //私有函数:搜索并输出根为subTree的二叉树
    if ( subTree != NULL ) {
        out << subTree->data << ' ';
        Traverse(subTree->leftChild, out);
        Traverse(subTree->rightChild, out);
    }
}

template<typename T>
istream &operator>>(istream &in, BinaryTree<T> &Tree) {
    //重载操作:输入并建立一棵二叉树Tree.in是输入流对象
    CreateBinTree(in, Tree.root);
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, BinaryTree<T> &Tree) {
    //重载操作:输出一棵二叉树Tree,out是输出流对象
    out << "二叉树的前序遍历\n";
    Tree.Traverse(Tree.root, out);
    out << endl;
    return out;
}

template<typename T>
void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&subTree) {
    //从输入流in输入二叉树的广义表表示建立对应的二叉链表
    T item;
    if ( ! in.eof() ) {                             //未读完,读入并建树
        in >> item;                                 //读入根节点的值
        if ( item != RefValue ) {
            subTree = new BinTreeNode<T>(item);     //建立根节点
            if ( subTree == NULL ) {
                cerr << "存储分配错误!" << endl;
                exit(1);
            }
            CreateBinTree(in, subTree->leftChild);  //递归建立左子树
            CreateBinTree(in, subTree->rightChild); //递归建立右子树
        }
        else
            subTree = NULL;                         //封闭指向空子树的指针
    }
}

template<typename T>
void BinaryTree<T>::InOrder(BinTreeNode<T> &subTree, void (*visit)(BinTreeNode<T> *p)) {
    //递归函数:此算法按照中序次序遍历以subTree为根的子树.
    if ( subTree != NULL ) {
        InOrder(subTree->leftChild, visit);
        visit(subTree);
        InOrder(subTree.rightChild, visit);
    }
}

template<typename T>
void BinaryTree<T>::PreOrder(BinTreeNode<T> &subTree, void (*visit)(BinTreeNode<T> *p)) {
    //递归函数:此算法按照前序次序遍历以subTree为根的二叉树
    if ( subTree != NULL ) {
        visit(subTree);
        PreOrder(subTree->leftChild, visit);
        PreOrder(subTree->rightChild, visit);
    }
}

template<typename T>
void BinaryTree<T>::PostOrder(BinTreeNode<T> &subTree, void (*visit)(BinTreeNode<T> *p)) {
    //递归函数:此算法按照后序遍历以subTree为根的二叉树
    if ( subTree != NULL ) {
        PostOrder(subTree->rightChild);
        PostOrder(subTree->leftChild);
        visit(subTree);
    }
}

template<typename T>
int BinaryTree<T>::Size(BinTreeNode<T> *subTree) {
    //私有函数:计算以*subTree为根的二叉树的结点个数
    if ( subTree == NULL )
        return 0;
    else
        return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
}

template<typename T>
int BinaryTree<T>::Height(BinTreeNode<T> *subTree) {
    //私有函数:计算以*subTree为根的二叉树的高度或深度
    if ( subTree == NULL )
        return 0;
    else {
        int i = Height(subTree->leftChild);
        int j = Height(subTree->rightChild);
        return ( i < j ) ?  j + 1  :  i + 1 ;
    }
}

template<typename T>
BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *orignode) {
    //私有函数:这个函数返回一个指针,它给出一个以orignode为根的二叉树的副本
    if ( orignode == NULL )
        return NULL;
    BinTreeNode<T> *temp = new BinTreeNode<T>;
    temp->data = orignode->data;
    temp->leftChild = Copy(orignode->leftChild);
    temp->rightChild = Copy(orignode->rightChild);
    return temp;
}

template<typename T>
int operator==(const BinaryTree<T> &s, const BinaryTree<T> &t) {
    //判断两棵二叉树的等价性,假定它是BinaryTree类的友元函数
    return equal(s.root, t.root);
}

template<typename T>
bool equal(BinTreeNode<T> *a, BinTreeNode<T> *b) {
    //如果a和b的子树不等同,则函数返回false,否则函数返回true.假定它是
    //BinTreeNode类的友元函数
    if ( a == NULL && b == NULL )
        return true;
    return a != NULL && b != NULL && a->data == b->data
           && equal(a->leftChild, b->leftChild)
           && equal(a->rightChild, b->rightChild);
}

template<typename T>
void BinaryTree<T>::PrintBTree(BinTreeNode<T> *BT) {
    if( BT != NULL ) {                                              //树为空时结束递归
        cout << BT->data;                                           //输出根节点的值
        if ( BT->leftChild != NULL || BT->rightChild != NULL ) {
            cout << '(';                                            //输出左括号
            PrintBTree(BT->leftChild);                              //输出左子树
            cout << ',';                                            //输出逗号分隔符
            if ( BT->rightChild != NULL )                           //若右子树不为空
                PrintBTree(BT->rightChild);                         //输出右子树
            cout << ')';                                            //输出右括号
        }
    }
}

template<typename T>
void BinaryTree<T>::PreOrder1(void (*visit)(BinTreeNode<T> *p)) {
    Stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;                                       //初始化
    S.Push(NULL);
    while ( p != NULL ) {
        visit(p);                                                   //访问结点
        if ( p->rightChild != NULL )
            S.Push(p->leftChild);                                   //预留右子树指针在栈中
        if ( p->leftChild != NULL )
            p = p->leftChild;                                       //进左子树
        else
            S.Pop(p);                                               //左子树为空
    }
}

template<typename T>
void BinaryTree<T>::PreOrder2(void (*visit)(BinTreeNode<T> *p)) {
    Stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    S.Push(root);
    while ( S.IsEmpty() ) {
        S.Pop(p);
        visit(p);
        if ( p->rightChild != NULL )
            S.Push(p->rightChild);
        if ( p->leftChild != NULL )
            S.Push(p->leftChild);
    }
}

template<typename T>
void BinaryTree<T>::LevelOrder(void (*visit)(BinTreeNode<T> *p)) {
    Queue<BinTreeNode<T> *> Q;
    BinTreeNode<T> *p = root;
    Q.EnQueue(p);
    while ( ! Q.IsEmpty() ) {
        Q.DeQueue(p);
        visit(p);
        if ( p->leftChild != NULL )
            Q.EnQueue(p->leftChild);
        if ( p->rightChild != NULL )
            Q.EnQueue(p->rightChild);
    }
}

template<typename T>
void BinaryTree<T>::InOrder1(void (*visit)(BinTreeNode<T> *)) {
    Stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;                   //p是遍历指针,从根节点开始
    do {
        while ( p != NULL ) {                   //遍历指针未到最左下的结点,不空
            S.Push(p);                          //该子树沿途结点进栈
            p = p->rightChild;                  //遍历指针进到有子女结点
        }
    } while ( p != NULL || !S.IsEmpty() );
}

template<typename T>
void BinaryTree<T>::PostOrder1(void (*visit)(BinTreeNode<T> *)) {
    Stack<stkNode<T>> S; stkNode<T> w;
    BinTreeNode<T> *p = root;                   //p是遍历指针
    do {
        while ( p != NULL ) {                   //左子树经过结点加L进栈
            w.ptr = p;
            w.tag = L;
            S.Push(w);
            p = p->leftChild;                   //向最左下结点走去
        }
        int continue1 = 1;                      //继续循环标记,用于R
        while ( continue1 && !S.IsEmpty() ) {
            S.Pop(w);                           //栈不空,退栈
            p = w.ptr;
            switch ( w.tag ) {                  //判断栈顶的tag标记
                case L: w.tag = R;
                        S.Push(w);              //从左子树退回,修改栈顶tag
                        continue1 = 0;
                        p = p->rightChild;      //向右子树遍历下去
                        break;
                case R: visit(p);
                        break;
            }
        }
    } while ( !S.IsEmpty() );                   //还有结点未遍历,继续循环
    cout << endl;
}

template<typename T>
BinTreeNode<T> *BinaryTree<T>::CreateBinaryTree(T *VLR, T *LVR, int n) {
    //VLR是二叉树前序序列,LVR是二叉树的中序序列,构造出的二叉树指针由函数返回.
    if ( n == 0 )
        return NULL;
    int k = 0;
    while ( VLR[0] != LVR[k] )                  //在中序序列中寻找根
        k ++;
    BinTreeNode<T> *t = new BinTreeNode<T>(VLR[0]);
                                                //创建根节点
    t->leftChild = CreateBinaryTree(VLR+1, LVR, k);
       //从前序VLR+1开始对终须的0~k-1左子序列的k个元素递归建立左子树
    t->rightChild = CreateBinaryTree(VLR+k+1, LVR+k+1, n-k-1);
       //从前序VLR+k+1开始对终须的k+1~n-1右子序列的n-k-1个元素递归建立右子树
    return t;
}


#endif //DATASTRUCTURE_BINARYTREE_H

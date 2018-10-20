//
// Created by fuwuchen on 18-10-16.
//

#ifndef DATASTRUCTURE_BST_H
#define DATASTRUCTURE_BST_H

#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename E, typename K>
struct BSTNode {
    E data;
    BSTNode<E,K> *left, *right;
    BSTNode(): left(NULL), right(NULL){}
    BSTNode(const E d, BSTNode<E,K> *L = NULL, BSTNode<E,K> *R = NULL)
        : data(d), left(L), right(R) {}
    ~BSTNode(){}
    void setData(E d) {
        data = d;
    }
    E getData() {
        return data;
    }
    bool operator < (const E& x) {
        return ( data.key < x.key );
    }
    bool operator > (const E& x) {
        return ( data.key > x.key );
    }
    bool operator == (const E& x) {
        return ( data.key == x.key );
    }
};

template<typename E, typename K>
class BST {
public:
    BST(): root(NULL){}
    BST(K value);
    ~BST() {};
    bool Search(const K x)const {
        return Search(x, root) != NULL;
    }
    BST<E,K>&operator = (const BST<E,K>& R);        //赋值
    void makeEmpty() {
        makeEmpty(root);
        root = NULL;
    }
    void PrintTree()const {
        PrintTree(root);
    }
    E Min() {
        return Min(root)->data;
    }
    E Max() {
        return Max(root)->data;
    }
    bool Insert(const E& el) {
        return Insert(el, root);
    }
    bool Remove(const K x) {
        return Remove(x, root);
    }

private:
    BSTNode<E,K> * root;
    K RefValue;                                             //输入停止标志,用于输入
    BSTNode<E,K> *Search(const K x, BSTNode<E,K> *ptr);     //递归:搜索
    void makeEmpty(BSTNode<E,K> *&ptr)const;                //递归:置空
    void PrintTree(BSTNode<E,K> *ptr)const;                 //递归:打印
    BSTNode<E,K> *Copy(const BSTNode<E,K> *ptr)const;       //递归:赋值
    BSTNode<E,K> *Min(BSTNode<E,K> *ptr)const;              //递归:求最小
    BSTNode<E,K> *Max(BSTNode<E,K> *ptr)const;              //递归:求最大
    bool Insert(const E& el, BSTNode<E,K> *& ptr);          //递归:插入
    bool Remove(const K x, BSTNode<E,K> *& ptr);            //递归:删除
};

template<typename E, typename K>
BSTNode<E, K> *BST<E, K>::Search(const K x, BSTNode<E, K> *ptr) {
    //私有递归函数:在以ptr为根的二叉搜索树中搜索含x的结点.若找到,则函数返回该结点的
    //地址,否则函数返回NULL值
    if ( ptr == NULL )
        return NULL;
    else if ( x < ptr->data )
        return Search(x, ptr->left);
    else if ( x > ptr->data )
        return Search(x, ptr->right);
    else
        return ptr;
}

template<typename E, typename K>
bool BST<E, K>::Insert(const E &el, BSTNode<E, K> *&ptr) {
    //私有函数:在以ptr为根的二叉搜索树中插入所含值为el的结点.若在树中已经含有el的
    //结点,则不插入
    if ( ptr == NULL ) {
        ptr = new BSTNode<E,K>(el);
        if ( ptr == NULL ) {
            cerr << "Out of Space" << endl;
            exit(1);
        }
        return true;
    }
    else if ( el < ptr->data )
        Insert(el, ptr->left);
    else if ( el > ptr->data )
        Insert(el, ptr->right);
    else
        return false;                           //x已在树中,不再插入
}

template<typename E, typename K>
BST<E, K>::BST(K value) {
    //输入一个元素序列,建立一棵二叉搜索树
    E x; root = NULL; RefValue = value;         //置空树
    cin >> x;
    while ( x.key != RefValue ) {
        Insert(x, root);
        cin >> x;
    }
}

template<typename E, typename K>
bool BST<E, K>::Remove(const K x, BSTNode<E, K> *&ptr) {
    //私有函数:在以ptr为根的二叉搜索树中删除含x的结点.若删除成功则新根通过ptr返回
    BSTNode<E,K> *temp;
    if ( ptr != NULL ) {
        if ( x < ptr->data )
            Remove(x, ptr->left);
        else if ( x > ptr->data )
            Remove(x, ptr->right);
        else if ( ptr->left != NULL && ptr->right != NULL ) {   //ptr指示关键码为x的结点,它有两个子女
            temp = ptr->right;                                  //到右子树搜寻中序下第一个结点
            while ( temp->left != NULL )
                temp = temp->left;                              //中序第一个结点
            ptr->data = temp->data;                             //用该结点数据代替根结点数据
            Remove(ptr->data, ptr->right);
        }
        else {                                                  //ptr指示关键码为x的结点,它只有一个或零个子女
            temp = ptr;
            if ( ptr->left == NULL )
                ptr = ptr->right;                               //左子树空,用右子女填补
            else
                ptr = ptr->left;                                //右子树空,用左子树填补
            delete temp;
            return true;
        }
    }
    return false;
}

#endif //DATASTRUCTURE_BST_H

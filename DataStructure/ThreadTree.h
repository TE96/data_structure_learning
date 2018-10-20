//
// Created by fuwuchen on 18-10-14.
//

#ifndef DATASTRUCTURE_THREADTREE_H
#define DATASTRUCTURE_THREADTREE_H

#include <iostream>

using namespace std;

template<typename T>
struct ThreadNode {
    int ltag, rtag;
    ThreadNode<T> *leftChild, *rightChild;
    T data;
    ThreadNode(const T item): data(item), leftChild(NULL),
        rightChild(NULL), ltag(0), rtag(0) {}
};

template<typename T>
class ThreadTree {
protected:
    ThreadNode<T> *root;
    void CreateInThread(ThreadNode<T> *current, ThreadNode<T> *&pre);
    //中序遍历建立线索二叉树
    ThreadNode<T> *parent(ThreadNode<T> *t);        //寻找结点t的父结点
public:
    ThreadTree(): root(NULL) {}
    void CreateInThread();
    ThreadNode<T> *First(ThreadNode<T> *current);   //寻找中序下第一个结点
    ThreadNode<T> *Last(ThreadNode<T> *current);    //寻找中序下最后一个结点
    ThreadNode<T> *Next(ThreadNode<T> *current);    //寻找中序下的后继结点
    ThreadNode<T> *Prior(ThreadNode<T> *current);   //寻找结点在中序下的前驱结点
    void InOrder(void(* visit)(ThreadNode<T> *p));  //中序遍历
    void PreOrder(void(* visit)(ThreadNode<T> *p)); //前序遍历
    void PostOrder(void(* visit)(ThreadNode<T> *p));//后序遍历
    bool Find(const T &value);
    ThreadNode<T>* getCurrent() {
        return current;
    }
    void destroy(ThreadNode<T> *& subTree);

private:
    ThreadNode<T> *current;
    bool Find(ThreadNode<T> *p, const T &value);
    bool setRoot(const T &rt) {
        root = new ThreadNode<T>(rt);
        if ( root )
            return true;
        else
            return false;
    }
    static ThreadNode<T> &leftChild (ThreadNode<T> *t) {
        return t->leftChild;
    }
    static ThreadNode<T> &rightChild (ThreadNode<T> *t) {
        return t->rightChild;
    }
    bool MakeLink(const T ex, const T ap, char linkmark);
    void Print(ThreadNode<T>* p, int i);
};

template<typename T>
ThreadNode<T> *ThreadTree<T>::First(ThreadNode<T> *current) {
    //函数返回以*current为根的中序线索二叉树中中序序列下的第一个结点.
    ThreadNode<T> *p = current;
    while ( p->ltag == 0 )
        p = p->leftChild;                   //最左下结点(不一定是叶结点)
    return p;
}

template<typename T>
ThreadNode<T> *ThreadTree<T>::Next(ThreadNode<T> *current) {
    //函数返回在中序线索二叉树中结点current在中序下的后继结点.
    ThreadNode<T> *p = current->rightChild;
    if ( current->rtag == 0 )
        return First(p);                    //在右子树中找中序下第一个结点
    else
        return p;                           //rtag==1,直接返回后继线索
}

template<typename T>
ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current) {
    //函数返回以*current为根的中序线索二叉树中中序序列下的最后一个结点
    ThreadNode<T> *p = current;
    while ( p->rtag == 0 )
        p = p->rightChild;                  //最右下结点(不一定是叶节点)
    return p;
}

template<typename T>
ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current) {
    //函数返回在中序线索二叉树中结点current在中序下的前驱结点.
    ThreadNode<T> *p = current->rightChild;
    if ( current->ltag == 0 )
        return Last(p);
    else
    return p;
}

template<typename T>
void ThreadTree<T>::InOrder(void (*visit)(ThreadNode<T> *p)) {
    ThreadNode<T> *p;
    for ( p = First(root) ; p != NULL ; p = Next(p) )
        visit(p);
}

template<typename T>
void ThreadTree<T>::PreOrder(void (*visit)(ThreadNode<T> *p)) {
    ThreadNode<T> *p = root;
    while ( p != NULL ) {
        visit(p);                               //访问根结点
        if ( p->ltag == 0 )
            p = p->leftChild;                   //有左子女,即为后继
        else if ( p->rtag == 0 )
            p = p->rightChild;                  //否则有右子女,即后继
        else{
            while ( p != NULL && p->rtag == 1 ) //沿后继线索检测
                p = p->rightChild;              //直到有右子女的结点
            if ( p != NULL )
                p = p->rightChild;              //右子女即为后继
        }
    }
}

template<typename T>
void ThreadTree<T>::PostOrder(void (*visit)(ThreadNode<T> *p)) {
    ThreadNode<T> *t = root;
    while ( t->ltag == 0 || t->rtag == 0 )      //寻找后序第一个结点
        if ( t->rtag == 0 )
            t = t->rightChild;
        else if ( t-> rtag == 0 )
            t = t->rightChild;
    visit(t);                                   //访问第一个结点
    ThreadNode<T> *p;
    while ( (p = parent(t)) != NULL ) {
        if ( p->rightChild == t || p->rtag == 1 )//*t是*p的后序后继
            t = p;
        else {
            t = p->rightChild;                  //否则t移到*p的右子树
            while ( t->ltag == 0 || t->rtag == 0 )
                if ( t->ltag == 0 )
                    t = t->leftChild;
                else if ( t->rtag == 0 )
                    t = t->rightChild;
        }
        visit(t);
    }
}

template<typename T>
void ThreadTree<T>::CreateInThread() {
    ThreadNode<T> *pre = NULL;                  //前驱结点指针
    if ( root != NULL ) {                       //非空二叉树,线索化
        CreateInThread(root, pre);              //中序遍历线索化二叉树
        pre->rightChild = NULL;
        pre->rtag = 1;                          //后处理中序最后一个结点
    }
}

template<typename T>
void ThreadTree<T>::CreateInThread(ThreadNode<T> *current, ThreadNode<T> *&pre) {
    //通过中序遍历,对二叉树进行线索化
    if ( current == NULL )
        return;
    CreateInThread(current->leftChild, pre);       //递归,左子树线索化
    if ( current->leftChild == NULL ) {            //建立当前结点的前驱线索
        current->leftChild = pre;
        current->ltag = 1;
    }
    if ( pre != NULL && pre->rightChild == NULL ) {//建立前驱结点的后继线索
        pre->rightChild = current;
        pre->rtag = 1;
    }
    pre = current;                                 //前驱跟上,当前指针向前遍历
    CreateInThread(current->rightChild, pre);      //递归,右子树线索化
}

template<typename T>
ThreadNode<T> *ThreadTree<T>::parent(ThreadNode<T> *t) {
    ThreadNode<T> *p;
    if ( t == root )
        return NULL;                                    //根结点无父结点
    for ( p = t ; p->ltag == 0 ; p = p->leftChild );    //求*t为根子树的第一个结点
    if ( p->leftChild != NULL )
        for ( p = p->leftChild ; p != NULL && p->leftChild != t && p->rightChild != t ;
              p = p->rightChild );
    if ( p == NULL || p->leftChild == NULL ) {
        for ( p = t ; p->rtag == 0 ; p = p->rightChild );
        for ( p = p->rightChild ; p != NULL && p->leftChild != t && p->rightChild != t ;
              p = p->leftChild );
    }
    return p;
}

//TODO:中序线索二叉树的插入与删除

//TODO:前序与后序的线索化二叉树

#endif //DATASTRUCTURE_THREADTREE_H

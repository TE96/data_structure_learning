//
// Created by fuwuchen on 18-10-11.
//

#ifndef DATASTRUCTURE_DBLLIST_H
#define DATASTRUCTURE_DBLLIST_H

#include <iostream>
#include "LinearList.h"

using namespace std;

template <typename T>
struct DblNode {                                //链表结点类定义
    T data;
    DblNode<T> *lLink, *rLink;                  //链表前驱(左链)、后继(右链)指针
    DblNode(DblNode<T> *left = NULL, DblNode *right = NULL)
    : lLink(left), rLink(right) {}                  //构造函数
    DblNode(T value, DblNode<T> *left = NULL, DblNode *right = NULL)
    :data(value), lLink(left), rLink(right) {}      //构造函数
};

template <typename T>
class DblList: public LinearList<T> {           //链表类定义
public:
    DblList(T uniqueVal);                       //构造函数:建立附加头结点
    ~DblList();                                 //析构函数:释放所用存储
    int Length()const;                          //计算双链表的长度
    bool IsEmpty() { return first->rlink == first; }
    DblNode<T> *getHead()const { return first; }
    void setHead(DblNode<T> *ptr) { first = ptr; }
    DblNode<T> *Search(const T& x);             //在链表中沿后继方向寻找等于给定值x的结点
    DblNode<T> *Locate(int i, int d);           //在链表中定位序号为i(i>=0)的结点,d=0按前驱方向,d≠0按后继方向
    bool Insert(int i, const T& x, int d);      //在第i个结点后插入一个包含有值x的新结点,d=0按前驱方向,d≠0按后继方向
    bool Remove(int i, T& x, int d);            //删除第i个结点,x返回其值,d=0按前驱方向,d≠0按后继方向

private:
    DblNode<T> *first;
};

template<typename T>
bool DblList<T>::Insert(int i, const T &x, int d) {
    //建立一个包含有值x的新结点,并将其按d指定的方向插入到第i个结点之后.
    DblNode<T> *current = Locate(i, d);         //查找第i个结点
    if ( current == NULL )
        return false;                           //i不合理,插入失败
    DblNode<T> *newNode = new DblNode<T>(x);
    if ( newNode == NULL ) {
        cerr << "存储分配失败" << endl;
        exit(1);
    }
    if ( d == 0 ) {                             //前驱方向插入
        newNode->lLink = current->lLink;
        current->lLink = newNode;
        newNode->lLink->rLink = newNode;
        newNode->rLink = current;
    }
    else {                                      //后继方向插入
        newNode->rLink = current->rLink;
        current->rLink = newNode;
        newNode->rLink->lLink = newNode;
        newNode->lLink = current;
    }
    return true;
}

template<typename T>
bool DblList<T>::Remove(int i, T &x, int d) {
    //在带附加头结点的双向循环链表中按照d所指方向删除第i个结点
    DblNode<T> *current = Locate(i, d);         //查找第i个结点
    if ( current == NULL )
        return false;                           //i不合理,删除失败
    current->rLink->lLink = current->lLink;     //从lLink链中摘下
    current->lLink->rLink = current->rLink;     //从rLink链中摘下
    x = current->data;
    delete current;                             //删除
}

#endif //DATASTRUCTURE_DBLLIST_H

//
// Created by fuwuchen on 18-10-11.
//

#ifndef DATASTRUCTURE_CIRCLIST_H
#define DATASTRUCTURE_CIRCLIST_H

#include <iostream>
#include "LinearList.h"

using namespace std;

template <typename T>
struct CircLinkNode {                           //链表结点类定义
    T data;
    CircLinkNode<T> *link;

    CircLinkNode( CircLinkNode<T> *next = NULL ):link(next){}
    CircLinkNode( T d, CircLinkNode<T> *next = NULL ):data(d), link(next){}
};

template <typename T>
class CircList: public LinearList<T> {          //链表类定义
public:
    CircList(const T& x);
    CircList(CircList<T>& L);
    ~CircList();
    int Length()const;                          //计算循环链表长度
    bool isEmpty() { return first->link == first; }
    CircLinkNode<T> *getHead()const;
    void setHead(CircLinkNode<T> *p);
    CircLinkNode<T> *Search(T x);
    CircLinkNode<T> *Locate(int i);
    T *getData(int i);
    void setData(int i, T& x);
    bool Insert(int i, T& x);
    bool Remove(int i, T& x);

private:
    CircLinkNode<T> *first, *last;
};

template<typename T>
CircList<T>::CircList(const T &x) {

}

template<typename T>
CircList<T>::CircList(CircList<T> &L) {

}

template<typename T>
CircList<T>::~CircList() {

}

template<typename T>
int CircList<T>::Length() const {
    return 0;
}

template<typename T>
CircLinkNode<T> *CircList<T>::getHead() const {
    return nullptr;
}

template<typename T>
void CircList<T>::setHead(CircLinkNode<T> *p) {

}

template<typename T>
CircLinkNode<T> *CircList<T>::Search(T x) {
    return nullptr;
}

template<typename T>
CircLinkNode<T> *CircList<T>::Locate(int i) {
    return nullptr;
}

template<typename T>
T *CircList<T>::getData(int i) {
    return nullptr;
}

template<typename T>
void CircList<T>::setData(int i, T &x) {

}

template<typename T>
bool CircList<T>::Insert(int i, T &x) {
    return false;
}

template<typename T>
bool CircList<T>::Remove(int i, T &x) {
    return false;
}

#endif //DATASTRUCTURE_CIRCLIST_H

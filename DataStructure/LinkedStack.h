//
// Created by fuwuchen on 18-10-12.
//

#ifndef DATASTRUCTURE_LINKEDSTACK_H
#define DATASTRUCTURE_LINKEDSTACK_H

#include <iostream>
#include "LinkedList.h"
#include "Stack.h"


template <typename T>
class LinkedStack: public Stack<T> {
public:
    LinkedStack(): top(NULL) {}
    ~LinkedStack() { makeEmpty(); };
    void Push(const T& x);
    bool Pop(T& x);
    bool getTop(T& x)const;
    bool IsEmpty()const { return ( top == NULL ); }
    int getSize()const;
    void makeEmpty();
    friend ostream&operator<<(ostream& os, LinkedStack<T>& s);

private:
    LinkNode<T> *top;
};

template<typename T>
void LinkedStack<T>::makeEmpty() {
    //逐次删去链式栈中的元素直至栈顶指针为空
    LinkNode<T> *p;
    while ( top != NULL ) {
        p = top;
        top = top->link;
        delete p;
    }
}

template<typename T>
void LinkedStack<T>::Push(const T &x) {
    //将元素值x插入到链式栈的栈顶,即链头
    top = new LinkNode<T>(x, top);                  //创建新的含x结点
    assert(top != NULL);                            //创建新结点失败退出
}

template<typename T>
bool LinkedStack<T>::Pop(T &x) {
    //删除栈顶结点,返回被删栈顶元素的值
    if ( IsEmpty() )
        return false;                               //若栈空则不退栈,返回
    LinkNode<T> *p = top;                           //否则暂存栈顶元素
    top = top->link;                                //栈顶指针推到新的栈顶位置
    x = p->data;
    delete p;
    return true;
}

template<typename T>
bool LinkedStack<T>::getTop(T &x) const {
    //返回栈顶元素的值
    if ( IsEmpty() )
        return false;                               //若栈空则返回false
    x = top->data;
    return true;
}

template<typename T>
int LinkedStack<T>::getSize() const {
    LinkNode<T> *p = top;
    int k = 0;
    while ( top != NULL ) {
        top = top->link;
        k ++;
    }
    return k;
}

template<typename T>
ostream &operator<<(ostream &os, LinkedStack<T> &s) {
    //输出栈中元素的重载操作 <<
    os << "栈中元素个数 = " << s.getSize() << endl;
    LinkNode<T> *p = S.top;
    int i = 0;
    while ( p != NULL )
        os << ++i << ":" << p->data << endl;
    return os;
}


#endif //DATASTRUCTURE_LINKEDSTACK_H

//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_LINKEDQUEUE_H
#define DATASTRUCTURE_LINKEDQUEUE_H

#include <iostream>
#include "LinkedList.h"
#include "Queue.h"

using namespace std;

template<typename T>
class LinkedQueue: public Queue<T> {
public:
    LinkedQueue(): rear(NULL), front(NULL) {}
    ~LinkedQueue() { makeEmpty(); }
    bool EnQueue(const T& x);
    bool DeQueue(T& x);
    bool getFront(T& x)const;
    void makeEmpty();
    bool IsEmpty()const { return (front == NULL); }
    int getSize()const;
    friend ostream&operator<<(ostream& os, LinkedQueue<T>& Q);

protected:
    LinkNode<T> *front, *rear;
};

template<typename T>
void LinkedQueue<T>::makeEmpty() {
    //置空队列,释放链表中所有结点
    LinkNode<T> *p;
    while ( front != NULL ) {
        p = front;
        front = front->link;
        delete p;
    }
}

template<typename T>
bool LinkedQueue<T>::EnQueue(const T &x) {
    //将新元素x插入到队列的队尾(链式队列的链尾)
    if ( front == NULL ) {
        front = rear = new LinkNode<T>(x);
            //空队列时,新结点成为队列的第一个结点,既是队头又是队尾
        if ( front == NULL )
            return false;               //分配结点失败
    }
    else {
        rear->link = new LinkNode<T>(x);
            //非空队列时,在链尾追加新的结点并更新队尾指针
        if ( rear->link == NULL )
            return false;               //分配结点失败
        rear = rear->link;
    }
    return true;
}

template<typename T>
bool LinkedQueue<T>::DeQueue(T &x) {
    //如果队列不为空,将队头结点从链式队列中删去,函数返回true,否则返回false
    if ( IsEmpty() )
        return false;
    LinkNode<T> *p = front;
    x = front->data;
    front = front->link;
    delete p;
    return true;
}

template<typename T>
bool LinkedQueue<T>::getFront(T &x) const {
    //若队列不空,则函数返回队头元素的值及true.若队列空,则函数返回false.
    if ( IsEmpty() )
        return false;
    x = front->data;
    return true;
}

template<typename T>
int LinkedQueue<T>::getSize() const {
    //求队列元素个数
    LinkNode<T> *p = front;
    int k = 0;
    while ( p != NULL ) {
        p = p->link;
        k ++;
    }
    return k;
}

template<typename T>
ostream &operator<<(ostream &os, LinkedQueue<T> &Q) {
    //输出队列中元素的重载操作<<
    os << "队列中的元素个数有" << Q.getSize() << endl;
    LinkNode<T> *p = Q.front;
    int i = 0;
    while ( p != NULL ) {
        os << ++i << ":" << p->data << endl;
        p = p->link;
    }
    return os;
}

#endif //DATASTRUCTURE_LINKEDQUEUE_H

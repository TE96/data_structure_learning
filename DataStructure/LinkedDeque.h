//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_LINKEDDEQUE_H
#define DATASTRUCTURE_LINKEDDEQUE_H

#include "Deque.h"
#include "LinkedQueue.h"
#include "LinkedList.h"

template<typename T>
class LinkedDeque: public Deque<T>, public LinkedQueue<T> {
public:
    LinkedDeque(){};
    ~LinkedDeque(){};
    bool getHead(T &x)const;
    bool getTail(T &x)const;
    bool EnQueue(const T &x){
        return EnQueueTail(x);
    }
    bool EnQueueHead(const T &x);
    bool EnQueueTail(const T &x);
    bool DeQueue(T &x){
        return DeQueueHead(x);
    }
    bool DeQueueHead(T &x);
    bool DeQueueTail(T &x);
};

template<typename T>
bool LinkedDeque<T>::getHead(T &x) const {
    T temp;
    bool tag = LinkedQueue<T>(temp);
    x = temp;
    return tag;
}

template<typename T>
bool LinkedDeque<T>::getTail(T &x) const {
    if ( front == NULL )
        return false;
    x = rear->data;
    return true;
}

template<typename T>
bool LinkedDeque<T>::EnQueueHead(const T &x) {
    LinkNode<T> *p = new LinkNode<T>(x);
    if ( p == NULL )
        return false;
    p->link = front;
    front = p;
    if ( !front->link )
        rear = front;
    return true;
}

template<typename T>
bool LinkedDeque<T>::EnQueueTail(const T &x) {
    return LinkedQueue<T>::EnQueue(x);
}

template<typename T>
bool LinkedDeque<T>::DeQueueHead(T &x) {
    T temp;
    bool tag = LinkedQueue<T>(temp);
    x = temp;
    return tag;
}

template<typename T>
bool LinkedDeque<T>::DeQueueTail(T &x) {
    if ( front == NULL )
        return false;
    LinkNode<T> *p = front;
    while ( p->link != rear )
        p = p->link;
    x = rear->data;
    delete rear;
    p->link = NULL;
    rear = p;
    return true;
}

#endif //DATASTRUCTURE_LINKEDDEQUE_H

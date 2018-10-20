//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_DEQUE_H
#define DATASTRUCTURE_DEQUE_H

#include <iostream>
#include "Queue.h"

template<typename T>
class Deque: public Queue<T> {
public:
    virtual bool getHead(T& x)const = 0;
    virtual bool getTail(T& x)const = 0;
    virtual bool EnQueue(const T& x);
    virtual bool EnQueueHead(const T& x) = 0;
    virtual bool EnQueueTail(const T& x) = 0;
    virtual bool DeQueue(const T& x);
    virtual bool DeQueueHead(const T& x) = 0;
    virtual bool DeQueueTail(const T& x) = 0;
};

template<typename T>
bool Deque<T>::EnQueue(const T &x) {
    return EnQueueTail(x);
}

template<typename T>
bool Deque<T>::DeQueue(const T &x) {
    T temp;
    bool tag = DeQueueHead(temp);
    x = temp;
    return tag;
}

#endif //DATASTRUCTURE_DEQUE_H

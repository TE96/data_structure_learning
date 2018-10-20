//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_SEQDEQUE_H
#define DATASTRUCTURE_SEQDEQUE_H

#include "Deque.h"
#include "SeqQueue.h"


template<typename T>
class SeqDeque: public Deque<T>, public SeqQueue<T> {
public:
    SeqDeque(int sz):SeqQueue<T>(sz){};
    ~SeqDeque(){};
    bool getHead(T& x)const;
    bool getTail(T& x)const;
    bool EnQueue(const T& x) { return EnQueueTail(x); }
    bool EnQueueHead(const T& x);
    bool EnQueueTail(const T& x);
    bool DeQueue(const T& x) { return DeQueueHead(x); }
    bool DeQueueHead(const T& x);
    bool DeQueueTail(const T& x);
};

template<typename T>
bool SeqDeque<T>::getHead(T &x) const {
    T temp;
    bool tag = SeqQueue<T>::getFront(temp);
    x = temp;
    return tag;
}

template<typename T>
bool SeqDeque<T>::getTail(T &x) const {
    if ( front == rear )
        return false;
    x = elements[(rear - 1 + maxSize) % maxSize];
}

template<typename T>
bool SeqDeque<T>::EnQueueHead(const T &x) {
    if ( (rear + 1) % maxSize == front )        //队满
        return false;
    front = (front - 1 + maxSize) % maxSize;
    elements[front] = x;
    return true;
}

template<typename T>
bool SeqDeque<T>::EnQueueTail(const T &x) {
    return SeqQueue<T>::EnQueue(x);
}

template<typename T>
bool SeqDeque<T>::DeQueueHead(const T &x) {
    T temp;
    bool tag = SeqQueue<T>::DeQueue(temp);
    x = temp;
    return tag;
}

template<typename T>
bool SeqDeque<T>::DeQueueTail(const T &x) {
    if ( front == rear )        //队空
        return false;
    rear = (rear - 1 + maxSize) % maxSize;
    x = elements[rear];
    return true;
}

#endif //DATASTRUCTURE_SEQDEQUE_H

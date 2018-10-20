//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

const int maxSize = 50;
template <typename T>
class Queue {
public:
    Queue(){};
    ~Queue(){};
    virtual void EnQueue(const T& x) = 0;
    virtual bool DeQueue(T& x) = 0;
    virtual bool getFront(T& x) = 0;
    virtual bool IsEmpty()const = 0;
    virtual bool IsFull()const = 0;
    virtual int getSize()const = 0;
};

#endif //DATASTRUCTURE_QUEUE_H

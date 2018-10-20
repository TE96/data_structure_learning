//
// Created by fuwuchen on 18-10-12.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

const int maxSize = 50;
template <typename T>
class Stack {
public:
    virtual void Push(const T& x) = 0;
    virtual bool Pop(T& x) = 0;
    virtual bool getTop(T& x) const = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual int getSize() const = 0;
};

#endif //DATASTRUCTURE_STACK_H

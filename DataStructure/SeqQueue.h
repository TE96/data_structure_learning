//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_SEQQUEUE_H
#define DATASTRUCTURE_SEQQUEUE_H

#include <assert.h>
#include <iostream>
#include "Queue.h"

using namespace std;

template <typename T>
class SeqQueue: public Queue<T> {
public:
    SeqQueue(int sz = 10);
    ~SeqQueue() { delete[] elements; }
    bool EnQueue(const T& x);               //若队列不满,则将x进队,否则队溢出处理.
    bool DeQueue(T& x);                     //若队列不空,则退出队头元素的值,否则返回false.
    bool getFront(T& x);                    //若队列不为空,则函数返回true及队头元素的值,否则返回false.
    void makeEmpty() { front = rear = 0; }   //置空操作:队头指针和队尾指针置0;
    bool IsEmpty()const { return (front == rear); }
    bool IsFull()const { return ((rear + 1) % maxSize == front); }
    int getSize()const { return (rear - front + maxSize) % maxSize; }
    friend ostream&operator << (ostream& os, SeqQueue<T>& Q);

protected:
    int rear, front;
    T *elements;
    int maxSize;
};

template<typename T>
SeqQueue<T>::SeqQueue(int sz) {
    //建立一个最大具有maxSize个元素的空队列
    elements = new T[maxSize];
    assert(elements != NULL);               //断言:动态存储分配成功与否
}

template<typename T>
bool SeqQueue<T>::EnQueue(const T &x) {
    //若队列不满,则将元素x插入到该队列的队尾,否则出错处理
    if ( IsFull() )
        return false;                       //队列满则插入失败,返回
    elements[rear] = x;                     //按照队尾指针指示位置插入
    rear = (rear + 1) % maxSize;
    return true;
}

template<typename T>
bool SeqQueue<T>::DeQueue(T &x) {
    //若队列不空则函数退掉一个队头元素并返回true,否则函数返回false
    if ( IsEmpty() )
        return false;
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
}

template<typename T>
bool SeqQueue<T>::getFront(T &x) {
    //若队列不空则函数返回该队列队头元素的值
    if ( IsEmpty() )
        return false;
    x = elements[front];
    return true;
}

template <typename T>
ostream &operator<<(ostream &os, SeqQueue<T> &Q) {
    //输出栈中元素的重载操作
    os << "front =" << Q.front << ", rear =" << Q.rear << endl;
    for ( int i = Q.front ; i != Q.rear ; i = (i + 1) % Q.maxSize )
        os << i << ":" << Q.elements[i] << endl;
    return os;
}

#endif //DATASTRUCTURE_SEQQUEUE_H

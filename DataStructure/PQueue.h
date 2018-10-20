//
// Created by fuwuchen on 18-10-13.
//

#ifndef DATASTRUCTURE_PQUEUE_H
#define DATASTRUCTURE_PQUEUE_H

#include <assert.h>
#include <iostream>
#include <stdlib.h>

const int DefaultPQSize = 50;
template<typename T>
class PQueue {
public:
    PQueue(int sz = DefaultPQSize);
    ~PQueue() { delete[] pqelements; }
    bool Insert(const T& x);
    bool RemoveMin(T& x);
    bool getFront(T& x)const;
    void makeEmpty() { count = 0; }
    bool IsEmpty()const { return ( count == 0 ); }
    bool IsFull()const { return ( count == maxSize ); }
    int getSize()const { return count; }

protected:
    T *pqelements;                      //优先级队列数组
    int count;                          //当前元素个数(长度)
    int maxSize;                        //队列最大可容纳元素个数
    void adjust();                      //队列调整
};

template<typename T>
PQueue<T>::PQueue(int sz): maxSize(sz), count(0) {
    //构造函数:建立一个最大具有maxSize个元素的空优先级队列
    pqelements = new T[maxSize];        //创建队列空间
    assert(pqelements != NULL);         //断言:动态存储分配成功与否
}

template<typename T>
bool PQueue<T>::Insert(const T &x) {
    //若优先级队列不满,则将元素x插入到该队列的队尾,否则出错处理
    if ( count == maxSize )
        return false;
    pqelements[count ++] = x;           //插入x到队尾
    adjust();
}

template<typename T>
void PQueue<T>::adjust() {
    //将队尾元素按其优先权大小调整到适当位置,保持所有元素按优先权从小到大有序
    T item = pqelements[count - 1];
    int j = count - 2;
    for ( ; j >= 0 ; --j ) {
        if( pqelements[j] <= item )
            break;                              //发现有比item更小或相等的pqelements[j]跳出循环
        else
            pqelements[j + 1] = pqelements[j];  //比item大的元素pqelements[j]后移
    }
    pqelements[j + 1] = item;
}

template<typename T>
bool PQueue<T>::RemoveMin(T &x) {
    //若优先级队列不空则函数返回该队列具最大优先权(值最小)元素的值,同时将该元素删除
    if ( count == 0 )
        return false;
    x = pqelements[0];
    for ( int i = 1 ; i < count ; ++i)
        pqelements[i - 1] = pqelements[i];
    count --;                                   //优先级队列元素个数减一
    return true;
}

template<typename T>
bool PQueue<T>::getFront(T &x) const {
    if ( count == 0 )
        return false;
    else
        return pqelements[0];                   //返回具最小优先权元素的值
}

#endif //DATASTRUCTURE_PQUEUE_H

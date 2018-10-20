//
// Created by fuwuchen on 18-10-12.
//

#ifndef DATASTRUCTURE_SEQSTACK_H
#define DATASTRUCTURE_SEQSTACK_H

#include <assert.h>
#include <iostream>
#include "Stack.h"

const int stackIncreament = 20;                     //栈溢出时扩展空间的增量
template <typename T>
class SeqStack: public Stack<T> {
public:
    explicit SeqStack(int sz = 50);
    ~SeqStack() { delete[] elements; }
    void Push(const T& x);                          //如果IsFull(),则溢出处理;否则把x插入到栈的栈顶
    bool Pop(T& x);                                 //如果IsEmpty(),则不执行退栈,返回false;
                                                    //否则退掉位于栈顶的元素,返回true,退出的元素值通过引用参数x返回
    bool getTop(T& x);                              //如果IsEmpty(),则返回false;否则返回true,并通过引用型参数x得到栈顶元素的值
    bool IsEmpty()const { return ( top == -1 ); }   //如果栈中元素个数等于0,则返回true,否则返回false
    bool IsFull()const { return ( top == maxSize - 1 ); }  //如果栈中元素个数等于maxSize,则返回true,否则返回false
    int getSize()const { return (top + 1); }        //函数返回栈中元素个数
    void MakeEmpty() { top = -1; }                   //清空栈的内容
    friend ostream&operator << (ostream& os, SeqStack<T>& s); //输出栈中元素的重载操作<<
private:
    T *elements;                                    //存放栈中元素的栈数组
    int top;                                        //栈顶指针
    int maxSize;                                    //栈最大可容纳元素个数
    void overflowProcess();                         //栈的溢出处理
};

template<typename T>
SeqStack<T>::SeqStack(int sz): top(-1), maxSize(sz) {
    //建立一个最大尺寸为sz的空栈,若分配不成功则错误处理.
    elements = new T[maxSize];
    assert(elements != NULL);
}

template<typename T>
void SeqStack<T>::overflowProcess() {
    //私有函数:扩充栈的存储空间
    T *newArray = new T[maxSize +  stackIncreament];
    if ( newArray == NULL ) {
        cerr << "存储分配失败!" << endl;
        exit(1);
    }
    for ( int i = 0 ; i <= top ; i ++ )
        newArray[i] = elements[i];
    maxSize = maxSize + stackIncreament;
    delete[]elements;
    elements = newArray;
}

template<typename T>
void SeqStack<T>::Push(const T &x) {
    //公共函数:若栈不满,则将元素x插入到该栈的栈顶,否则溢出处理
    if( IsFull() )
        overflowProcess();
    elements[++ top] = x;
}

template<typename T>
bool SeqStack<T>::Pop(T &x) {
    //公共函数:若栈不空则函数返回该栈栈顶元素的值,然后栈顶指针退1.
    if ( IsEmpty() )
        return false;
    x = elements[top --];
    return true;
}

template<typename T>
bool SeqStack<T>::getTop(T &x) {
    //公共函数:若栈不空则函数返回该栈栈顶元素的地址
    if ( IsEmpty() )
        return false;
    x = elements[top];
    return true;
}

template <typename T>
ostream &operator<<(ostream &os, SeqStack<T> &s) {
    //输出栈中元素的重载操作 <<
    os << "top = " << s.top << endl;                //输出栈顶位置
    for ( int i = 0 ; i <= s.top ; ++i)             //逐个输出栈中元素的值
        os << i << " : " << s.elements[i] << endl;
    return os;
}

#endif //DATASTRUCTURE_SEQSTACK_H

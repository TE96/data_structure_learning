//
// Created by fuwuchen on 18-10-19.
//

#ifndef DATASTRUCTURE_MINSPANTREE_H
#define DATASTRUCTURE_MINSPANTREE_H

#include <iostream>
#include "assert.h"

using namespace std;

const double maxValue = 99999999.0;
const int DefaultSize2 = 50;

template<typename T, typename E>
struct MSTEdgeNode {
    int tail, head;                         //两顶点位置
    E key;
    MSTEdgeNode(): tail(-1),head(-1),key(0){}

    friend bool operator < (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
    friend bool operator > (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
    friend bool operator == (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
    friend bool operator <= (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2);
};

template <typename T, typename E>
bool operator < (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2) {
    return n1.key < n2.key;
}

template <typename T, typename E>
bool operator > (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2) {
    return n1.key > n2.key;
}

template <typename T, typename E>
bool operator == (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2) {
    return n1.key == n2.key;
}

template <typename T, typename E>
bool operator <= (MSTEdgeNode<T,E> &n1, MSTEdgeNode<T,E> &n2) {
    return n1.key <= n2.key;
}

template<typename T, typename E>
class MinSpanTree {
protected:
    MSTEdgeNode<T,E> *edgevalue;            //用边值数组表示树
    int maxSize, n;                         //数组最大元素个数和当前个数
public:
    MinSpanTree(int sz = DefaultSize2): maxSize(sz), n(0) {
        edgevalue = new MSTEdgeNode<T,E>[sz];
        assert(edgevalue);
    }
    int Insert(MSTEdgeNode<T,E>& item);
};

template<typename T, typename E>
int MinSpanTree<T, E>::Insert(MSTEdgeNode<T, E> &item) {
    if ( n == maxSize )
        return false;
    edgevalue[n] = item;
    n ++;
    return true;
}

#endif //DATASTRUCTURE_MINSPANTREE_H

//
// Created by fuwuchen on 18-10-16.
//

#ifndef DATASTRUCTURE_SORTEDLIST_H
#define DATASTRUCTURE_SORTEDLIST_H


#include "SearchList.h"

template<typename E, typename K>
class SortedList: public SearchList<E, K> {
public:
    SortedList(int sz = 100): SearchList<E,K>(sz) {}
    ~SortedList(){}
    int SeqentSearch(const K x)const;                       //顺序搜索
    int BinarySearch(const K x)const;                       //折半搜索
    int BinarySearch1(const K x, int low, int high);        //折半搜索递归算法
    int FibonacciSearch(K k1);                              //斐波那契搜索
    bool Insert(const E& el);                               //有序插入
    int Begin() {
        return ( CurrentSize == 0 ) ? 0 : 1;                //定位第一个
    }
    int Next(int i) {
        return ( i > 1 && i <= CurrentSize ) ? i + 1 : 0;   //定位下一个
    }
protected:
    DataNode<E,K> *Element;                                 //数据表中存储数据的数组
    int ArraySize, CurrentSize;                             //数组最大长度和当前长度
};

template<typename E, typename K>
int SortedList<E, K>::SeqentSearch(const K x) const {
    //顺序搜索关键码为x的数据元素
    for ( int i = 1 ; i <=CurrentSize ; ++i) {
        if ( Element[i - 1].key == x )                      //成功,停止搜索
            return i;
        else if ( Element[i - 1].key > x )                  //不成功,停止搜索
            break;
    }
    return 0;                                               //顺序搜索失败
}                                                           //实际元素序号与数组下标差1

template<typename E, typename K>
int SortedList<E, K>::BinarySearch(const K x) const {
    //迭代算法
    int high = CurrentSize - 1, low = 0, mid;
    while ( low <= high ) {
        mid = ( low + high ) / 2;
        if ( x > Element[mid].key )
            low = mid + 1;                                  //右缩搜索区间
        else if ( x < Element[mid].key )
            high = mid - 1;                                 //左缩搜索区间
        else
            return mid + 1;                                 //搜索成功
    }
    return 0;
}

template<typename E, typename K>
int SortedList<E, K>::BinarySearch1(const K x, int low, int high) {
    //递归算法:在搜索区间[low..high]采用折半搜索算法搜索与给定元素匹配的元素
    //此程序中low与high的值从1到CurrentSize.
    int mid = 0;
    if ( low <= high ) {
        mid = ( low + high ) / 2;
        if ( x > Element[mid-1].key )                       //右缩搜索区间
            mid = BinarySearch1(x, mid + 1, high);
        else if ( x < Element[mid - 1].key )                //左缩搜索区间
            mid = BinarySearch1(x, low, mid - 1);
    }
    return mid;                                             //实际元素序号与数组下标差1
}

template<typename E, typename K>
bool SortedList<E, K>::Insert(const E &el) {
    assert(CurrentSize == ArraySize);                       //断言:不满足则终止插入
    int i = 1;                                              //查找插入位置
    while ( i <= CurrentSize && Element[i - 1].key <= el.key )
        i ++;
    for ( int j = CurrentSize ; j >= i ; j-- )
        Element[j] = Element[j - 1];
    Element[i - 1] = el;
    CurrentSize ++;
    return true;
}

//TODO:FibonacciSearch
template<typename E, typename K>
int SortedList<E, K>::FibonacciSearch(K k1) {
    return 0;
}


#endif //DATASTRUCTURE_SORTEDLIST_H

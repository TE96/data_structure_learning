//
// Created by fuwuchen on 18-10-19.
//

#ifndef DATASTRUCTURE_MINHEAP_H
#define DATASTRUCTURE_MINHEAP_H

#include <iostream>
#include <cassert>

using namespace std;

const int DefaultSize = 50;

template<typename T, typename Item>
class MinHeap {
public:
    MinHeap(int sz = DefaultSize);
    MinHeap(Item arr[], int n);
    ~MinHeap() {
        delete []heap;
    }
    bool Insert(const Item &x);
    bool RemoveMin(Item &x);
    bool IsEmpty()const {
        return currentSize == 0;
    }
    bool IsFull()const {
        return currentSize == maxHeapSize;
    }
    void MakeEmpty() {
        currentSize = 0;
    }

    void output() {
        for ( int i = 0 ; i < currentSize ; i ++ )
            cout << heap[i] << ' ';
        cout << endl;
    }

private:
    Item *heap;
    int currentSize;
    int maxHeapSize;
    void siftDown(int start, int m);
    void siftUp(int start);
};

template<typename T, typename Item>
MinHeap<T, Item>::MinHeap(int sz) {
    maxHeapSize = ( DefaultSize < sz ) ? sz : DefaultSize;
    heap = new Item[maxHeapSize];
    assert(heap);
    currentSize = 0;
}

template<typename T, typename Item>
MinHeap<T, Item>::MinHeap(Item *arr, int n) {
    maxHeapSize = ( DefaultSize < sz ) ? sz : DefaultSize;
    heap = new Item[maxHeapSize];
    assert(heap);
    for ( int i = 0 ; i < currentSize ; i ++ )
        heap[i] = arr[i];
    currentSize = n;
    int currentPos = ( currentSize - 2 ) / 2;       //找最初调整位置：最后分支结点
    while ( currentPos >= 0 ) {                     //自底向上逐步扩大形成堆
        siftDown(currentPos, currentSize - 1);      //局部自上向下下滑调整
        currentPos --;                              //再向前换一个分支节点
    }
}

template<typename T, typename Item>
bool MinHeap<T, Item>::Insert(const Item &x) {
    if ( currentSize == maxHeapSize ) {
        cerr << "Heap Full" << endl;
        exit(1);
    }
    heap[currentSize] = x;                          //插入
    siftUp(currentSize);                            //向上调整
    currentSize ++;                                 //堆计数加1
    return true;
}

template<typename T, typename Item>
bool MinHeap<T, Item>::RemoveMin(Item &x) {
    if ( !currentSize ) {
        cerr << "Heap Empty" << endl;
        exit(1);
    }
    x = heap[0];                                    //返回最小元素
    heap[0] = heap[currentSize - 1];                //最后元素填补到根节点
    currentSize --;
    siftDown(0, currentSize - 1);                   //自上向下调整为堆
    return true;
}

template<typename T, typename Item>
void MinHeap<T, Item>::siftDown(int start, int m) {
    //私有函数:最小堆的下滑调整算法
    int i = start, j = 2 * i + 1;                   //j是i的左子女位置
    Item temp = heap[i];
    while ( j <= m ) {                              //检查是否到最后位置
        if ( j < m && heap[j] > heap[j + 1] )       //让j指向两子女中的小者
            j ++;
        if ( temp <= heap[j] )
            break;
        else {
            heap[i] = heap[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    heap[i] = temp;                                 //回放temp中暂存的元素
}

template<typename T, typename Item>
void MinHeap<T, Item>::siftUp(int start) {
    //私有函数:最小堆的上滑调整算法
    int j = start, i = ( j - 1 ) / 2 ;
    Item temp = heap[j];
    while ( j > 0 ) {                               //沿父结点路径向上直达根
        if ( heap[i] <= temp )
            break;
        else {
            heap[j] = heap[i];
            j = i;
            i = ( j - 1 ) / 2 ;
        }
    }
    heap[j] = temp;                                 //回放temp中暂存的元素
}


#endif //DATASTRUCTURE_MINHEAP_H

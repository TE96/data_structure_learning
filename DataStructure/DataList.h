//
// Created by fuwuchen on 18-10-16.
//

#ifndef DATASTRUCTURE_DATALIST_H
#define DATASTRUCTURE_DATALIST_H

#include <iostream>
#include <assert.h>

using namespace std;

const int defaultSize = 100;
template<typename E, typename K>
class DataList;                                     //数据表类的前视定义

template<typename E, typename K>
class DataNode {
friend class DataList<E, K>;
public:
    DataNode(const K x): key(x) {}
    K getKey()const {
        return key;
    }
    void setKey(K k) {
        key = k;
    }

private:
    K key;
};

template<typename E, typename K>
class DataList {
public:
    DataList(int sz = defaultSize): ArraySize(sz), CurrentSize(0) {
        Element = new DataNode<E,K>[sz];
        assert(Element != NULL);
    }
    DataList(DataList<E,K>& R);
    virtual ~DataList() {
        delete[] Element;
    }
    virtual int Length() {
        return CurrentSize;
    }
    virtual K getKey(int i)const {
        assert(i > 0 || i <= CurrentSize);
        return Element[i - 1].key;
    }
    virtual void setKey(K x, int i) {
        assert(i > 0 || i <= CurrentSize);
        Element[i - 1].key = x;
    }
    virtual int SeqSearch(const K x)const;
    virtual int SeqSearch1(const K x, int loc)const {
        if ( loc > CurrentSize )
            return 0;
        else if ( Element[loc - 1].key == x )
            return loc;
        else
            return SeqSearch1(x, loc + 1);
    }
    virtual bool Insert(E& el);
    virtual bool Remove(const K x, E& el);
    friend ostream&operator << (ostream& out, const DataList<E,K>& OutList);
    friend istream&operator >> (istream& in, DataList<E,K>& InList);

protected:
    DataNode<E,K> *Element;                         //数据表中存储数据的数组
    int ArraySize, CurrentSize;                     //数组最大长度和当前长度
};

template<typename E, typename K>
bool DataList<E, K>::Insert(E &el) {
    //在DataList的尾部插入新元素el,若插入失败函数返回false,否则返回true
    if ( CurrentSize == ArraySize )
        return false;
    Element[CurrentSize] = el;                      //插入在尾端
    CurrentSize ++;
    return true;
}

template<typename E, typename K>
bool DataList<E, K>::Remove(const K x, E &el) {
    //在DalaList中删除关键码为x的元素,通过el返回,用为元素填补被删除元素
    if ( CurrentSize == 0 )
        return false;
    int i;
    for ( i = 0 ; i < CurrentSize && Element[i].key != x ; i++ );
    if ( i == CurrentSize )
        return false;
    el = Element[i];                                //找到,保存被删元素的值
    Element[i] = Element[CurrentSize - 1];          //填补
    CurrentSize --;
    return true;
}

template<typename E, typename K>
ostream &operator<<(ostream &out, const DataList<E, K> &OutList) {
    out << "Array Contents : \n";
    for ( int i = 1 ; i < OutList ; ++i )
        out << OutList.Element[i - 1] << ' ';
    out << endl;
    out << "Array Current Size :" << OutList.CurrentSize << endl;
    return out;
}

template<typename E, typename K>
istream &operator>>(istream &in, DataList<E, K> &InList) {
    cout << "Enter array Current Size: ";
    in >> InList.CurrentSize;
    cout << "Enter array elements : \n";
    for ( int i = 1 ; i <= InList.CurrentSize ; ++i ) {
        cout << "Element" << i << " : ";
        in >> InList.Element[i - 1];
    }
    return in;
}

template<typename E, typename K>
int DataList<E, K>::SeqSearch(const K x) const {
    //在搜索表SearchList中顺序搜索其关键码为x的数据元素,要求数据元素在表中从下标0
    //开始存放,CurrentSize号位置作为控制搜索过程自动结束的"监视哨"使用.若找到则
    //函数返回该元素在表中的位置i,否则返回CurrentSize
    Element[CurrentSize].key = x;
    int i = 0;                                      //将x设置为监视哨
    while ( Element[i].key != x )                   //从前向后顺序搜索
        i ++;
    return i + 1;
}



#endif //DATASTRUCTURE_DATALIST_H

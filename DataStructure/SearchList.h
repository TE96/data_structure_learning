//
// Created by fuwuchen on 18-10-16.
//

#ifndef DATASTRUCTURE_SEARCHLIST_H
#define DATASTRUCTURE_SEARCHLIST_H

#include "DataList.h"

template<typename E, typename K>
class SearchList: public DataList<E,K> {
    //搜索表SearchList继承了DataList,并且增加了成员函数Search()
public:
    SearchList(int sz = defaultSize): DataList<E,K>(sz){}
    virtual int SeqSearch(const K x)const;
protected:
    DataNode<E,K> *Element;                         //数据表中存储数据的数组
    int ArraySize, CurrentSize;                     //数组最大长度和当前长度
};

template<typename E, typename K>
int SearchList<E, K>::SeqSearch(const K x) const {
    return DataList<E,K>::SeqSearch(x);
}

#endif //DATASTRUCTURE_SEARCHLIST_H

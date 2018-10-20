//
// Created by fuwuchen on 18-10-19.
//

#ifndef DATASTRUCTURE_UFSETS_H
#define DATASTRUCTURE_UFSETS_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int DefaultSize1 = 10;

class UFSets {
public:
    UFSets(int sz = DefaultSize1);
    UFSets(UFSets &R);
    ~UFSets(){
        delete[]parent;
    }
    UFSets&operator = (UFSets &R);
    void SimpleUnion(int Root1, int Root2);
    int Find(int x);
    void WeightedUnion(int Root1, int Root2);
    int CollapsingFind(int i);
    void output(ostream& out = cout);

    friend ostream& operator << (ostream &out, UFSets &R){
        int i;
        out << "\n" << string(70, '=');
        for (int j = 0; j <= (R.size-1)/10; j++){
            out << "\nNode:\t";
            for(i = 10*j; i < 10*(j+1) && i < R.size; i++){
                out << setw(6) << i;
            }
            cout << "\nParent:\t";
            for(i = 10*j; i < 10*(j+1) && i < R.size; i++){
                out << setw(6) << R.parent[i];
            }
            if (i < R.size){
                out << "\n" << string(70, '-');
            }
        }
        out << "\n" << string(70, '=') << "\n";
        return out;
    }

private:
    int *parent;
    int size;
};

UFSets::UFSets(int sz) {
    //构造函数:s是集合元素个数,父指针数组的范围为parent[0]~parent[size-1]
    size = sz;
    parent = new int[size];
    for ( int i = 0 ; i < size ; ++ i )
        parent[i] = -1;
}

UFSets::UFSets(UFSets &R) {
    //复制构造函数
    size = R.size;
    parent = new int[size];
    for (int i = 0; i < size; i++)
        parent[i] = R.parent[i];
}

UFSets &UFSets::operator=(UFSets &R) {
    size = R.size;
    parent = new int[size];
    for (int i = 0; i < size; i++)
        parent[i] = R.parent[i];
    return *this;
}

int UFSets::Find(int x) {
    //函数搜索并返回包含元素x的树的根
    while ( parent[x] >= 0 )            //循链寻找x的根
        x = parent[x];
    return x;                           //根的Parent[]值小于0
}

void UFSets::SimpleUnion(int Root1, int Root2) {
    int r1 = Find(Root1), r2 = Find(Root2);
    if ( r1 != r2 ) {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
}

void UFSets::WeightedUnion(int Root1, int Root2) {
    int r1 = Find(Root1), r2 = Find(Root2), temp;
    if ( r1 != r2 ) {
        temp = parent[r1] + parent[r2];
        if ( parent[r2] < parent[r1] ) {
            parent[r1] = r2;
            parent[r2] = temp;
        }
        else {
            parent[r2] = r1;
            parent[r1] = temp;
        }
    }
}

int UFSets::CollapsingFind(int i) {
    int j = i;
    for ( ; parent[j] >= 0 ; j = parent[j] );
    while ( i != j ) {
        int temp = parent[i];
        parent[i] = j;
        i = temp;
    }
    return j;
}

void UFSets::output(ostream &out) {
    int i;
    out << "\n" << string(70, '=');
    for (int j = 0; j <= (size-1)/10; j++){
        out << "\nNode:\t";
        for(i = 10*j; i < 10*(j+1) && i < size; i++){
            out << setw(6) << i;
        }
        out << "\nParent:\t";
        for(i = 10*j; i < 10*(j+1) && i < size; i++){
            out << setw(6) << parent[i];
        }
        if (i < size){
            out << "\n" << string(70, '-');
        }
    }
    cout << "\n" << string(70, '=') << "\n";
}

#endif //DATASTRUCTURE_UFSETS_H

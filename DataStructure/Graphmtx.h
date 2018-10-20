//
// Created by fuwuchen on 18-10-18.
//

#ifndef DATASTRUCTURE_GRAPHMTX_H
#define DATASTRUCTURE_GRAPHMTX_H

#include <iostream>
#include "Graph.h"


using namespace std;

template<typename T,typename E>
class Graphmtx: public Graph<T,E> {
    friend istream&operator>>(istream& in, Graphmtx<T,E>& G);
    friend ostream&operator<<(ostream& out, Graphmtx<T,E>& G);

public:
    Graphmtx(int sz = DefaultVertices);
    ~Graphmtx() {
        delete []VerticesList;
        delete []Edge;
    }
    T getValue(int i) {
        return i >= 0 && i <= numVertices ? VerticesList[i] : NULL;
    }
    E getWeight(int v1, int v2) {                   //取边(v1,v2)上的权值
        return i >= 0 && i < numVertices ? VertexList[i] : 0;
    }
    int getVertexPos(T vertex) {
        for ( int i = 0 ; i < numVertices ; ++i )
            if ( VerticesList[i] == vertex )
                return i;
        return -1;
    }
    int getFirstNeighbor(int v);                    //取顶点v的第一个邻接顶点
    int getNextNeighbor(int v, int w);              //取邻接顶点w的下一邻接顶点
    bool insertVertex(const T& vertex);             //插入顶点vertex
    bool insertEdge(int v1, int v2, E cost);        //插入边(v1,v2),权值为cost
    bool removeVertex(int v);                       //删去顶点v和所有与它相关联的边
    bool removeEdge(int v1, int v2);                //在图中删去边(v1,v2)

private:
    T *VerticesList;
    E * * Edge;

};

template<typename T, typename E>
Graphmtx<T, E>::Graphmtx(int sz) {
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    int i, j;
    VerticesList = new T[maxVertices];              //创建顶点表数组
    Edge = (int * *)new int *[maxVertices];         //创建邻接矩阵数组
    for ( i = 0 ; i < maxVertices ; ++i )
        Edge[i] = new int[maxVertices];
    for ( int j = 0; j < maxVertices ; ++j )
        Edge[i][j] = ( i == j ) ? 0 : maxWeight;
}

template<typename T, typename E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
    //给出顶点位置为v的第一个邻接顶点的位置,如果找不到,则函数返回-1
    if ( v != -1 ) {
        for ( int col = 0; col < numVertices ; col ++ )
            if ( Edge[v][col] > 0 && Edge[v][col] < maxWeight )
                return col;
    }
    return -1;
}

template<typename T, typename E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
    //给出顶点v的某邻接顶点w的下一个邻接顶点
    if ( v != -1 && w != -1 ) {
        for ( int col = w + 1 ; col < numVertices ; col ++ )
            if ( Edge[v][col] > 0 && Edge[v][col] < maxWeight )
                return col;
    }
    return -1;
}

template<typename T, typename E>
bool Graphmtx<T, E>::insertVertex(const T &vertex) {
    //插入顶点vertex
    if ( numVertices == maxVertices )
        return false;
    VerticesList[numVertices++] = vertex;
    return true;
}

template<typename T, typename E>
bool Graphmtx<T, E>::removeVertex(int v) {
    //删去顶点v和所有与它相关联的边
    if ( v < 0 && v >= numVertices )
        return false;                               //v不在图中,不删除
    if ( numVertices == 1 )
        return false;                               //只有一个顶点,不删除
    int i, j;
    VerticesList[v] = VerticesList[numVertices - 1];//顶点表中删除该结点
    for ( i = 0 ; i < numVertices ; i ++ )          //减去与v相关联边数
        if ( Edge[i][col] > 0 && Edge[i][col] < maxWeight )
            numEdges --;
    for ( i = 0 ; i < numVertices ; i ++ )          //用最后一列填补第v列
        Edge[i][v] = Edge[i][numVertices - 1];
    numVertices --;                                 //顶点数减1
    for ( j = 0 ; j < numVertices ; j ++ )          //用最后一行填补第v行
        Edge[v][j] = Edge[numVertices - 1][j];
    return true;
}

template<typename T, typename E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
    //插入边(v1,v2),权值为const
    if ( v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices &&
            Edge[v1][v2] == maxWeight ) {           //插入条件
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges ++;
        return true;
    }
    else
        return false;
}

template<typename T, typename E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
    if ( v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices &&
            Edge[v1][v2] > 0 && Edge[v2][v1] < maxWeight) {
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges --;
        return true;
    }
    else
        return false;
}

template<typename T, typename E>
istream &operator>>(istream &in, Graphmtx<T, E> &G) {
    int i, j, k, n, m;
    T e1, e2;
    E weight;
    in >> n >> m;                       //输入顶点数n和边数m
    for ( i = 0 ; i < n ; i ++ ) {      //建立顶点表数据
        in >> el;
        G.insertVertex(el);
    }
    i = 0;
    while ( i < m ) {
        in >> e1 >> e2 >> weight;       //输入端点信息
        j = G.getVertexPos(e1);
        k = G.getVertexPos(e2);         //查顶点号
        if ( j == -1 || k == -1 )
            cout << "边两端点信息有误,重新输入!" << endl;
        else {
            G.insertEdge(j, k, weight);
            i ++;
        }
    }
    return in;
}

template<typename T, typename E>
ostream &operator<<(ostream &out, Graphmtx<T, E> &G) {
    int i, j, n, m;
    T e1, e2;
    E w;
    n = G.NumberOfVertices();
    m = G.NumberOfEdges();
    out << n << "," << m << endl;                   //输出顶点数和边数
    for ( i = 0 ; i < n ; i ++ )
        for ( j = i + 1 ; j < n ; j ++ ) {
            w = G.getWeight(i, j);                  //取边上权值
            if ( w > 0 and w < maxWeight ) {
                e1 = G.getValue(i);
                e2 = G.getValue(j);
                out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
            }
        }
    return out;
}

#endif //DATASTRUCTURE_GRAPHMTX_H

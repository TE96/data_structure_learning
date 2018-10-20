//
// Created by fuwuchen on 18-10-18.
//

#ifndef DATASTRUCTURE_GRAPHLNK_H
#define DATASTRUCTURE_GRAPHLNK_H

#include <iostream>
#include "Graph.h"

using namespace std;

template<typename T, typename E>
struct Edge {
    int dest;                       //边的另一顶点位置
    E cost;                         //边上的权值
    Edge<T,E> *link;                //下一条边链指针
    Edge(){}
    Edge(int num, E weight): dest(num), cost(weight), link(NULL){}
    bool operator!=(Edge<T,E>& R)const {
        return (dest != R.dest);
    }
};

template<typename T, typename E>
struct Vertex {
    T data;                         //顶点的名字
    Edge<T,E> *adj;                 //边链表的头指针
};

template<typename T, typename E>
class Graphlnk: public Graph<T,E> {
    friend istream&operator>>(istream& in, Graphlnk<T,E>& G);
    friend ostream&operator<<(ostream& out, Graphlnk<T,E>& G);

public:
    Graphlnk(int sz = DefaultVertices);
    ~Graphlnk();
    T getValue(int i) {
        return i >= 0 && i <= numVertices ? NodeTable[i] : NULL;
    }
    E getWeight(int v1, int v2);                    //取边(v1,v2)上的权值
    int getVertexPos(const T vertex) {
        for ( int i = 0 ; i < numVertices ; ++i )
            if ( NodeTable[i].data == vertex )
                return i;
        return -1;
    }
    int getFirstNeighbor(int v);                    //取顶点v的第一个邻接顶点
    int getNextNeighbor(int v, int w);              //取邻接顶点w的下一邻接顶点
    bool insertVertex(const T& vertex);             //插入顶点vertex
    bool insertEdge(int v1, int v2, E weight);        //插入边(v1,v2),权值为weight
    bool removeVertex(int v);                       //删去顶点v和所有与它相关联的边
    bool removeEdge(int v1, int v2);                //在图中删去边(v1,v2)

private:
    Vertex<T,E> *NodeTable;                         //顶点表(各边链表的头结点)
};

template<typename T, typename E>
Graphlnk<T, E>::Graphlnk(int sz):Graph<T,E>(sz) {
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    NodeTable = new Vertex<T,E>[maxVertices];       //创建顶点表数组
    if ( NodeTable == NULL ) {
        cerr << "存储分配错误!" << endl;
        exit(1);
    }
    for ( int i = 0 ; i < maxVertices; i ++ )
        NodeTable[i].adj = NULL;
}

template<typename T, typename E>
Graphlnk<T, E>::~Graphlnk() {
    for ( int i = 0 ; i < numVertices; i ++ ) {     //删除各边链表中的结点
        Edge<T,E> *p = NodeTable[i].adj;            //找到其对应边链表的首结点
        while ( p != NULL ) {                       //不断地删除第一个结点
            NodeTable[i].adj = p->link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete []NodeTable;                             //删除顶点表数组
}

template<typename T, typename E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
    //给出顶点位置为v的第一个邻接顶点的位置,如果找不到,则函数返回-1.
    if ( v != -1 ) {                                //顶点v存在
        Edge<T,E> *p = NodeTable[v].adj;            //对应边链表第一个边结点
        if ( p != NULL )
            return p->dest;                         //存在,返回第一个邻接顶点
    }
    return -1;                                      //第一个邻接顶点不存在
}

template<typename T, typename E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
    //给出顶点v的邻接顶点w下一个邻接顶点的位置,若没有下一个邻接顶点,则函数返回-1.
    if ( v != -1 ) {                                //顶点v存在
        Edge<T,E> *p = NodeTable[v].adj;            //对应边链表第一个边结点
        while ( p != NULL && p->dest != w )         //寻找邻接顶点w
            p = p->link;
        if ( p != NULL )
            return p->link->dest;                   //返回下一个邻接顶点
    }
    return -1;                                      //下一个邻接顶点不存在
}

template<typename T, typename E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
    //函数返回边(v1,v2)上的权值,若该边不在图中,则函数返回权值0
    if ( v1 != -1 && v2 != -1 ) {
        Edge<T,E> *p = NodeTable[v1].adj;
        while ( p != NULL && p->dest != v2 )        //寻找邻接顶点v2
            p = p->link;
        if ( p != NULL )
            return p->cost;                         //找到此边,返回权值.
    }
    return 0;                                       //边(v1,v2)不存在
}

template<typename T, typename E>
bool Graphlnk<T, E>::insertVertex(const T &vertex) {
    //在图的顶点表中插入一个新顶点vertex.若插入成功,函数返回true,否则返回false
    if ( numVertices == maxVertices )
        return false;
    NodeTable[numVertices].data = vertex;           //插入在表的最后
    numVertices ++;
    return true;
}

template<typename T, typename E>
bool Graphlnk<T, E>::removeVertex(int v) {
    //在图中删除一个指定顶点v,v是顶点号.若删除成功,函数返回true,否则返回false
    if ( numVertices == 1 || v < 0 || v >numVertices )
        return false;                               //表空或顶点号超出范围
    Edge<T,E> *p, *s, *t;
    int i, k;
    while ( NodeTable[v].adj != NULL ) {            //删除第v个边链表中所有结点
        p = NodeTable[v].adj;
        k = p->dest;                                //取邻接顶点k
        s = NodeTable[k].adj;
        t == NULL;                                  //找对称存放的边结点
        while ( s != NULL && s->dest != v ) {
            t = s;
            s = s->link;
        }
        if ( s != NULL ) {                          //删除对称存放的边结点
            if ( t == NULL )
                NodeTable[k].adj = s->link;
            else
                t->link = s->link;
            delete s;
        }
        NodeTable[v].adj = p->link;                 //清除顶点v的边链表结点
        delete p;
        numEdges --;
    }
    numVertices --;                                 //图的顶点个数减1
    NodeTable[v].data = NodeTable[numVertices].data;//填补
    NodeTable[v].adj = NodeTable[numVertices].adj;
    p = NodeTable[v].adj;
    while ( p != NULL ) {
        s = NodeTable[p->dest].adj;
        while ( s != NULL )
            if ( s->dest == numVertices ) {
                s->dest = v;
                break;
            }
            else
                s = s->link;
    }
    return true;
}

template<typename T, typename E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
    //在带权图中插入一条边(v1,v2),若此边存在或参数不合理,函数返回false,否则返回
    //true.对于非带全图,最后一个参数weight不要.算法中相应语句也不要
    if ( v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices ) {
        Edge<T,E> *q, *p = NodeTable[v1].adj;       //v1对应的边链表头指针
        while ( p != NULL && p->dest != v2 )        //寻找邻接顶点v2
            p = p->link;
        if ( p != NULL )
            return false;                           //找到此边,不插入
        p = new Edge<T,E>;
        q = new Edge<T,E>;                          //否则,创建新结点
        p->dest = v2;
        p->cost = weight;
        p->link = NodeTable[v1].adj;                //链入v1边链表
        NodeTable[v1].adj = p;
        q->dest = v1;
        q->cost = weight;
        q->link = NodeTable[v2].adj;                //链入v2边链表
        NodeTable[v2].adj = q;
        numEdges ++;
        return true;
    }
    return false;
}

template<typename T, typename E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2) {
    //在图中删除一条边(v1,v2)
    if ( v1 != -1 && v2 != -1 ) {
        Edge<T,E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
        while ( p != NULL && p->dest != v2 ) {      //v1对应边链表中找被删边
            q = p;
            p = p->link;
        }
        if ( p != NULL ) {                          //找到被删边结点
            if ( p == s )
                NodeTable[v1].adj = p->link;        //该结点是边链表首结点
            else
                q->link = p->link;                  //不是,重新链接
            delete p;
        }
        else
            return false;                           //没有找到被删边结点
        p = NodeTable[v2].adj;
        q = NULL;
        s = p;                                      //v2对应边链表中删除
        while ( p->dest != v1 ) {                   //寻找被删边结点
            q = p;
            p = p->link;
        }
        if ( p == s )                               //该结点是边链表首结点
            NodeTable[v2].adj = p->link;
        else
            q->link = p->link;                      //不是,重新链接.
        delete p;
        return true;
    }
    return false;
}

template<typename T, typename E>
istream &operator>>(istream &in, Graphlnk<T, E> &G) {
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
ostream &operator<<(ostream &out, Graphlnk<T, E> &G) {
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


#endif //DATASTRUCTURE_GRAPHLNK_H

//
// Created by fuwuchen on 18-10-18.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include <iostream>
#include "SeqQueue.h"
#include "Tree.h"
#include "MinSpanTree.h"
#include "MinHeap.h"
#include "UFSets.h"

using namespace std;

const int maxWeight = 2147483647;                   //无穷大
const int DefaultVertices = 30;                     //默认最大边数
template<typename T, typename E>
class Graph {
    //对象:由一个定点的非空集合和一个边集合构成,每条边由一个顶点对来表示
public:
    void DFS();
    void BFS();
    void Components();
    void Kruskal(MinSpanTree<T,E> &MST);
    void Prim(MinSpanTree<T,E> &MST);
    void DFSTree(Tree<T> &tree);
    Graph(int sz = DefaultVertices);
      //建立一个空的图
    ~Graph();
    bool GraphEmpty()const {
        return numEdges == 0;
    }
    bool GraphFull()const {
        return numVertices == maxVertices ||
        numEdges == maxVertices * ( maxVertices - 1) / 2;
    }
    int NumberOfVertices() {
        return numVertices;                         //返回当前顶点数
    }
    int NumberOfEdges() {
        return numEdges;                            //返回当前边数
    }
    int getVertexPos(T vertex);
    virtual T getValue(int i);                      //取顶点i的值,i不合理返回0
    virtual E getWeight(int v1, int v2);            //取边(v1,v2)上的权值
    virtual int getFirstNeighbor(int v);            //取顶点v的第一个邻接顶点
    virtual int getNextNeighbor(int v, int w);      //取邻接顶点w的下一邻接顶点
    virtual void insertVertex(const T& vertex);     //在图中插入一个顶点vertex,该顶点暂时没有入边
    virtual void insertEdge(int v1, int v2, E cost);//若构成边的两个顶点v1和v2是图中的顶点,则在图中插入一条边(v1,v2)
    virtual void removeVertex(int v);               //若被删顶点是图中的顶点,则删去顶点v和所有关联到它的边
    virtual void removeEdge(int v1, int v2);        //若构成边的两个顶点v1和v2是图中的顶点,则在图中删去 边(v1,v2)
    friend istream& operator >> (istream &in, Graph<T,E> &G){
        int i, j, k, n, m;
        T e1, e2;
        E weight;
        in >> n >> m ;
        for ( i = 0 ; i < n ; i ++ ){
            in >> e1;
            G.insertVertex(e1);
        }
        i = 0;
        while (i < m){
            assert(in >> e1 >> e2 >> weight);
            j = G.getVertexPos(e1);
            k = G.getVertexPos(e2);
            if ( j == -1 || k == -1 ) {
                cout << "Input error!\n";
            }
            else{
                G.insertEdge(j, k, weight);
                i++;
            }
        }
        return in;
    }
    friend ostream& operator << (ostream &out, Graph<T,E> &G){
        int i, j, n, m;
        T e1, e2;
        E weight;
        n = G.NumberOfVertices();
        m = G.NumberOfEdges();
        out << "Number of Vertices: " << n << endl;
        out << "Number of Edges: " << m << endl;
        out << "The edges in the graph are:\n";
        for ( i = 0 ; i < n ; i ++ ){
            for ( j = i + 1 ; j < n ; j ++ ) {
                weight = G.getWeight(i, j);
                if ( weight > 0 && weight < maxWeight ) {
                    e1 = G.getValue(i);
                    e2 = G.getValue(j);
                    out << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
                }
            }
        }
        return out;
    }

protected:
    int maxVertices;
    int numEdges;
    int numVertices;
    void DFS(int v, bool visited[]);
    void DFSTree(int v, bool visited[], TreeNode<T> *& subTree);
};


template<typename T, typename E>
void Graph<T, E>::DFS() {
    //从顶点v出发,对图G进行深度优先遍历的主过程
    int i, n = NumberOfVertices();                  //取图中顶点个数
    bool *visited = new bool[n];                    //创建辅助数组
    for ( i = 0 ; i < n ; i ++ )
        visited[i] = false;                         //辅助数组visited初始化
    for ( i = 0 ; i < n ; i ++ ) {
        if ( ! visited[i] ) {
            DFS(i, visited);
            cout << endl;
        }
    }
    delete []visited;
}

template<typename T, typename E>
void Graph<T, E>::DFS(int v, bool *visited) {
    cout << getValue(v) << ' ';
    visited[v] = true;
    int w = getFirstNeighbor(v);
    while ( w != -1 ) {
        if ( ! visited[w] )
            DFS(w, visited);
        w = getNextNeighbor(v, w);
    }
}

template<typename T, typename E>
void Graph<T, E>::DFSTree(Tree<T> &tree) {
    //从图的第一个顶点出发,深度优先遍历图,
    //建立以左子女-有兄弟链表表示的DFS生成森林
    TreeNode<T> *p, *q;
    int v, n = NumberOfVertices();                  //取图中顶点个数
    bool *visited = new bool[n];                    //创建辅助数组
    for ( v = 0 ; v < n ; v ++ )
        visited[v] = false;                         //辅助数组visited初始化
    for ( v = 0 ; v < n ; v ++ ) {                  //从每个顶点开始,各做一次遍历
        if ( ! visited[v] ) {                       //已访问的顶点不会作为新起点.输出了所有连通分量,不会重复
            p = new TreeNode<T>(getValue(v));
            if ( ! tree.getRoot() )
                tree.setRoot(p);
            else
                q->nextSibling = p;
            q = p;
            DFSTree(v, visited, p);                 //从顶点0开始深度优先搜索
        }
    }
    delete []visited;                               //释放visited
}

template<typename T, typename E>
void Graph<T, E>::DFSTree(int v, bool visited[], TreeNode<T> *&subTree) {
    //从图的顶点v出发,以深度优先次序遍历图,建立以subTree为根的生成树;
    //根节点subTree已在上层算法中创建
    //算法中用到一个辅助数组visited,对已访问过的顶点作访问标记
    bool first = true;
    visited[v] = true;
    TreeNode<T> *p, *q;
    int w = getFirstNeighbor(v);                    //找顶点v的第一个邻接顶点w
    while ( w != -1 ) {                             //若邻接顶点w存在
        if ( ! visited[w] ) {                       //未访问过
            p = new TreeNode<T>(getValue(w));
            if ( first ) {
                subTree->firstChild = p;            //第一个邻接顶点作为左长子女
                first = false;
            }
            else
                q->nextSibling = p;                 //其余邻接顶点作为右兄弟
            q = p;
            DFSTree(w, visited, q);
        }
        w = getNextNeighbor(v, w);                  //取v排在w后的下一个邻接顶点
    }
}


template<typename T, typename E>
void Graph<T, E>::BFS() {
    int i, v, w, n = NumberOfVertices();
    bool *visited = new bool[n];
    for ( i = 0; i < n ; i ++ )
        visited[i] = false;
    SeqQueue<int> Q;
    for ( i = 0; i < n ; i ++ ) {
        if ( visited[i] )
            continue;
        cout << getValue(i) << ' ';
        visited[i] = true;
        Q.EnQueue(i);
        while ( ! Q.IsEmpty() ) {
            Q.DeQueue(v);
            w = getFirstNeighbor(v);
            while ( w != -1 ) {
                if ( ! visited[w] ) {
                    cout << getValue(i) << ' ';
                    visited[w] = true;
                    Q.EnQueue(w);
                }
                w = getNextNeighbor(v, w);
            }
        }
        cout << endl;
    }
    delete []visited;
}

template<typename T, typename E>
void Graph<T, E>::Components() {
    int i, n = NumberOfVertices();                      //取图中顶点个数
    bool *visited = new bool[n];
    for ( i = 0; i < n ; i ++ )
        visited[i] = false;                             //初始化,表示所有顶点未访问过
    int j = 1;
    for ( i = 0; i < n ; i ++ ) {                       //顺序扫描所有顶点
        if ( ! visited[i] ) {                           //若没有访问过,则访问这个连通分量
            cout << "Component " << j << ":" << endl;
            DFS(i, visited);                            //未访问,出发访问
            j ++;
            cout << endl;
        }
    }
    delete []visited;
}

template<typename T, typename E>
void Graph<T, E>::Kruskal(MinSpanTree<T, E> &MST) {
    //求最小生成树
    MSTEdgeNode<T,E> ed;                                //边结点辅助单元
    int u, v, count;
    int n = NumberOfVertices();                         //顶点数
    int m = NumberOfEdges();                            //边数
    MinHeap<E,MSTEdgeNode<T,E>> H(m);                   //最小堆,关键码类型为E
    UFSets F(n);
    for ( u = 0 ; u < n ; u ++ ) {
        for ( v = u + 1 ; v < n ; v ++ ) {
            if ( getWeight(u, v) != 0 ) {               //对应边存在
                ed.tail = u;
                ed.head = v;
                ed.key = getWeight(u, v);
                H.Insert(ed);                           //插入堆
            }
        }
    }
    count = 1;                                          //最小生成树加入边数计数
    while ( count < n ) {                               //反复执行,取n-1条边
        H.RemoveMin(ed);                                //从最小堆中退出具最小权值的边ed
        u = F.Find(ed.tail);
        v = F.Find(ed.head);                            //取两顶点所在集合的根u与v
        if ( u != v ) {                                 //不是同一集合,说明不连通
            F.SimpleUnion(u, v);                        //合并,连通他们
            MST.Insert(ed);                             //该边存入最小生成树
            count ++;
        }
    }
}

template<typename T, typename E>
void Graph<T, E>::Prim(MinSpanTree<T, E> &MST) {
    MSTEdgeNode<T,E> ed;                                //边结点辅助单元
    int i, u, v, count;
    int n = NumberOfVertices();                         //顶点数
    int m = NumberOfEdges();                            //边数
    u = 0;
    MinHeap<E,MSTEdgeNode<T,E>> H(m);                   //最小堆
    bool *Vmst = new bool[n];                           //最小生成树顶点集合
    for ( i = 0; i < n ; i ++ )
        Vmst[i] = false;
    Vmst[u] = true;                                     //u加入生成树
    count = 1;
    do {                                                //迭代
        v = getFirstNeighbor(u);
        while ( v != -1 ) {                             //检测u所有邻接顶点
            if ( ! Vmst[v] ) {                          //v不在mst中
                ed.tail = u;
                ed.head = v;
                ed.key = getWeight(u, v);
                H.Insert(ed);                           //(u,v)加入堆
            }                                           //堆中存所有 u在mst中, v不在mst中 的边
            v = getNextNeighbor(u, v);
        }
        while ( ! H.IsEmpty() && count < n ) {
            H.RemoveMin(ed);                            //选堆中具最小权的边
            if ( ! Vmst[ed.head] ) {
                MST.Insert(ed);                         //加入最小生成树
                u = ed.head;
                Vmst[u] = true;                         //u加入生成树顶点集合
                count ++;
                break;
            }
        }
    } while ( count < n );
}


#endif //DATASTRUCTURE_GRAPH_H

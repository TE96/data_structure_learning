//
// Created by fuwuchen on 18-10-14.
//

#ifndef DATASTRUCTURE_TREE_H
#define DATASTRUCTURE_TREE_H

#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

//树的子女-兄弟表示的类定义
template<typename T>
struct TreeNode {
    T data;
    TreeNode<T> *firstChild, *nextSibling;
    TreeNode(T value = 0, TreeNode<T> *fc = NULL, TreeNode<T> *ns = NULL)
        : data(value), firstChild(fc), nextSibling(ns) {}
};

template<typename T>
class Tree {
    //对象:树是由n(>=0)个结点组成的有限集合.在类界面中的position是树中结点的地址
    //在顺序存储方式下是下标型,在链表存储方式下是指针型.T是树结点中存放数据的类型,要
    //求所有结点的数据类型是一致的
private:
    TreeNode<T> *root, *current;
    bool Find(TreeNode<T> *p, T value);                     //在以p为根的树中搜索value
    void RemovesubTree(TreeNode<T> *p);                     //删除以p为根的子树
    bool FindParent(TreeNode<T> *t, TreeNode<T> *p);
    void PreOrder(ostream& out, TreeNode<T> *p);
    void PostOrder(ostream& out, TreeNode<T> *p);
    void LevelOrder(ostream& out, TreeNode<T> *p);
    void Output(TreeNode<T> *subTree, string str, ostream &out);
    void IntendedText(TreeNode<T> *subTree, string str, ostream &out);
    void ShowTree(TreeNode<T> *t);
    TreeNode<T> CreateTree(T *& GL);
    T RefValue;                                             //数据输入停止标志
public:
    Tree() {
        root = current = NULL;
    }                                                       //构造函数,生成树的结构并初始化
    Tree(T value) {
        root = current = NULL;
        RefValue = value;
    }
//    ~Tree();                                                //析构函数,释放树所占存储
    bool Root();                                            //置根结点为当前结点
    TreeNode<T> *getRoot() {
        return root;
    }
    void setRoot(TreeNode<T> *rt) {
        root = rt;
    }                                                       //建立树的根节点
    bool FirstChild();                                      //将当前结点的第一个子女置为当前结点
    bool NextSibling();                                     //将当前结点的下一个兄弟置为当前结点
    bool Parent();                                          //将当前结点的双亲置为当前结点
    bool Find(T value);
    void PreOrder(void (* visit)(TreeNode<T> *t)) {
        TreeNode<T> *p = root;
        while ( p ) {
            PreOrder(p, visit);
            p = p->nextSibling;
        }
    }
    void PostOrder(void (* visit)(TreeNode<T> *t)) {
        TreeNode<T> *p = root;
        while ( p ) {
            PostOrder(p, visit);
            p = p->nextSibling;
        }
    }
    void LevelOrder(void (* visit)(TreeNode<T> *t)) {
        LevelOrder(root, visit);
    }
    void CreateTree(istream &in = cin) {
        CreateTree(in, root);
    }
    void Output(ostream &out = cout) {                      //树状格式输出
        Output(root, string(), out);
    }
    void IntendedText(ostream &out = cout){                 //将树用缩格文本形式输出
        IntendedText(root, string(), out);                  //string()是构造函数
    }
    void ShowTree(ostream &out = cout){
        ShowTree(root, out);
    }
    void reSetCurrent(){                                    //将current重新指向根节点
        current = root;
    }
    int CountNode(TreeNode<T> *t)const;
    int FindDepth(TreeNode<T> *t)const;
    friend istream& operator >> (istream &in, Tree<T> &tree);
    friend ostream& operator << (ostream &out, Tree<T> &tree);
    bool IsEmpty() {
        return root == NULL;
    }                                        //判树空否.若空则返回true

};

template<typename T>
istream& operator >> (istream &in, Tree<T> &tree){
    tree.CreateTree(in,tree.root);
    return in;
}

template<typename T>
ostream& operator << (ostream &out, Tree<T> &tree){
    tree.IntendedText(out);
    return out;
}

template<typename T>
bool Tree<T>::Root() {
    //让树的根结点成为树的当前结点
    if ( root == NULL ) {
        current = NULL;
        return false;
    }
    else {
        current = root;
        return true;
    }
}

template<typename T>
bool Tree<T>::Parent() {
    //在树中找当前结点的父结点,使之成为当前结点
    TreeNode<T> *p = current;
    if ( current == NULL || current == root ) {
        current = NULL;
        return false;
    }
    return FindParent(root, p);
}

template<typename T>
bool Tree<T>::FindParent(TreeNode<T> *t, TreeNode<T> *p) {
    //在根为*t的树中找*p的父结点,并使之成为当前结点.
    TreeNode<T> *q = t->firstChild;
    while ( q != NULL && q != p ) {                     //循根的长子的兄弟链,搜索
        if ( FindParent(q, p) ) {
            return true;
        }
        q = q->nextSibling;
    }
    if ( q != NULL && q == p ) {
        current = t;
        return true;
    }
    else {
        current = NULL;
        return false;
    }
}

template<typename T>
bool Tree<T>::FirstChild() {
    //在树中找当前结点的长子,并使之成为当前结点.
    if ( current && current->firstChild ) {
        current = current->firstChild;
        return true;
    }
    current = NULL;
    return false;
}

template<typename T>
bool Tree<T>::NextSibling() {
    //在树中找当前结点的兄弟,并使之成为当前结点.
    if ( current && current->nextSibling ) {
        current = current->nextSibling;
        return true;
    }
    current = NULL;
    return false;
}

template<typename T>
bool Tree<T>::Find(T value) {
    if ( IsEmpty() )
        return false;
    return Find(root, value);
}

template<typename T>
bool Tree<T>::Find(TreeNode<T> *p, T value) {
    //在根为*p的树中找值为value的结点,找到后该结点成为当前结点,否则当前结点不变
    //函数返回成功表示:=true,成功;=false,失败
    bool result = false;
    if ( p->data == value ) {
        result = true;
        current = p;
    }
    else {                                                  //搜索失败
        TreeNode<T> *q = p->firstChild;
        while ( q != NULL && !(result = Find(q, value)) )
            q = q->nextSibling;
    }
    return result;
}

template<typename T>
void Tree<T>::RemovesubTree(TreeNode<T> *p) {

}

template<typename T>
void Tree<T>::IntendedText(TreeNode<T> *subTree, string str, ostream &out) {

}

template<typename T>
void Tree<T>::Output(TreeNode<T> *subTree, string str, ostream &out) {

}

template<typename T>
void Tree<T>::ShowTree(TreeNode<T> *t) {
    //将二叉树转换为广义表,输出广义表
    if ( t == NULL )
        return;
    cout << '(';
    cout << t->data;
    for ( TreeNode<T> *p = t->firstChild ; p != NULL ; p = p->nextSibling )
        ShowTree(p);
    cout << ')';
}

template<typename T>
TreeNode<T> Tree<T>::CreateTree(T *& GL) {
    //利用广义表构造树,在扫描广义表的同时,利用树的先根遍历构造子女-兄弟链表
    if ( *GL == '\0' )
        return NULL;
    if ( *(GL) == ')' ) {
        GL++;
        return NULL;
    }
    if ( *(GL) == '(' )
        GL++;
    TreeNode<T> *t = new TreeNode<T>( * (GL++) );
    t->firstChild = CreateTree(GL);
    t->nextSibling = CreateTree(GL);
}

template<typename T>
void Tree<T>::PreOrder(ostream &out, TreeNode<T> *p) {
    //先根次序遍历并输出以*p为根的树
    if ( p != NULL ) {
        out << p->data;
        for ( p = p->firstChild ; p != NULL; p = p->nextSibling )
            PreOrder(out, p);
    }
}

template<typename T>
void Tree<T>::PostOrder(ostream &out, TreeNode<T> *p) {
    //以指针p为根,按后根次序遍历树
    if ( p != NULL ) {
        TreeNode<T> *q;
        for ( q = p->firstChild ; q != NULL ; q = q->nextSibling )
            PostOrder(out, q);
        out << p->data;
    }
}

template<typename T>
void Tree<T>::LevelOrder(ostream &out, TreeNode<T> *p) {
    //按广度优先次序(层次次序)分层遍历树,树的根节点是*p.算法中用到一个队列
    Queue<TreeNode<T> *> Q;
    if ( p != NULL ) {
        Q.EnQueue(p);
        while ( !Q.IsEmpty() ) {
            Q.DeQueue(p);
            out << p->data;
            for ( p = p->firstChild ; p != NULL ; p = p->nextSibling )
                Q.EnQueue(p);
        }
    }
}

template<typename T>
int Tree<T>::CountNode(TreeNode<T> *t) const {
    //求树的结点数
    if ( t == NULL )
        return 0;
    int count = 1;
    count += CountNode(t->firstChild);
    count += CountNode(t->nextSibling);
    return count;
}

template<typename T>
int Tree<T>::FindDepth(TreeNode<T> *t) const {
    //利用后根遍历求树的深度
    if ( t == NULL )
        return 0;
    int fcDepth = FindDepth(t->firstChild) + 1;
    int nsDepth = FindDepth(t->nextSibling);
    return (fcDepth > nsDepth) ? fcDepth : nsDepth;
}

#endif //DATASTRUCTURE_TREE_H

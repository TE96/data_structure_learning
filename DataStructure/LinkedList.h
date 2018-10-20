//
// Created by fuwuchen on 18-10-10.
//

#ifndef DATASTRUCTURE_LINKEDLIST_H
#define DATASTRUCTURE_LINKEDLIST_H

#include <iostream>
#include <cassert>
using namespace std;

#ifndef INSMOD_INF_INR
#define INSMOD_INF_INR
enum InsMod {INF, INR};//定义向前还是向后生成
#endif

template <typename T>
struct LinkNode {                           //链表节点类的定义
    T data;                                 //数据域
    LinkNode<T> *link;                      //链指针域

    LinkNode(LinkNode<T> *ptr = NULL) {     //仅初始化指针成员的构造函数
        link = ptr;
    }
    LinkNode(const T &item, LinkNode<T> *ptr = NULL) {  //初始化数据与指针成员的构造函数
        data = item;
        link = ptr;
    }
};

template <typename T>
class List {
    //链表类,直接使用链表结点类的数据和操作
protected:
    LinkNode<T> *first;
    void inputFront(T endTag);
    void inputRear(T endTag);

public:
    //链表操作
    List() {                                            //构造函数
        first = new LinkNode<T>;
    };
    List(const T &x) {                                  //构造函数
        first = new LinkNode<T>(x);
    }
    List(List<T> &L);                                   //复制构造函数
    ~List() {                                           //析构函数
        makeEmpty();
        delete first;
    }
    void makeEmpty();                                   //将链表置为空表
    int Length()const;                                  //计算链表的长度
    LinkNode<T> *getHead()const {                       //返回附加头结点地址
        return first;
    }
    void setHead(LinkNode<T> *p) {                      //设置附加头结点地址
        first = p;
    }
    LinkNode<T> *Search(T &x);                          //搜索含数据x的元素
    LinkNode<T> *Locate(int i);                         //搜索第i个元素的地址
    T *getData(int i);                                  //取出第i个元素的地址
    void setData(int i, T &x);                          //用x修改第i个元素的值
    bool Insert(int i, T &x);                           //在第i个元素后插入x
    bool Remove(int i, T &x);                           //删除第i个元素,x返回该元素的值
    bool IsEmpty()const {                               //判表空否?空则返回true
        return ( first->link = NULL ) ? true : false;
    }
    bool IsFull()const {                                //判表满否?不满则返回false
        return false;
    }
    void Sort();                                        //排序
    void Inverse();
    void input(T endTag, InsMod im = INR);              //输入
    void output();                                      //输出
    List<T> &operator = (List<T> &L);
    friend ostream&operator << (ostream &out, List<T> &L) {
        LinkNode<T> *current = L.first->link;
        while ( current ) {
            out << current->data << '\t';
            current = current->link;
        }
        out << endl;
        return out;
    }
    friend istream&operator >> (istream &in, List<T> &L) {
        LinkNode<T> *newNode, *last;
        T val;
        L.makeEmpty();
        while ( !in.eof() ) {
            in >> val;
            newNode = new LinkNode<T>(val);
            assert(newNode);
            last->link = newNode;
            last = newNode;
        }
        last->link = NULL;
        return in;
    }
};

template <typename T>
List<T>::List(List<T> &L) {
    T value;
    LinkNode<T> *srcptr = L.getHead();                  //被复制表的附加头结点地址
    LinkNode<T> *destptr = first = new LinkNode<T>;
    while ( srcptr->link ) {                            //逐个结点复制
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
}

template <typename T>
void List<T>::makeEmpty() {
    //将链表置为空表
    LinkNode<T> *q;
    while ( first->link != NULL ) {                     //当链不空时,删去链中所有结点
        q = first->link;
        first->link = q->link;                          //保存被删结点,从链上摘下该节点
        delete q;
    }wxz
};

template <typename T>
int List<T>::Length() const {
    LinkNode<T> *p = first->link;
    int count = 0;
    while ( p != NULL ) {                               //循链扫描
        p = p->link;
        count ++;
    }
    return count;
}

template <typename T>
LinkNode<T> *List<T>::Search(T &x) {
    //在表中搜索含数据x的节点,搜索成功时函数返回该节点地址;否则返回NULL值.
    LinkNode<T> *current = first->link;
    while ( current != NULL )
        if ( current->data == x )                       //循链找含x结点
            break;
        else
            current = current->link;
    return current;
}

template <typename T>
LinkNode<T> *List<T>::Locate(int i) {
    //定位函数.返回表中第i个元素的地址.若i<0或i超出表中结点个数,则返回NULL.
    if ( i < 0 )                                        //i不合理
        return NULL;
    LinkNode<T> *current = first;
    int k = 0;
    while ( current != NULL && k < i ) {                //循链找第i个结点
        current = current->link;
        k ++;
    }
    return current;
}

template <typename T>
T *List<T>::getData(int i) {
    //取出链表中第i个元素的值.
    if ( i <= 0 )                                       //i值太小
        return NULL;
    LinkNode<T> *current = Locate(i);
    if ( current == NULL )
        return NULL;                                    //i值太大
    else
        return &current->data;
}

template <typename T>
void List<T>::setData(int i, T &x) {
    //给链表中第i个元素赋值x
    if ( i <= 0 )                                       //i值太小
        return;
    LinkNode<T> *current = Locate(i);
    if ( current == NULL )                              //i值太大
        return;
    else
        current->data = x;
}

template <typename T>
bool List<T>::Insert(int i, T &x) {
    //将新元素x插入在链表中第i个节点之后
    LinkNode<T> *current = Locate(i);
    if ( current == NULL )
        return false;                                   //插入不成功
    LinkNode<T> *newNode = new LinkNode<T>(x);
    if ( newNode == NULL ) {
        cerr << "存储分配错误!" << endl;
        exit(1);
    }
    newNode->link = current->link;                      //链接在current之后
    current->link = newNode;
    return true;                                        //插入成功
}

template <typename T>
bool List<T>::Remove(int i, T &x) {
    //将链表中的第i个元素删去,通过引用型参数x返回该元素的值
    LinkNode<T> *current = Locate(i-1);
    if ( current == NULL || current ->link == NULL )
        return false;                                   //删除不成功
    LinkNode<T> *del = current->link;                   //重新拉链,将被删结点从链中摘下
    current->link = del->link;
    x = del->data;                                      //取出被删结点中的数据值
    delete del;
    return true;
}

template <typename T>
void List<T>::output() {
    //单链表的输出函数:将单链表中所有数据按逻辑顺序输出到屏幕上
    LinkNode<T> *current = first->link;
    while ( current != NULL ) {
        cout << current->data << "->" << endl;
        current = current->link;
    }
}

template <typename T>
List<T>& List<T>::operator=(List<T> &L) {
    //重载函数:赋值操作,形式如 A = B 其中A是调用此操作的List对象,B是参数表中的
    //引用型参数L结合的实参
    T value;
    LinkNode<T> *srcptr = L.getHead();                  //被复制表的附加头结点地址
    LinkNode<T> *destptr = first = new LinkNode<T>;
    while ( *srcptr->link != NULL ) {                   //逐个结点复制
        value = srcptr->link->data;
        destptr->link = new LinkNode<T>(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;                                       //返回操作对象地址
}

template <typename T>
void List<T>::input(T endTag, InsMod im) {
    if ( im == INF )
        inputFront(endTag);
    else
        inputRear(endTag);
}

template <typename T>
void List<T>::inputFront(T endTag) {
    LinkNode<T> *newNode;
    T val;
    cin >> val;
    while ( val != endTag ) {
        newNode = new LinkNode<T>(val);
        if ( !newNode ) {
            cerr << "存储分配错误!" << endl;
            exit(1);
        }
        newNode->link = first->link;
        first->link = newNode;
        cin >> val;
    }
}

template <typename T>
void List<T>::inputRear(T endTag) {
    LinkNode<T> *newNode, *last=first;
    T val;
    cin >> val;
    while ( last->link != NULL )
        last = last->link;
    while ( val != endTag ) {
        newNode = new LinkNode<T>(val);
        if ( !newNode ) {
            cerr << "存储分配错误!" << endl;
            exit(1);
        }
        last->link = newNode;
        last = newNode;
        cin >> val;
    }
}

template <typename T>
void List<T>::Sort() {

}

template <typename T>
void List<T>::Inverse() {
    LinkNode<T> *h, *p, *pr;
    h = NULL;
    p = first->link;
    while ( p ) {
        pr = h;
        h = p;
        p = h->link;
        h->link = pr;
    }
    first->link = h;
}
#endif //DATASTRUCTURE_LINKEDLIST_H
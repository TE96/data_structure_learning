//
// Created by fuwuchen on 18-10-17.
//

#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include <iostream>
#include "Stack.h"
#include "BST.h"

using namespace std;

template<typename E, typename K>
struct AVLNode: public BSTNode<E,K> {
    int bf;
    E data;
    AVLNode<E,K> *left, *right;
    AVLNode():left(NULL),right(NULL),bf(0){}
    AVLNode(E d, AVLNode<E,K> *l = NULL, AVLNode<E,K> *r = NULL)
        :data(d),left(l),right(r),bf(0){}
};

template<typename E,typename K>
class AVLTree: public BST<E,K>{
public:
    AVLTree():root(NULL){}
    AVLTree(K Ref): RefValue(Ref), root(NULL){}
    bool Insert(E& el) {
        return Insert(root, el);
    }
    bool Remove(K x, E& el) {
        return Remove(root, x, el);
    }
    friend istream&operator>>(istream& in, AVLTree<E,K>& Tree);
    friend ostream&operator>>(ostream& out, AVLTree<E,K>& Tree);
    void Traverse(AVLNode<E,K> *ptr, ostream& out)const;
    int Height() const;

protected:
    AVLNode<E,K> *root;
    K RefValue;
    AVLNode<E,K> *Search(K x, AVLNode<E,K> *&par)const;
    bool Insert(AVLNode<E,K> *&ptr, E& el);
    bool Remove(AVLNode<E,K> *&ptr, K x, E& el);
    void RotateL(AVLNode<E,K> *&ptr);               //左单旋
    void RotateR(AVLNode<E,K> *&ptr);               //右单旋
    void RotateLR(AVLNode<E,K> *&ptr);              //先左后右双旋
    void RotateRL(AVLNode<E,K> *&ptr);              //先右后左双旋
    int Height(AVLNode<E,K> *ptr)const;             //求高度
};

template<typename E, typename K>
void AVLTree<E, K>::RotateL(AVLNode<E, K> *&ptr) {
    //右子树比左子树高:对以ptr为根的AVL树做左单旋转,旋转后新根在ptr.
    AVLNode<E,K> *subL = ptr;                       //要旋转的结点
    ptr = subL->right;
    subL->right = ptr->left;
    ptr->left = subL;
    ptr->bf = subL->bf = 0;
}

template<typename E, typename K>
void AVLTree<E, K>::RotateR(AVLNode<E, K> *&ptr) {
    AVLNode<E,K> *subR = ptr;
    ptr = subR->right;
    subR->left = ptr->right;
    ptr->right = subR;
    ptr->bf = subR->bf = 0;
}

template<typename E, typename K>
void AVLTree<E, K>::RotateLR(AVLNode<E, K> *&ptr) {
    AVLNode<E,K> *subR = ptr, *subL = subR->left;
    ptr = subL->right;
    subL->right = ptr->left;
    ptr->left = subL;
    if ( ptr->bf <= 0 )
        subL->bf = 0;
    else
        subL->bf = -1;
    subR->left = ptr->right;
    ptr->right = subR;
    if ( ptr->bf == -1 )
        subR->bf = 1;
    else
        subR->bf = 0;
    ptr->bf = 0;
}

template<typename E, typename K>
void AVLTree<E, K>::RotateRL(AVLNode<E, K> *&ptr) {
    AVLNode<E,K> *subL = ptr, *subR = subL->right;
    ptr = subR->right;
    subR->left = ptr->right;
    ptr->right = subR;
    if ( ptr->bf >= 0 )
        subR->bf = 0;
    else
        subR->bf = 1;
    subL->right = ptr->left;
    ptr->left = subL;
    if ( ptr->bf == 1 )
        subL->bf = -1;
    else
        subL->bf = 0;
    ptr->bf = 0;
}

template<typename E, typename K>
bool AVLTree<E, K>::Insert(AVLNode<E, K> *&ptr, E &el) {
    AVLNode<E,K> *pr = NULL, *p = ptr, *q;
    int d;
    Stack<AVLNode<E,K> *> st;

    while ( p != NULL ) {
        if ( el == p->data )
            return false;
        pr = p;
        st.Push(pr);
        if ( el < p->data )
            p = p->left;
        else
            p = p->right;
    }

    p = new AVLNode<E,K>(el);
    if ( p == NULL ) {
        cerr << "Out of Space" << endl;
        exit(1);
    }
    if ( pr == NULL ) {
        ptr = p;
        return true;
    }
    if ( el < pr->data )
        pr->left = p;
    else
        pr->right = p;

    while ( st.IsEmpty() == false ) {
        st.Pop(pr);
        if ( p == pr->left )
            pr->bf--;
        else
            pr->bf++;

        if ( pr->bf == 0 )
            break;
        if ( pr->bf == 1 || pr->bf == -1 )
            p = pr;
        else {
            d = ( pr->bf < 0 ) ? -1 : 1;
            if ( p->bf == d ) {
                if ( d == -1 )
                    RotateR(pr);
                else
                    RotateL(pr);
            }
            else {
                if ( d == -1 )
                    RotateLR(pr);
                else
                    RotateRL(pr);
            }
            break;
        }
    }
    if ( st.IsEmpty() )
        ptr = pr;
    else {
        st.getTop(q);
        if ( q->data > pr->data )
            q->left = pr;
        else
            q->right = pr;
    }
    return true;
}

template<typename E,typename K>
istream &operator>>(istream &in, AVLTree<E, K> &Tree) {
    E item;
    cout << "Construct AVL tree :\n";
    cout << "Input Data (end with " << Tree.RefValue << ")";
    in >> item;
    while ( item.key != Tree.RefValue ) {
        Tree.Insert(item);
        cout << "Input Data (end with " << Tree.RefValue << ")";
        in >> item;
    }
    return in;
}

template<typename E,typename K>
ostream &operator>>(ostream &out, AVLTree<E, K> &Tree) {
    out << "Inorder traversal of AVLTree. \n";
    Tree.Traverse(Tree.root, out);
    out << endl;
    return out;
}

template<typename E, typename K>
void AVLTree<E, K>::Traverse(AVLNode<E, K> *ptr, ostream &out) const {
    if ( ptr != NULL ) {
        Traverse(ptr->left, out);
        out << ptr->data << ' ';
        Traverse(ptr->right, out);
    }
}

template<typename E, typename K>
bool AVLTree<E, K>::Remove(AVLNode<E, K> *&ptr, K x, E &el) {
    AVLNode<E, K> *pr = NULL, *p = ptr, *q, *ppr;
    int d, dd = 0;
    Stack<AVLNode<E, K> *> st;
    while ( p != NULL ) {                           //寻找删除位置
        if ( x == p->data.key )                     //找到等于k的结点,停止搜索
            break;
        pr = p;
        st.Push(pr);                                //否则用栈记忆查找路径
        if ( x < p->data.key )
            p = p->left;
        else
            p = p->right;
    }

    if ( p == NULL )
        return false;
    el = p->data;

    if ( p->left != NULL && p->right != NULL ) {    //被删结点有两个子女
        pr = p;
        st.Push(pr);
        q = p->left;                                //在p左子树找p的直接前驱
        while ( q->right != NULL ) {
            pr = q;
            st.Push(pr);
            q = q->right;
        }
        p->data = q->data;                          //用q的值填补p
        p = q;                                      //被删结点转化为q
    }
    if ( p->left != NULL )                          //被删结点只有一个子女q
        q = p->left;
    else
        q = p->right;
    if ( pr == NULL )                               //被删结点为根结点
        ptr = q;
    else {                                          //被删结点不是根结点
        if ( pr->left == p )
            pr->left = q;                           //链接
        else
            pr->right = q;
        while ( !st.IsEmpty() ) {                       //重新平衡化
            st.Pop(pr);                                 //从栈中退出父结点
            if ( q == NULL )
                pr->bf = 0;
            else {
                if ( pr->right == q )
                    pr->bf--;                               //调整父结点的平衡因子
                else
                    pr->bf++;
            if ( !st.IsEmpty() ) {
                st.getTop(ppr);                         //从栈中取出祖父结点
                dd = ( ppr->left == pr ) ? -1 : 1;      //旋转后与上层链接方向
            }
            else
                dd = 0;                                 //栈空,旋转后不与上层链接
            if ( pr->bf == 1 || pr->bf == -1 )          //|bf|=1
                break;
            if ( pr->bf != 0 ) {                        //|bf|=2
                if ( pr->bf < 0 ) {
                    d = -1;
                    q = pr->left;
                }
                else {
                    d = 1;
                    q = pr->right;                      //用q指示较高的子树
                }
                if ( q->bf == 0 ) {
                    if ( d == -1 ) {
                        RotateR(pr);
                        pr->bf = 1;
                        pr->right->br = -1;             //#改
                    }
                    else {
                        RotateL(pr);
                        pr->bf = -1;
                        pr->left->bf = 1;               //#改
                    }

                    if ( dd == -1 )
                        ppr->left = pr;
                    else if (dd == 1)
                        ppr->right = pr;                    //旋转后新根与上层链接
                    break;
                }
                if ( q->bf == d ) {                     //两结点平衡因子同号
                    if ( d == -1 )
                        RotateR(pr);
                    else
                        RotateL(pr);
                }
                else {                                  //两结点平衡因子反号
                    if ( d == -1 )
                        RotateLR(pr);                   //先左后右双旋转,"<"型
                    else
                        RotateRL(pr);                   //先右后左双旋,">"型
                }
                if ( dd == -1 )
                    ppr->left = pr;
                else if ( dd == 1 )
                    ppr->right = pr;                    //旋转后新根与上层链接
            }
            q = pr;
        }
        if ( st.IsEmpty() )
            ptr = pr;                                   //调整到树的根节点
    }
    delete p;
    return true;
}

#endif //DATASTRUCTURE_AVLTREE_H

#include <iostream>
#include "CircList.h"

#include <cstring>
#include <stdio.h>
#include "Stack.h"
#include "Queue.h"

//约瑟夫问题
template <typename T>
void Josephus(CircList<T>& Js, int n, int m) {
    CircLinkNode<T> *p = Js.getHead(), *pre = NULL;
    int i, j;
    for ( i = 0 ; i < n - 1 ; ++i ) {           //执行n-1次
        for (j = 1; j < m; ++j) {               //数m-1个人
            pre = p;
            p = p->link;
        }
        cout << "出列的人是" << p->data << endl;  //输出
        pre->link = p->link;
        delete p;                               //删去
        p = pre->link;
    }
}

//匹配括号问题
//const  int maxLength = 100;
//void PringMatchedParis(char *expression) {
//    Stack<int> s(maxLength);
//    int j, length = strlen(expression);
//    for ( int i = 1 ; i < length ; ++i) {
//        if ( expression[i-1] == '(' )
//            s.Push(i);
//        else if ( expression[i-1] == ')' ) {
//            if ( s.Pop(j) )
//                cout << j << "与" << i << "匹配" << endl;
//            else
//                cout << "没有与第" << i << "个左括号相匹配的右括号!" << endl;
//        }
//    }
//    while ( !s.IsEmpty() ) {
//        s.Pop(j);
//        cout << "没有与第" << j << "个左括号相匹配的右括号!" << endl;
//    }
//}

//杨辉三角
//void YANGVI(int n) {
//    //分行打印二项式(a+b)^n展开式的系数.在程序中利用了一个队列,咋在输出上一行系数时,
//    //将其下一行的系数预先放入队列中.在各行系数之间插入一个0.
//    Queue<int> q(n+1);
//    int i = 1, j, s = k = 0, t, u;          //计算下一行系数时用到的工作单元
//    q.EnQueue(i); q.EnQueue(i);             //预先放入第1行的两个系数
//    for ( i = 1 ; i <= n ; ++i) {
//        cout << endl;
//        q.EnQueue(k);                       //各行间插入一个0
//        for ( j = 1 ; j <= i + 2 ; ++j) {
//            q.DeQueue(t);                   //读取一个系数
//            u = s + t;
//            q.EnQueue(u);                   //计算下一行系数,并进队列
//            s = t;
//            if ( j != i + 2 )
//                cout << s << ' ' << endl;   //打印一个系数,第i+2个是0
//        }
//    }
//
//}

//汉诺塔问题
void Hanoi(int n, string A, string B, string C) {
    if ( n == 1 )
        cout << "Move top disk from peg " << A << " to peg " << C << endl;
    else {
        Hanoi(n-1, A, C, B);
        cout << "Move top disk from peg " << A << " to peg " << C << endl;
        Hanoi(n-1, B, A, C);
    }
}

int main() {
//    CircList<int> clist;
//    int i, n, m;
//    cout << "输入游戏者人数和报数间隔:";
//    cin >> n >> m;
//    for ( i = 1 ; i <= n ; i ++ )
//        clist.insert(i);                        //形成约瑟夫环
//    Josephus(clist, n, m);
//    return 0;
    Hanoi(3, "A", "B", "C");
}
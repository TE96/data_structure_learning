//
// Created by fuwuchen on 18-10-12.
//

#ifndef DATASTRUCTURE_CALCULATOR_H
#define DATASTRUCTURE_CALCULATOR_H

#include <math.h>
#include <stack>
#include <iostream>
#include "Stack.h"

using namespace std;

class Calculator {
    //模拟一个简单的计算器.次计算器从键盘读入的后缀表达式求职
public:
    Calculator(int sz):s(sz) {}

    void Run();
    void Clear();

private:
    Stack<double> s;                                        //栈对象定义
    void AddOperand(double value);                          //进操作数栈
    bool Get2Operands(double& left, double& right);         //从栈中退出两个操作数
    void DoOperator(char op);                               //形成运算指令,进行计算
};

void Calculator::DoOperator(char op) {
    double left, right, value;
    int result;
    result = Get2Operands(left, right);                     //取两个操作数
    if ( result )
        switch ( op ) {
            case '+': value = left + right; s.Push(value); break;
            case '-': value = left - right; s.Push(value); break;
            case '*': value = left * right; s.Push(value); break;
            case '/':
                if (right != 0.0) {
                    value = left / right;
                    s.Push(value);
                    break;
                } else {
                    cerr << "Divided by 0!" << endl;
                    Clear();
                }
    }
    else Clear();
}

bool Calculator::Get2Operands(double &left, double &right) {
    //私有函数:从操作数栈中取出两个操作数.
    if ( s.IsEmpty() ) {
        std::cerr << "缺少右操作数!" << std::endl;
        return false;
    }
    s.Pop(right);
    if ( s.IsEmpty() ) {
        std::cerr << "缺少左操作数!" << std::endl;
        return false;
    }
    s.Pop(left);
    return true;
}

void Calculator::AddOperand(double value) {
    //私有函数:将操作数的值value进操作数栈
    s.Push(value);
}

void Calculator::Run() {
    //读字符串并求一个后缀表达式的值.以'#'结束
    char ch;
    double newOperand;
    while ( cin >> ch, ch!='#' ) {
        switch ( ch ) {
        case '+': case '-': case '*': case '/':
            DoOperator(ch);break;
        default: cin.putback(ch);
            cin >> newOperand;
            AddOperand(newOperand);
        }
    }
}

void Calculator::Clear() {
    s.MakeEmpty();
}


#endif //DATASTRUCTURE_CALCULATOR_H

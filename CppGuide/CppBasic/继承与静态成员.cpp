#include <iostream>
using namespace std;
 
class A {
public:
    static int num1;
    static int num2;
};

/* 静态数据成员只能在类外进行初始化 */
int A::num1 = 1;
int A::num2 = 5;
class B : public A {
public:
    static int num1; // 同名隐藏
};

/* 静态数据成员只能在类外进行初始化 */
int B::num1 = 2;

int main() {
    A::num1 = 3;
    B::num1 = 4; // 同名隐藏
    cout << "A::num1 = " << A::num1 << endl; // 输出 3
    cout << "B::num1 = " << B::num1 << endl; // 输出 4
    
    A::num2 = 6;
    B::num2 = 7; // 子类可以直接使用父类的静态成员变量
    cout << "A::num2 = " << A::num2 << endl; // 输出 6
    cout << "B::num2 = " << B::num2 << endl; // 输出 7
    return 0;
}
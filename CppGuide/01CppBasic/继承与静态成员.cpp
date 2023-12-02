#include <iostream>
using namespace std;
 
class A {
public:
    static int num;
};

/* 静态数据成员只能在类外进行初始化 */
int A::num = 1;
 
class B : public A {
public:
    static int num;
};

/* 静态数据成员只能在类外进行初始化 */
int B::num = 2;

int main() {
    A::num = 3;
    B::num = 4;
    cout << "A::num = " << A::num << endl;//3
    cout << "B::num = " << B::num << endl;//3
 
    return 0;
}
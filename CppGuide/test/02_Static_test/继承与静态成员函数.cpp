#include <iostream>
using namespace std;
 
class A 
{
public:
    static int num;
    static void print() 
    {
        cout << "A::num = " << num << endl;
    }
};
 
int A::num = 1;
 
class B : public A {
public:
    static int num;// 同名隐藏
 
    static void print() // 同名隐藏
    {
        A::print();// 使用基类中的同名函数
        cout << "B::num = " << num << endl;
    }
};
 
int B::num = 5;
 
int main() 
{
    A::print();// 打印 A::num = 1
    B::print();// 打印 A::num = 1 B::num = 5
    return 0;
}
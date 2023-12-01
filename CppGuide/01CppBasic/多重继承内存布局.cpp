#include <bits/stdc++.h>
using namespace std;

class Chair
{
    int value;
public:
    Chair(int x = 0) : value(x) { }
    ~Chair(){}
    void fun(){ cout << "Chair::fun" << endl; }
};

class Bed
{
    int num;
public:
    Bed(int x = 0) : num(x) { }
    ~Bed() { }
    void fun(){ cout << "Bed::fun" << endl; }
};

class DeckChair : public Bed, public Chair
{
    int sum;
public:
    DeckChair(int x = 0) : Chair(x), Bed(x + 1), sum(x + 2) {}
    ~DeckChair() {}
};

/* 菱形继承 */


/* 虚函数与多态 */
class Object
{
public:
    virtual void fun() {}
    virtual int add(int a, int b) { return 0; }
};

class Base : public Object
{
public:
    
};

int main()
{
    // DeckChair dc(10);
    // Bed *bp = static_cast<Bed*> (&dc);
    // Chair *cp = static_cast<Chair*> (&dc);
    // // dc.fun(); // 报错：不明确调用哪个基类中的 fun 方法，则产生二义性
    // // 解决方法：在调用时，使用作用域解析符进行限定
    // dc.Bed::fun();
    // dc.Chair::fun();
    // bp->fun();
    // cp->fun();
    // Bed *bp = &dc;
    // Chair *cp = &dc;
    // cout << "Bed address : " << &bp << endl;
    // cout << "Chair address : " << &cp << endl;
    // 在多重继承时，只能把派生类对象给到基类对象，或者把派生类对象地址给基类对象指针，反之是不行的
    // Bed *bp = static_cast<Bed*> (&dc);
    // Chair *cp = static_cast<Chair*> (&dc);

    // DeckChair *dp = &dc;
    // dp = static_cast<DeckChair*> (bp);  // error: 基类地址不能给派生类对象指针
    // dp = static_cast<DeckChair*> (cp);  // error: 基类地址不能给派生类对象指针
    return 0;
}
#include <iostream>
using namespace std;

class Bed
{
    int num;
public:
    Bed(int x = 0) : num(x) {}
    void fun() { cout << "Bed::fun" << endl; }
    ~Bed() {}
};

class Chair
{
    int value;
public:
    Chair(int x = 0) : value(x) {}
    void fun(){ cout << "Chair::fun" << endl; }
    ~Chair() {}
};

class DeckChair : public Bed, public Chair
{
    int sum;
public:
    DeckChair(int x = 0): Chair(x + 1), Bed(x + 2), sum(x + 2){}
    ~DeckChair() {}
};

int main()
{
    DeckChair dc(10);
    // dc.fun();// 不明确用哪个基类中的 fun 方法，则产生二义性报错
    Bed *bp = static_cast<Bed*> (&dc);
    Chair *cp = static_cast<Chair*>(&dc);

    // 派生类在调用时，使用作用域解析符来进行限定，从而避免二义性
    dc.Bed::fun();
    dc.Chair::fun();

    bp->fun();
    cp->fun();
    return 0;
}
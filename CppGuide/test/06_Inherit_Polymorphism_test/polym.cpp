#include <iostream>
#include <stdlib.h>
using namespace std;

class CA
{
public:
    void f()
    {
        cout << "CA f()" << endl;
    }
    virtual void ff()       // 虚函数
    {
        cout << "CA ff()" << endl;
        f();
    }
};

class CB : public CA
{
public :
    virtual void f()    // 虚函数
    {
        cout << "CB f()" << endl;
    }
    void ff()
    {
        cout << "CB ff()" << endl;
        f(); // 同名隐藏，调用自身的 f() 函数
        CA::ff();
    }
};

class CC : public CB
{
public:
    virtual void f()    // 虚函数
    {
        cout << "C f()" << endl;
    }
};

int main()
{
    CB b; // 
    CA *ap = &b; // ap 指向 CB
    CC c;
    CB &br = c; // br 绑定 CC
    CB *bp = &c; // bp 指向 CC

    ap->f();    // 非虚函数，编译时就绑定了，调用基类的同名函数 CA F()
    cout << endl;

    b.f();      // 虚函数，调用自身的函数 CB f()
    cout << endl;

    br.f();     // 虚函数，调用子类的函数 C f()
    cout << endl;

    bp->f();    // 虚函数，调用子类的函数 C f()
    cout << endl;

    ap->ff();   // CB ff(); CB f(); CA ff(); CA f()
    cout << endl;

    bp->ff();   // CB ff(); C f(); CA ff(); CA f()
    cout << endl;

    return 0;
}
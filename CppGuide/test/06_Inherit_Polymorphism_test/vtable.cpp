#include <iostream>

using namespace std;

class A {
public:
    A() : m_data1(0), m_data2(0) {}

    virtual void vfunc1() { cout << "A::vfunc1" << endl; };

    virtual void vfunc2() { cout << "A::vfunc2" << endl; };

    void func1() { cout << "A::func1" << endl; };

    void func2() { cout << "A::func2" << endl; };
private:
    int m_data1, m_data2;
};

class B : public A {
public:
    B() : A(), m_data3(0) {}

    virtual void vfunc1() { cout << "B::vfunc1" << endl; };

    void func1() { cout << "B::func1" << endl; };
private:
    int m_data3;
};

class C : public B {
public:
    C() : B(), m_data1(0), m_data4(0) {}

    virtual void vfunc2() { cout << "C::vfunc2" << endl; };

    void func2() { cout << "C::func2" << endl; };
private:
    int m_data1, m_data4;
};


int main() {
    B bObject;
    A *p = &bObject;
    p->vfunc1();

    cout << "**************" << endl;

    A aObject = (A) bObject;
    aObject.vfunc1();

    cout << "**************" << endl;

    C cObject;
    p = &cObject;
    p->vfunc1();
    p->vfunc2();

    cout << "**************" << endl;

    bObject.func1();
    bObject.func2();
    bObject.A::func1();
    cObject.A::func1();
    cObject.func2();

    return 0;
}
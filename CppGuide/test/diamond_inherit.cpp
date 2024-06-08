#include<iostream>
using namespace std;
 
class A
{
public:
    int num;
};
 
class B : public A
{
public:
    int b;
};
 
class C : public A
{
public:
    int c;
};
 
class D : public B, public C
{
public:
    int d;
};
 
int main()
{
    D di;
    cout << sizeof(di) << endl;
    di.B::num = 1;
    di.C::num = 2;
    di.b = 3;
    di.c = 4;
    di.d = 5;
    return 0;
}
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
    static int num;
 
    static void print() 
    {
        A::print();
        cout << "B::num = " << num << endl;
    }
};
 
int B::num = 5;
 
int main() 
{
    A::print();
    B::print();
    return 0;
}
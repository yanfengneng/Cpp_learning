#include <iostream>
using namespace std;

class Base
{
public:
   Base(){cout << "Base constructor" << endl;}
   ~Base(){cout << "Base destructor" << endl;}
};

class Persion1: public Base
{
public:
   Persion1(){cout << "Persion1 constructor" << endl;}
   ~Persion1(){cout << "Persion1 destructor" << endl;}
};

class Persion2: public Persion1
{
public:
   Persion2(){cout << "Persion2 constructor" << endl;}
   ~Persion2(){cout << "Persion2 destructor" << endl;}
};

int main()
{
   Persion2 test;
   return 0;
}
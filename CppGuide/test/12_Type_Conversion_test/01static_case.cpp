#include <iostream>
using namespace std;

// 基类（父类）
class CBase {
 public:
  CBase() { cout << "CBase construct." << endl; }
  ~CBase() { cout << "CBase disconstruct." << endl; }
};

// 派生类(子类)
class CDerived : public CBase {
  public:
  CDerived() { cout << "CDerived construct." << endl; }
  ~CDerived() { cout << "CDerived disconstruct." << endl; }
};

int main() {
  // 1. 使用 static_cast 在基本数据类型之间进行转换
  float fval = 10.12;
  int ival = static_cast<int>(fval);  // float => int
  cout << ival << endl;               // output: 10

  // 2. 使用 static_cast 来有类型指针与 void * 之间转换
  int *intp = &ival;
  void *voidp = static_cast<void *>(intp);
  // cout << *voidp << endl; // 报错：void*
  // 的大小未知，不是一个指向对象的指针类型 由于 long 为 64
  // 位长整数，因此这里的转换会导致 *longp 被初始化为 long
  // 的最大值，因此不能这样进行转换 long *longp = static_cast<long *>(voidp);
  // cout << *longp << endl;

  unsigned *unsignedp = static_cast<unsigned *>(voidp);
  cout << *unsignedp << endl;  // output: 10

  // 3. 用于类层次结构中基类与派生类之间指针或引用的转换
  // 3.1 上行转换：派生类 => 基类 是安全的
  CDerived *d1 = nullptr;
  CBase *b1 = static_cast<CBase *>(d1);  // 派生类转换为基类

  // 3.2 下行转换：基类 => 派生类，由于没有动态类型转换，所以是不安全的
  CBase *b2 = nullptr;
  CDerived *d2 = static_cast<CDerived*>(b2);

  // 4. 不能使用 static_cast 来有类型指针（非 void *）之间进行转换
  float *floatp = &fval;
  // int *intp1 = static_cast<int *>(floatp);
  // cout << *intp1 << endl;
  cout << *floatp << endl;
  return 0;
}

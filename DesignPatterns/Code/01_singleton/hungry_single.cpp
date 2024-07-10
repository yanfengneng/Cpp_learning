#include <iostream>
#include <mutex>
#include <memory>

class Singleton {
 public:
  // 获取单实例
  static Singleton *GetInstance();

  // 释放单实例，进程退出时调用
  static void deleteInstance();

  // 打印实例地址
  void Print();

 private:
  // 将其构造和析构成为私有的, 禁止外部构造和析构
  Singleton();
  ~Singleton();

  // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
  Singleton(const Singleton &signal);
  const Singleton &operator=(const Singleton &signal);

 private:
  // 唯一单实例对象指针
  static Singleton *g_pSingleton;
};

int main() { 
  auto s = Singleton::GetInstance();
  s->Print();
  s->deleteInstance();
  return 0; 
}

// 代码一运行就初始化创建实例 ，本身就线程安全
// 使用 std::nothrow 申请内存时，申请失败的话，指针为空，这样有助于 Test-for-NULL 检查
Singleton *Singleton::g_pSingleton = new (std::nothrow) Singleton();

Singleton *Singleton::GetInstance() { return g_pSingleton; }

void Singleton::deleteInstance() {
  if (g_pSingleton) {
    delete g_pSingleton;
    g_pSingleton = nullptr;
  }
}

void Singleton::Print() {
  std::cout << "我的实例内存地址是:" << this << std::endl;
}

Singleton::Singleton() { std::cout << "构造函数" << std::endl; }

Singleton::~Singleton() { std::cout << "析构函数" << std::endl; }

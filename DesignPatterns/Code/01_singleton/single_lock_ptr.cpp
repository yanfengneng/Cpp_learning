#include <iostream>
#include <mutex>
using namespace std;

/* 加锁的懒汉式实现 */
class SingleInstance {
 public:
  // 获取单实例对象
  static SingleInstance *GetInstance();

  // 释放单实例，进程退出时调用
  static void deleteInstance();

  // 打印实例地址
  void Print();

 private:
  // 将其构造和析构成为私有的, 禁止外部构造和析构
  SingleInstance();
  ~SingleInstance();

  // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
  SingleInstance(const SingleInstance &signal) = delete;
  const SingleInstance &operator=(const SingleInstance &signal) = delete;

 private:
  // 唯一单实例对象指针
  static SingleInstance *m_SingleInstance;
  static std::mutex m_Mutex;
};

int main() {
  // 获取单例对象并使用
  SingleInstance *singleton = SingleInstance::GetInstance();
  singleton->Print();
  singleton->deleteInstance();
  return 0;
}

// 初始化静态成员变量
// 静态成员变量只能在类外进行初始化
SingleInstance *SingleInstance::m_SingleInstance = nullptr;
std::mutex SingleInstance::m_Mutex;

// 注意：不能返回指针的引用，否则存在外部被修改的风险！
SingleInstance *SingleInstance::GetInstance() {
  // 这里使用了两个 if
  // 判断语句的技术称为双检锁；好处是，只有判断指针为空的时候才加锁，
  // 避免每次调用 GetInstance() 的方法都加锁，锁的开销毕竟还是有点大的。
  // 若实例已存在，则直接返回，无需进入锁定区域
  if (m_SingleInstance == nullptr) {
    std::unique_lock<std::mutex> lock(m_Mutex);  // 加锁
    /*
      第二次检查（加锁后）是为了确保即使多个线程同时通过了第一次的nullptr检查，
      在实例化对象前，只有一个线程能够创建实例。这是因为第一次检查后，
      多个线程可能同时尝试获取锁来创建实例。加锁之后的第二次检查确保了即使多个线程等待锁，
      只有第一个获取锁的线程进入此区域并判断实例是否已创建，防止多次实例化。
    */
    // 获得锁的线程进入此区域后，还是需要判断该实例是否已经创建，来防止多次实例化。
    if (m_SingleInstance == nullptr) { 
      /**
       * singleton 对象在初始化的时候实际上是分三步的：
          1. 先申请一块内存；
          2. 再调用构造函数进行初始化；
          3. 将内存地址赋值给 m_SingleInstance 。
        但是上述操作在不同编译器上表现可能是不一样的，可能先将内存地址赋值给
        m_SingleInstance ，再调用构造函数进行初始化。那在并发场景下，线程拿到的
       m_SingleInstance 可能是还未构造完成的单例对象，在使用时可能出现问题。
       先赋值给 temp 在赋值给 m_SingleInstance
       ，可以保证返回的单例对象一定是初始化完成的。
       */
      volatile auto temp = new (std::nothrow) SingleInstance();
      m_SingleInstance = temp;
    }
  }
  return m_SingleInstance;
}

void SingleInstance::deleteInstance() {
  std::unique_lock<std::mutex> lock(m_Mutex);  // 加锁
  if (m_SingleInstance) {
    delete m_SingleInstance;
    m_SingleInstance = nullptr;
  }
}

void SingleInstance::Print() {
  std::cout << "我的实例内存地址是:" << this << std::endl;
}

SingleInstance::SingleInstance() { std::cout << "构造函数" << std::endl; }

SingleInstance::~SingleInstance() { std::cout << "析构函数" << std::endl; }

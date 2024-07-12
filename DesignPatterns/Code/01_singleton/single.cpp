#include <iostream>

/*内部静态变量的懒汉实现*/
class Single {
 public:
  // 获取单实例对象
  static Single &GetInstance();

  // 打印实例地址
  void Print();

 
 private:
  // 禁止外部构造
  Single();

  // 禁止外部析构
  ~Single();

  // 禁止外部拷贝构造
  Single(const Single &single) = delete;

  // 禁止外部赋值操作
  const Single &operator=(const Single &single) = delete;
};

int main() { 
  Single& s = Single::GetInstance();
  s.Print();

  Single& s2 = Single::GetInstance();
  s2.Print();
  return 0; 
}

Single &Single::GetInstance() {
  /**
   * 局部静态特性的方式实现单实例。
   * 静态局部变量只在当前函数内有效，其他函数无法访问。
   * 静态局部变量只在第一次被调用的时候初始化，也存储在静态存储区(全局数据区)，生命周期从第一次被初始化起至程序结束止。
   */
  static Single single;
  return single;
}

void Single::Print() {
  std::cout << "我的实例内存地址是:" << this << std::endl;
}

Single::Single() { std::cout << "构造函数" << std::endl; }

Single::~Single() { std::cout << "析构函数" << std::endl; }
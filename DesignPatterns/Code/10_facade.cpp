#include <iostream>

// 子系统类
class Compiler {
 public:
  void compile() { std::cout << "Compiling source code...\n"; }
};

class Linker {
 public:
  void link() { std::cout << "Linking object files...\n"; }
};

// 外观类
class BuildFacade {
 private:
  Compiler compiler_;
  Linker linker_;

 public:
  void build() {
    compiler_.compile();
    linker_.link();
    std::cout << "Build completed!\n";
  }
};

// 使用
int main() {
  BuildFacade facade;
  facade.build();  // 依次输出编译、链接完成提示
  return 0;
}

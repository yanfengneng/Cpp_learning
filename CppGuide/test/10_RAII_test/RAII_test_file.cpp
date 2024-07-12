#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/* FileRAII 封装了文件句柄管理的逻辑 */
class FileRAII {
 public:
  /* 构造函数打开指定的文件，并在构造过程中获得文件句柄 */
  FileRAII(const std::string& filename) : file(filename) {
    file.open(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file: " + filename);
    }
    std::cout << "File opened: " << filename << std::endl;
  }

  /* 析构函数在对象销毁时自动调用，关闭文件句柄，确保文件资源被释放 */
  ~FileRAII() {
    if (file.is_open()) {
      file.close();
      std::cout << "File closed." << std::endl;
    }
  }

  /* 用于向文件写入内容，通过文件句柄 file 来实现 */
  void write(const std::string& text) {
    if (file.is_open()) {
      file << text;
    }
  }

 private:
  std::ofstream file;
};

int main() {
  try {
    FileRAII file("example.txt");
    file.write("Hello, RAII!");
    // 当 file 对象离开作用域时，即使在异常情况下，也会自动调用 FileRAII
    // 的析构函数，关闭文件句柄，确保文件资源的正确释放。 file will be
    // automatically closed when leaving scope
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

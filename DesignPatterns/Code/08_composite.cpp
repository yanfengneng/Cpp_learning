#include <iostream>
#include <vector>

class FileSystemComponent {
 public:
  virtual void display() = 0;
  virtual void add(FileSystemComponent* item) {}
};

// 文件节点
class File : public FileSystemComponent {
 private:
  std::string name_;

 public:
  File(const std::string& name) : name_(name) {}

  void display() override { std::cout << "File: " << name_ << std::endl; }
};

// 文件夹节点
class Folder : public FileSystemComponent {
 private:
  std::string name_;
  std::vector<FileSystemComponent*> children_;

 public:
  Folder(const std::string& name) : name_(name) {}

  void add(FileSystemComponent* item) override { children_.push_back(item); }

  void display() override {
    std::cout << "Folder: " << name_ << std::endl;
    for (auto& child : children_) {
      child->display();
    }
  }
};

// 使用
int main() {
  Folder root("Root");
  File file1("a.txt");
  Folder sub("Subfolder");
  File file2("b.doc");

  root.add(&file1);
  root.add(&sub);
  sub.add(&file2);

  root.display();
  return 0;
}

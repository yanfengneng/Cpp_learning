#include <iostream>
#include <unordered_map>

// 享元对象
class TextStyle {
 private:
  std::string font_;
  int size_;

 public:
  TextStyle(const std::string& font, int size) : font_(font), size_(size) {}

  void apply(const std::string& text) {
    std::cout << text << " [Font: " << font_ << ", Size: " << size_ << "]\n";
  }
};

// 享元工厂
class TextStyleFactory {
 private:
  std::unordered_map<std::string, TextStyle*> pool_;

 public:
  TextStyle* get_style(const std::string& font, int size) {
    std::string key = font + "_" + std::to_string(size);
    if (pool_.find(key) == pool_.end()) {
      pool_[key] = new TextStyle(font, size);
    }
    return pool_[key];
  }
};

// 使用
int main() {
  TextStyleFactory factory;
  TextStyle* style1 = factory.get_style("Arial", 12);
  TextStyle* style2 = factory.get_style("Arial", 12);  // 复用对象

  style1->apply("Hello");  // Hello [Font: Arial, Size: 12]
  style2->apply("World");  // World [Font: Arial, Size: 12]
  return 0;
}

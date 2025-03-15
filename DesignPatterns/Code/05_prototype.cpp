#include <iostream>
#include <memory>

// 抽象原型接口
class Prototype {
 public:
  virtual ~Prototype() = default;
  virtual std::unique_ptr<Prototype> clone() const = 0;
  virtual void print() const = 0;
};

// 具体原型：文档模板
class DocumentTemplate : public Prototype {
 public:
  DocumentTemplate(const std::string& title, const std::string& content)
      : m_title(title), m_content(content) {}

  std::unique_ptr<Prototype> clone() const override {
    return std::make_unique<DocumentTemplate>(
        *this);  // 深拷贝（假设成员可拷贝）
  }

  void print() const override {
    std::cout << "Title: " << m_title << "\nContent: " << m_content
              << std::endl;
  }

  void setContent(const std::string& content) { m_content = content; }

 private:
  std::string m_title;
  std::string m_content;
};

int main() {
  DocumentTemplate original("Report", "Initial content");
  auto clone = original.clone();

  // 使用 dynamic_cast 将 Prototype 类型转换为 DocumentTemplate 类型
  DocumentTemplate* clonedDoc = dynamic_cast<DocumentTemplate*>(clone.get());
  if (clonedDoc) {
    clonedDoc->setContent("Modified content");
  }
  // clone->setContent("Modified content");

  original.print();  // Output: Title: Report \n Content: Initial content
  clone->print();    // Output: Title: Report \n Content: Modified content

  return 0;
}

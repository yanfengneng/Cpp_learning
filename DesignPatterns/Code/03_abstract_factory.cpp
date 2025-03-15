#include <iostream>

// 抽象按钮
class Button {
 public:
  // 该函数为纯虚函数，要求所有具体的产品类必须实现这个方法
  virtual void render() = 0;
  virtual ~Button() = default;
};

// Windows 按钮
class WinButton : public Button {
 public:
  // 实现纯虚函数 render，输出 Windows Button
  virtual void render() override { std::cout << "Windows Button" << std::endl; }
};

// Mac 按钮
class MacButton : public Button {
 public:
  // 实现纯虚函数 render，输出 Mac Button
  virtual void render() override { std::cout << "Mac Button" << std::endl; }
};

// 抽象文本框
class TextBox {
 public:
  // 该函数为纯虚函数，要求所有具体的产品类必须实现这个方法
  virtual void render() = 0;
  virtual ~TextBox() = default;
};

// Windows 文本框
class WinTextBox : public TextBox {
 public:
  // 实现纯虚函数 render，输出 Windows TextBox
  virtual void render() override {
    std::cout << "Windows TextBox" << std::endl;
  }
};

// Mac 文本框
class MacTextBox : public TextBox {
 public:
  // 实现纯虚函数 render，输出 Mac TextBox
  virtual void render() override { std::cout << "Mac TextBox" << std::endl; }
};

// 抽象工厂
// GUIFactory 是一个抽象工厂类，定义了两个纯虚函数 createButton() 和
// createTextBox()，要求子类实现这些方法以创建具体的 Button 和 TextBox 对象。
class GUIFactory {
 public:
  virtual Button* createButton() = 0;
  virtual TextBox* createTextBox() = 0;
  virtual ~GUIFactory() = default;
};

// WinFactory 和 MacFactory 是 GUIFactory 的具体实现类，分别实现了
// createButton() 和 createTextBox() 方法，创建 WinButton 和 WinTextBox 对象，或
// MacButton 和 MacTextBox 对象。 Windows 工厂
class WinFactory : public GUIFactory {
 public:
  Button* createButton() override { return new WinButton(); }
  TextBox* createTextBox() override { return new WinTextBox(); }
};

// Mac 工厂
class MacFactory : public GUIFactory {
 public:
  Button* createButton() override { return new MacButton(); }
  TextBox* createTextBox() override { return new MacTextBox(); }
};

// 客户端代码
// createUI 函数接受一个 GUIFactory 引用作为参数，使用工厂创建 Button 和 TextBox
// 对象，并调用它们的 render() 方法
void createUI(GUIFactory& factory) {
  Button* button = factory.createButton();
  TextBox* textBox = factory.createTextBox();
  button->render();
  textBox->render();
  delete button;
  delete textBox;
}

int main() {
  GUIFactory* winFactory = new WinFactory();
  createUI(*winFactory);  // Output: Windows Button \n Windows TextBox

  GUIFactory* macFactory = new MacFactory();
  createUI(*macFactory);  // Output: Mac Button \n Mac TextBox

  delete winFactory;
  delete macFactory;
  return 0;
}

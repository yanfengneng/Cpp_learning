- [一、创建型模式](#一创建型模式)
  - [1.1 单例模式（Singleton Pattern）](#11-单例模式singleton-pattern)
  - [1.2 工厂方法模式（Factory Method Pattern）](#12-工厂方法模式factory-method-pattern)
  - [1.3 抽象工厂模式（Abstract Factory Pattern）](#13-抽象工厂模式abstract-factory-pattern)
  - [1.4 建造者模式（Builder Pattern）](#14-建造者模式builder-pattern)
  - [1.5 原型模式（Prototype Pattern）](#15-原型模式prototype-pattern)
  - [1.6 创建型模式总结](#16-创建型模式总结)
- [二、结构型模式](#二结构型模式)
  - [2.1 适配器模式（Adapter Pattern）](#21-适配器模式adapter-pattern)
  - [2.2 桥接模式（Bridge Pattern）](#22-桥接模式bridge-pattern)
  - [2.3 组合模式（Composite Pattern）](#23-组合模式composite-pattern)
  - [2.4 装饰者模式（Decorator Pattern）](#24-装饰者模式decorator-pattern)
  - [2.5 外观模式（Facade Pattern）](#25-外观模式facade-pattern)
  - [2.6 享元模式（Flyweight Pattern）](#26-享元模式flyweight-pattern)
  - [2.7 代理模式（Proxy Pattern）](#27-代理模式proxy-pattern)
  - [2.8 总结](#28-总结)
- [三、行为型模式](#三行为型模式)
  - [3.1 观察者模式（Observer Pattern）](#31-观察者模式observer-pattern)
  - [3.2 命令模式（Command Pattern）](#32-命令模式command-pattern)
  - [3.3 状态模式（State Pattern）](#33-状态模式state-pattern)


> [C++设计模式（全23种）](https://blog.csdn.net/weixin_45712636/article/details/124328504)

常见的设计模型在面试时会考察，因此在这里进行整理下。

1. [单例模式](01单例模式.md)

C++ 中的设计模式是经过验证的通用解决方案，用于解决常见的设计问题。它们通常分为三大类：**创建型**、**结构型**和**行为型**。以下是每种模式的简要总结及其应用。

# 一、创建型模式

创建型模式在设计模式中主要处理**对象的创建**。其主要目的是**解耦对象的创建和使用**，让对象的创建过程更灵活、可扩展，从而提高代码的可维护性和可复用性。

<font color=blue>创建型模式对类的实例化过程进行了抽象，能够将软件模块中**对象的创建和对象的使用进行分离**。</font>为了使软件的结构更加清晰，外界仅需要知道它们的共同接口，而不需要了解其具体实现的细节，从而使整个系统的设计更加符合单一职责原则。

创建型模式**在创建什么（what）、由谁创建（who）、何时创建（when）**等方面都为软件设计者提供了尽可能大的灵活性。创建型模式**隐藏了类的实例的创建细节**，**通过隐藏对象如何被创建和组合在一起**达到整个系统独立的目的。

## 1.1 单例模式（Singleton Pattern）

**描述**：确保某个类只有一个实例，并提供全局访问点。通常用于管理共享资源或全局配置。

**应用场景**：需要全局唯一实例时，例如日志记录类（所有对象都使用同一个日志系统）、数据库连接管理（系统中只有一个数据库连接池）。

**实现**：

```cpp
#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;

    // 私有构造函数
    Singleton() = default;

public:
    // 禁用拷贝和赋值
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);  // 线程安全
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }

    void doSomething() {
        std::cout << "Singleton instance working" << std::endl;
    }
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    std::cout << "s1 == s2? " << (s1 == s2) << std::endl;  // Output: 1 (true)
    s1->doSomething();  // Output: Singleton instance working

    return 0;
}
```



## 1.2 工厂方法模式（Factory Method Pattern）

工厂方法模式的核心思想是**通过定义一个创建对象的接口（`createTransport()`），将对象的创建延迟到子类中（`RoadLogistics` 和 `SeaLogistics`），由子类决定实例化哪一个类（`Truck` 或 `Ship`）**。这样做的好处是可以在不修改现有代码的情况下引入新的产品类型，符合开闭原则（对扩展开放，对修改关闭）。

**优点**：1）工厂方法将具体类的实例化延迟到子类中，符合开闭原则（对扩展开放，对修改关闭）。2）客户端代码不需要知道具体类，只需通过抽象类接口操作。

**缺点：每增加一个产品类，可能需要增加相应的具体工厂类，类的数量增加。**

在以下代码中，`Logistics` 类定义了一个创建 `Transport` 对象的接口 `createTransport()`，具体的 `RoadLogistics` 和 `SeaLogistics` 类实现了这个接口，分别创建 `Truck` 和 `Ship` 对象。这样，当需要增加新的运输方式时，只需创建一个新的具体工厂类并实现 `createTransport()` 方法即可，无需修改现有的代码。

***

总结下：**工厂模式需要有一个产品基类，一个工厂基类**，然后再产品基类上派生出具体产品类，一个具体产品类对应一个具体工厂类，由该具体工厂来创建具体的产品。工厂基类负责实现两个函数，一个是**创建具体产品的纯虚函数**，另一个是调用产品的功能函数，该函数需要创建具体的产品，然后由该具体产品来调用其功能函数；由于创建具体产品的函数为纯虚函数，因此必须**由具体工厂来实现该函数并创建具体产品**。

**代码如下：**

```cpp
#include <iostream>

// 抽象产品
class Transport {
 public:
  virtual void deliver() = 0;
  virtual ~Transport() = default;
};

// 具体产品：卡车
class Truck : public Transport {
 public:
  // 重写父类的纯虚函数
  virtual void deliver() override {
    std::cout << "Delivering by land (Truck)" << std::endl;
  }
};

// 具体产品：轮船
class Ship : public Transport {
 public:
  // 重写父类的纯虚函数
  virtual void deliver() override {
    std::cout << "Delivering by sea (Ship)" << std::endl;
  }
};

// 抽象工厂
class Logistics {
 public:
  // 纯虚函数，要求子类实现该方法，并创建具体的产品 Transport
  // 定义创建对象的接口，该接口是纯虚函数，要求所有继承 Logistics
  // 的子类必须实现这个方法，以创建具体的 Trasport 对象
  virtual Transport* createTransport() = 0;

  // planDelivery() 方法调用了 createTransport() 方法来创建 Transport
  // 对象，但具体创建哪种 Transport 对象由子类决定
  void planDelivery() {
    Transport* transport = createTransport();
    transport->deliver();
    delete transport;
  }
  virtual ~Logistics() = default;
};

//  RoadLogistics 和 SeaLogistics 是 Logistics 的子类，它们分别实现了
//  createTransport() 方法，决定实例化 Truck 和 Ship 对象。
// 具体工厂：陆运
class RoadLogistics : public Logistics {
 public:
  virtual Transport* createTransport() override { return new Truck(); }
};

// 具体工厂：海运
class SeaLogistics : public Logistics {
 public:
  virtual Transport* createTransport() override { return new Ship(); }
};

int main() {
  // 创建一个具体工厂对象，调用 planDelivery() 方法
  Logistics* roadLogistics = new RoadLogistics();
  roadLogistics->planDelivery();  // Output: Delivering by land (Truck)

  Logistics* seaLogistics = new SeaLogistics();
  seaLogistics->planDelivery();  // Output: Delivering by sea (Ship)

  delete roadLogistics;
  delete seaLogistics;
  return 0;
}
```



## 1.3 抽象工厂模式（Abstract Factory Pattern）

**应用场景**：当需要创建一组互相关联的对象时，例如跨平台的 UI 工具包，一个工具包可能包含按钮、文本框、菜单等。

**关键点**：提供一组工厂方法，每个方法创建相关的对象。

抽象工厂模式的核心思想是**提供一个接口，用于创建一系列相关或相互依赖的对象，而无需指定它们具体的类**。这样做的好处是可以在不修改现有代码的情况下引入新的产品系列，符合开闭原则（对扩展开放，对修改关闭）。

在这个例子中，**GUIFactory 类定义了创建 Button 和 TextBox 对象的接口，具体的 WinFactory 和 MacFactory 类实现了这个接口，分别创建 Windows 和 Mac 的按钮和文本框对象**。这样，当需要增加新的操作系统支持时，**只需创建一个新的具体工厂类并实现 GUIFactory 接口即可**，无需修改现有的代码。

**优点**：1）提供了一致的方法创建一系列相关对象，而无需指定它们的具体类。2）客户端不需要知道具体平台的实现，便可以创建相关对象。

**缺点**：增加新的产品族会非常困难，需要修改抽象工厂及所有具体工厂的接口。

**实现**：

```cpp
#include <iostream>

// 抽象按钮
class Button {
 public:
  virtual void render() = 0;
  virtual ~Button() = default;
};

// Windows 按钮
class WinButton : public Button {
 public:
  virtual void render() override { std::cout << "Windows Button" << std::endl; }
};

// Mac 按钮
class MacButton : public Button {
 public:
 virtual void render() override { std::cout << "Mac Button" << std::endl; }
};

// 抽象文本框
class TextBox {
 public:
  virtual void render() = 0;
  virtual ~TextBox() = default;
};

// Windows 文本框
class WinTextBox : public TextBox {
 public:
 virtual void render() override { std::cout << "Windows TextBox" << std::endl; }
};

// Mac 文本框
class MacTextBox : public TextBox {
 public:
 virtual void render() override { std::cout << "Mac TextBox" << std::endl; }
};

// 抽象工厂
class GUIFactory {
 public:
  virtual Button* createButton() = 0;
  virtual TextBox* createTextBox() = 0;
  virtual ~GUIFactory() = default;
};

// Windows 工厂
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
// 提供一个接口，创建一组相关或依赖的对象
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
```



## 1.4 建造者模式（Builder Pattern）

**描述**：将对象的构建过程与其表示分离，以便同样的构建过程可以创建不同的表示。

**应用场景**：用于创建复杂对象，例如构建多步骤对象（如汽车、房子）。

**关键点**：将构造过程与表示分离；**允许一步步的构建，同时隐藏复杂的构建逻辑**。

建造者模式的核心思想是将**一个复杂对象的构建过程与其表示分离，使得同样的构建过程可以创建不同的表示**。建造者模式通常包括以下几个角色：

1. **产品（Product）**：最终要构建的复杂对象。
2. **抽象建造者（Builder）**：定义构建产品各个部分的接口。
3. **具体建造者（ConcreteBuilder）**：实现抽象建造者接口，构建和装配产品的各个部分。
4. **导演（Director）**：负责管理构建过程，调用建造者的方法来构建产品。

在这个例子中，`Computer` 是产品类，`ComputerBuilder` 是抽象建造者类，`GamingComputerBuilder` 是具体建造者类，`Director` 是导演类。通过将构建过程与表示分离，建造者模式使得构建过程可以灵活地创建不同的产品表示。

**优点：**1）可以改变建造过程来得到不同的表示。2）构建过程可以被复用，避免了构造函数的膨胀。

**缺点：**增加了复杂性，尤其是产品类特别简单时，使用该模式显得有些冗余。

**实现**：

```cpp
#include <iostream>
#include <memory>
#include <string>

// 最终产品：电脑
class Computer {
 public:
  void setCPU(const std::string& cpu) { m_cpu = cpu; }
  void setRAM(const std::string& ram) { m_ram = ram; }
  void setStorage(const std::string& storage) { m_storage = storage; }

  void showSpec() const {
    std::cout << "CPU: " << m_cpu << "\n"
              << "RAM: " << m_ram << "\n"
              << "Storage: " << m_storage << std::endl;
  }

 private:
  std::string m_cpu;
  std::string m_ram;
  std::string m_storage;
};

// 抽象建造者
class ComputerBuilder {
 public:
  virtual ~ComputerBuilder() = default;
  virtual void buildCPU() = 0;
  virtual void buildRAM() = 0;
  virtual void buildStorage() = 0;
  virtual Computer getResult() = 0;
};

// 具体建造者：游戏电脑
class GamingComputerBuilder : public ComputerBuilder {
 public:
  GamingComputerBuilder() { m_computer = Computer(); }

  void buildCPU() override { m_computer.setCPU("Intel i9"); }
  void buildRAM() override { m_computer.setRAM("32GB DDR5"); }
  void buildStorage() override { m_computer.setStorage("2TB NVMe SSD"); }
  Computer getResult() override { return m_computer; }

 private:
  Computer m_computer;
};

// 导演类（可选）
class Director {
 public:
  Computer construct(ComputerBuilder& builder) {
    builder.buildCPU();
    builder.buildRAM();
    builder.buildStorage();
    return builder.getResult();
  }
};

int main() {
  GamingComputerBuilder builder; // 创建游戏电脑建造者
  Director director;
  Computer computer = director.construct(builder);
  computer.showSpec();
  // Output:
  // CPU: Intel i9
  // RAM: 32GB DDR5
  // Storage: 2TB NVMe SSD

  return 0;
}
```



## 1.5 原型模式（Prototype Pattern）

**关键点**：提供克隆自身的能力；可以通过**深拷贝或浅拷贝**来实现。

原型模式的核心思想是**通过复制现有的对象来创建新对象，而不是通过实例化类来创建对象**。这样做的好处是可以避免创建对象时的复杂初始化过程，并且可以在运行时动态地创建对象。

在这个例子中，Prototype 类定义了一个克隆对象的接口 clone()，具体的 DocumentTemplate 类实现了这个接口，**通过深拷贝来克隆对象**。这样，**当需要创建一个新的 DocumentTemplate 对象时，可以通过克隆现有的对象来实现，而不需要重新实例化类**。

**优点**：1）**通过克隆而不是实例化来创建对象**，减少了复杂对象创建的开销。2）**可以在运行时动态改变具体对象的类型**。

**缺点**：如果对象之间存在复杂的依赖关系，克隆可能会变得复杂，特别是深拷贝时需要处理的对象间依赖关系。

**实现**：

```cpp
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
```



## 1.6 创建型模式总结

| **模式** |       **核心目标**       |           **适用场景**           |
| :------: | :----------------------: | :------------------------------: |
|   单例   |       全局唯一实例       | 配置管理、日志服务等全局唯一场景 |
| 工厂方法 | **由子类决定实例化对象** |   需要动态创建**不同子类对象**   |
| 抽象工厂 |   **创建一组相关对象**   |  跨平台组件、产品族兼容性要求高  |
|  建造者  |  **分步骤构造复杂对象**  | 构造过程复杂、需要灵活配置的对象 |
|   原型   |   **通过克隆生成对象**   |   对象创建成本高、需要快速复制   |



# 二、结构型模式

结构型模式主要关注**类与对象之间的组合与关系**，它们通过不同的方式组合类或对象来实现更大的结构，以满足更复杂的设计需求。结构型模式的主要目标是**处理对象的组合关系，使得系统更灵活、扩展性更好、复用性更强**。

## 2.1 适配器模式（Adapter Pattern）

**描述**：将一个类的接口转换为客户端期望的另一个接口，使得原本接口不兼容的类能够协同工作。

**应用场景**：需要使用一个现有的类，但它的接口与当前系统不兼容时；当你想要复用一些已有的类，而这些类的接口与系统期望的接口不符时。

**实现**：

```cpp
// 目标接口（客户端期望的接口）
class Target {
public:
    virtual void request() { std::cout << "Target request" << std::endl; }
};

// 现有类（需要适配的类）
class Adaptee {
public:
    void specificRequest() { std::cout << "Adaptee specific request" << std::endl; }
};

// 适配器类（将 Adaptee 的接口转换为 Target 的接口）
class Adapter : public Target {
private:
    Adaptee* adaptee;
public:
    Adapter(Adaptee* a) : adaptee(a) {}
    void request() override {
        adaptee->specificRequest();
    }
};

// 客户端代码
int main() {
    Adaptee* adaptee = new Adaptee();
    Target* target = new Adapter(adaptee);
    target->request(); // 输出: "Adaptee specific request"
    return 0;
}
```



## 2.2 桥接模式（Bridge Pattern）

**描述**：将抽象部分与其实现部分分离，使它们可以独立变化。

**应用场景**：当需要在多个维度上扩展时，可以使用桥接模式进行解耦。

注意：将抽象与实现分离，使用**组合**而不是**继承**。

**实现**：

```cpp
// 实现接口
class Implementor {
public:
    virtual void operationImpl() = 0;
};

// 具体实现类
class ConcreteImplementorA : public Implementor {
public:
    void operationImpl() override {
        std::cout << "ConcreteImplementorA operation" << std::endl;
    }
};

// 抽象接口
class Abstraction {
protected:
    Implementor* implementor;
public:
    Abstraction(Implementor* impl) : implementor(impl) {}
    virtual void operation() = 0;
};

// 扩展抽象类
class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(Implementor* impl) : Abstraction(impl) {}
    void operation() override {
        implementor->operationImpl();
    }
};

// 客户端代码
int main() {
    Implementor* impl = new ConcreteImplementorA();
    Abstraction* abstraction = new RefinedAbstraction(impl);
    abstraction->operation(); // 输出: "ConcreteImplementorA operation"
    return 0;
}

```

**优点：**

- 分离了抽象和实现，降低了类之间的耦合度。
- 实现可以在运行时动态更改，不需要修改抽象部分。

**缺点：**

- 增加了系统的复杂性。



## 2.3 组合模式（Composite Pattern）

**描述**：将对象组合成树形结构，以表示“部分-整体”的层次结构。组合模式使客户端对单个对象和组合对象的使用具有一致性。

**应用场景**：用于表示对象的层次结构，如文件系统。

**关键点：**

- 组合模式基于递归结构。
- 叶节点和组合节点实现相同的接口。

**实现**：

```cpp
// 抽象组件
class Component {
public:
    virtual void operation() = 0;
};

// 叶节点类
class Leaf : public Component {
public:
    void operation() override {
        std::cout << "Leaf operation" << std::endl;
    }
};

// 组合节点类
class Composite : public Component {
private:
    std::vector<Component*> children;
public:
    void add(Component* component) {
        children.push_back(component);
    }
    void operation() override {
        std::cout << "Composite operation" << std::endl;
        for (auto child : children) {
            child->operation();
        }
    }
};

// 客户端代码
int main() {
    Leaf* leaf1 = new Leaf();
    Leaf* leaf2 = new Leaf();
    
    Composite* composite = new Composite();
    composite->add(leaf1);
    composite->add(leaf2);
    
    composite->operation(); // 输出: "Composite operation" 和两次 "Leaf operation"
    return 0;
}
```

**优点：**

- 简化了客户端代码，使得客户端可以一致地处理单个对象和组合对象。
- 可以方便地增加新的组件。

**缺点：**

- 对象层次过于复杂时，可能导致系统的复杂性增加。



## 2.4 装饰者模式（Decorator Pattern）

**描述**：动态地给对象添加职责，而不改变其接口。装饰者模式提供了比继承更灵活的功能扩展方式。

**应用场景**：用于扩展对象的功能，如图形绘制系统中的滤镜效果。

**关键点：**

- 装饰器和被装饰对象实现相同的接口。
- 装饰器持有被装饰对象的引用，并将操作委托给被装饰对象。

**实现**：

```cpp
// 抽象组件
class Component {
public:
    virtual void operation() = 0;
};

// 具体组件
class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "ConcreteComponent operation" << std::endl;
    }
};

// 装饰者抽象类
class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* comp) : component(comp) {}
    void operation() override {
        component->operation();
    }
};

// 具体装饰者
class ConcreteDecorator : public Decorator {
public:
    ConcreteDecorator(Component* comp) : Decorator(comp) {}
    void operation() override {
        Decorator::operation();
        addedBehavior();
    }
    void addedBehavior() {
        std::cout << "Added behavior" << std::endl;
    }
};

// 客户端代码
int main() {
    Component* component = new ConcreteComponent();
    Component* decoratedComponent = new ConcreteDecorator(component);
    
    decoratedComponent->operation(); // 输出: "ConcreteComponent operation" 和 "Added behavior"
    return 0;
}
```

**优点：**

- 比继承更灵活，可以在运行时动态地增加或删除对象的功能。
- 遵循开闭原则（对扩展开放，对修改关闭）。

**缺点：**

- 增加了系统的复杂性，特别是使用过多装饰者时，可能会导致代码难以维护。



## 2.5 外观模式（Facade Pattern）

**目的**：为子系统中的一组接口提供一个一致的接口，外观模式定义了一个高层接口，使得子系统更容易使用。

**用法场景**：

- 当需要简化复杂子系统的操作时（如数据库、第三方库或操作系统的调用）。
- 当希望为一个复杂的子系统提供一个简单的接口时。

**关键点：**

- 外观模式并不限制子系统类本身的使用，客户端仍然可以直接访问子系统类。

**实现：**

```cpp
// 子系统类1
class Subsystem1 {
public:
    void operation1() {
        std::cout << "Subsystem1: operation1" << std::endl;
    }
};

// 子系统类2
class Subsystem2 {
public:
    void operation2() {
        std::cout << "Subsystem2: operation2" << std::endl;
    }
};

// 外观类
class Facade {
private:
    Subsystem1* subsystem1;
    Subsystem2* subsystem2;
public:
    Facade() {
        subsystem1 = new Subsystem1();
        subsystem2 = new Subsystem2();
    }
    
    void operation() {
        std::cout << "Facade simplifies subsystem operations:" << std::endl;
        subsystem1->operation1();
        subsystem2->operation2();
    }
};

// 客户端代码
int main() {
    Facade* facade = new Facade();
    facade->operation();
    // 输出：
    // Facade simplifies subsystem operations:
    // Subsystem1: operation1
    // Subsystem2: operation2
    return 0;
}
```

**优点：**

- 为复杂子系统提供一个简单的接口，简化了客户端的操作。
- 松散了客户端与子系统之间的耦合，使得子系统更容易扩展和维护。

**缺点：**

- 可能会让子系统的功能变得不透明，如果外观模式过度简化，可能无法完全展现子系统的全部能力。



## 2.6 享元模式（Flyweight Pattern）

**目的：**

通过**共享技术**来支持**大量细粒度对象的高效复用**，减少内存使用量。

**用法场景：**

- 当系统中有大量相似的对象时，使用享元模式来减少内存占用。
- 对象的数量非常大，并且大多数状态可以外部化时。

**关键点：**

- 将对象的可共享部分和不可共享部分分离。共享部分称为**内部状态**，不可共享部分称为**外部状态**。

**实现：**

```cpp
#include <iostream>
#include <unordered_map>

// 享元接口
class Flyweight {
public:
    virtual void operation(int extrinsicState) = 0;
};

// 具体享元类
class ConcreteFlyweight : public Flyweight {
private:
    int intrinsicState;
public:
    ConcreteFlyweight(int state) : intrinsicState(state) {}
    
    void operation(int extrinsicState) override {
        std::cout << "Intrinsic state: " << intrinsicState << ", Extrinsic state: " << extrinsicState << std::endl;
    }
};

// 享元工厂
class FlyweightFactory {
private:
    std::unordered_map<int, Flyweight*> flyweights;
public:
    Flyweight* getFlyweight(int key) {
        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new ConcreteFlyweight(key);
        }
        return flyweights[key];
    }
};

// 客户端代码
int main() {
    FlyweightFactory factory;
    
    Flyweight* fw1 = factory.getFlyweight(1);
    fw1->operation(100); // 输出: Intrinsic state: 1, Extrinsic state: 100
    
    Flyweight* fw2 = factory.getFlyweight(2);
    fw2->operation(200); // 输出: Intrinsic state: 2, Extrinsic state: 200
    
    Flyweight* fw3 = factory.getFlyweight(1);
    fw3->operation(300); // 输出: Intrinsic state: 1, Extrinsic state: 300
    
    return 0;
}
```

**优点：**

- 通过共享对象，有效减少内存开销。
- 享元模式可以大大提高系统在大量细粒度对象下的性能。

**缺点：**

- 增加了系统的复杂性，特别是当有大量外部状态时，管理这些状态的工作变得复杂。



## 2.7 代理模式（Proxy Pattern）

**目的：**为其他对象提供一种代理以控制对这个对象的访问。代理模式通常用来**控制对象的创建、访问或行为**。

**用法场景：**

- 需要控制访问某个类或对象时（如远程对象、昂贵的对象）。
- 当需要延迟加载（懒加载）某个对象时。

**关键点：**

- 代理类实现了与真实对象相同的接口，客户端无法直接访问真实对象，只能通过代理来间接访问。

**常见类型：**

- **虚代理**：延迟加载资源。
- **远程代理**：控制对远程对象的访问。
- **保护代理**：控制对敏感对象的访问。
  

**实现：**

```cpp
// 抽象主题
class Subject {
public:
    virtual void request() = 0;
};

// 真实主题
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject request" << std::endl;
    }
};

// 代理类
class Proxy : public Subject {
private:
    RealSubject* realSubject;
public:
    Proxy() : realSubject(nullptr) {}
    
    void request() override {
        if (!realSubject) {
            realSubject = new RealSubject();  // 延迟创建真实对象
        }
        realSubject->request();
    }
};

// 客户端代码
int main() {
    Subject* proxy = new Proxy();
    proxy->request();  // 输出: "RealSubject request"
    return 0;
}
```

**优点：**

- 可以控制对象的访问，增加了灵活性。
- 可以延迟初始化昂贵的对象，提升系统性能。

**缺点：**

- 增加了一层间接性，可能会导致请求的处理速度变慢。
- 增加了系统复杂性。

## 2.8 总结

- **适配器模式**：转换接口，解决接口不兼容问题。
- **桥接模式**：分离抽象与实现，解决多维度扩展问题。
- **组合模式**：组合对象，处理部分-整体的层次结构。
- **装饰者模式**：动态地添加对象功能，解决类膨胀问题。
- **外观模式**：简化子系统的接口，提供统一接口。
- **享元模式**：共享对象，减少内存消耗。
- **代理模式**：控制对对象的访问，增强系统的灵活性。

结构型模式主要通过合理地组合类和对象，使得系统更灵活、可扩展，并且在处理复杂问题时，提供了一些有效的解决方案。如果你对其中某些模式有更多的疑问，或需要在项目中应用，可以进一步讨论。

# 三、行为型模式

行为型模式主要关注对象之间的**职责分配与交互**，定义了对象如何协作以完成某些任务。行为型模式通过明确的模式和规范来组织对象间的通信，帮助解决对象的职责分配、算法封装等问题，主要目的是提升系统的**可扩展性**和**可维护性**。

## 3.1 观察者模式（Observer Pattern）

**描述**：定义对象间的一对多依赖，当一个对象状态发生变化时，所有依赖它的对象都会收到通知并自动更新。

**应用场景**：例如事件系统、GUI控件状态变化。

**实现**：

```cpp
class Observer {
public:
    virtual void update() = 0;
};
class Subject {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer* o) { observers.push_back(o); }
    void notify() {
        for (auto* o : observers) {
            o->update();
        }
    }
};
class ConcreteObserver : public Observer {
public:
    void update() override { /* 更新操作 */ }
};
```

## 3.2 命令模式（Command Pattern）

**描述**：将请求封装为一个对象，从而使您可以用不同的请求对客户端进行参数化。

**应用场景**：例如操作历史记录、事务系统。

**实现**：

```cpp
class Command {
public:
    virtual void execute() = 0;
};
class Receiver {
public:
    void action() { /* 执行操作 */ }
};
class ConcreteCommand : public Command {
private:
    Receiver* receiver;
public:
    ConcreteCommand(Receiver* r) : receiver(r) {}
    void execute() override { receiver->action(); }
};
```

## 3.3 状态模式（State Pattern）
**描述**：允许对象在内部状态发生改变时改变其行为，看起来像是改变了类。

**应用场景**：如状态机，应用于对象有多种状态，并且状态转换较复杂时。

**实现**：
```cpp
class State {
public:
    virtual void handle() = 0;
};
class Context {
private:
    State* state;
public:
         void setState(State* s) { state = s; }
         void request() { state->handle(); }
};
```

这只是设计模式的简要概述，实际应用时要根据具体的场景选择合适的模式。有些模式也可以组合使用，如将**工厂模式**与**单例模式**结合，以管理对象的生命周期。
- [一、创建型模式](#一创建型模式)
- [二、结构型模式](#二结构型模式)
- [三、行为型模式](#三行为型模式)


常见的设计模型在面试时会考察，因此在这里进行整理下。

1. [单例模式](01单例模式.md)

C++ 中的设计模式是经过验证的通用解决方案，用于解决常见的设计问题。它们通常分为三大类：**创建型**、**结构型**和**行为型**。以下是每种模式的简要总结及其应用：

# 一、创建型模式

创建型模式主要处理对象的创建问题，目的是解耦对象的创建和使用。

## 1.1 单例模式（Singleton Pattern）

- **描述**：确保类只有一个实例，并提供全局访问点。
- **应用场景**：需要全局唯一实例时，例如日志类、线程池。
- **实现**：
  
  ```cpp
  class Singleton {
  public:
      static Singleton& getInstance() {
          static Singleton instance;
          return instance;
      }
  private:
      Singleton() {}
      Singleton(const Singleton&) = delete;
      void operator=(const Singleton&) = delete;
  };
  ```

## 1.2 工厂方法模式（Factory Method Pattern）

- **描述**：定义一个接口，用于创建对象，但让子类决定实例化哪一个类。
- **应用场景**：当类的实例化逻辑复杂时，将其委托给子类处理。
- **实现**：
  ```cpp
  class Product {
  public:
      virtual void use() = 0;
  };
  class ConcreteProduct : public Product {
  public:
      void use() override { /* 实现具体功能 */ }
  };
  class Creator {
  public:
      virtual Product* factoryMethod() = 0;
  };
  class ConcreteCreator : public Creator {
  public:
      Product* factoryMethod() override { return new ConcreteProduct(); }
  };
  ```

## 1.3 抽象工厂模式（Abstract Factory Pattern）

- **描述**：提供创建一系列相关或相互依赖对象的接口，而无需指定它们的具体类。
- **应用场景**：需要创建一组相关对象，如跨平台UI组件。
- **实现**：
  ```cpp
  class AbstractFactory {
  public:
      virtual Button* createButton() = 0;
      virtual TextBox* createTextBox() = 0;
  };
  class ConcreteFactory : public AbstractFactory {
  public:
      Button* createButton() override { return new ConcreteButton(); }
      TextBox* createTextBox() override { return new ConcreteTextBox(); }
  };
  ```

## 1.4 建造者模式（Builder Pattern）

- **描述**：将对象的构建过程与其表示分离，以便同样的构建过程可以创建不同的表示。
- **应用场景**：用于创建复杂对象，例如构建多步骤对象（如汽车、房子）。
- **实现**：
  ```cpp
  class Product {
      // 复杂对象
  };
  class Builder {
  public:
      virtual void buildPartA() = 0;
      virtual void buildPartB() = 0;
      virtual Product* getResult() = 0;
  };
  class ConcreteBuilder : public Builder {
  public:
      void buildPartA() override { /* 构建 A */ }
      void buildPartB() override { /* 构建 B */ }
      Product* getResult() override { return new Product(); }
  };
  ```

## 1.5 原型模式（Prototype Pattern）

- **描述**：通过复制现有对象来创建新对象，而不是通过实例化类。
- **应用场景**：当对象的创建成本较高时，通过克隆已有实例来减少开销。
- **实现**：
  ```cpp
  class Prototype {
  public:
      virtual Prototype* clone() const = 0;
  };
  class ConcretePrototype : public Prototype {
  public:
      Prototype* clone() const override { return new ConcretePrototype(*this); }
  };
  ```

# 二、结构型模式

结构型模式关注类和对象之间的组合，确保这些类能协同工作。

## 2.1 适配器模式（Adapter Pattern）

- **描述**：将一个类的接口转换为客户端所期望的另一个接口。
- **应用场景**：接口不兼容的类需要一起工作时使用。
- **实现**：
  ```cpp
  class Target {
  public:
      virtual void request() = 0;
  };
  class Adaptee {
  public:
      void specificRequest() { /* 特定功能 */ }
  };
  class Adapter : public Target {
  private:
      Adaptee* adaptee;
  public:
      Adapter(Adaptee* a) : adaptee(a) {}
      void request() override { adaptee->specificRequest(); }
  };
  ```

## 2.2 桥接模式（Bridge Pattern）

- **描述**：将抽象部分与其实现部分分离，使它们可以独立变化。
- **应用场景**：当需要在多个维度上扩展时，可以使用桥接模式进行解耦。
- **实现**：
  ```cpp
  class Implementor {
  public:
      virtual void operationImpl() = 0;
  };
  class ConcreteImplementor : public Implementor {
  public:
      void operationImpl() override { /* 实现功能 */ }
  };
  class Abstraction {
  protected:
      Implementor* implementor;
  public:
      Abstraction(Implementor* impl) : implementor(impl) {}
      virtual void operation() { implementor->operationImpl(); }
  };
  ```

## 2.3 组合模式（Composite Pattern）

- **描述**：将对象组合成树形结构，以表示“部分-整体”的层次结构。组合模式使客户端对单个对象和组合对象的使用具有一致性。
- **应用场景**：用于表示对象的层次结构，如文件系统。
- **实现**：
  ```cpp
  class Component {
  public:
      virtual void operation() = 0;
  };
  class Leaf : public Component {
  public:
      void operation() override { /* 叶子节点的操作 */ }
  };
  class Composite : public Component {
  private:
      std::vector<Component*> children;
  public:
      void add(Component* c) { children.push_back(c); }
      void operation() override {
          for (auto* child : children) {
              child->operation();
          }
      }
  };
  ```

## 2.4 装饰者模式（Decorator Pattern）

- **描述**：动态地给对象添加职责，而不改变其结构。
- **应用场景**：用于扩展对象的功能，如图形绘制系统中的滤镜效果。
- **实现**：
  ```cpp
  class Component {
  public:
      virtual void operation() = 0;
  };
  class ConcreteComponent : public Component {
  public:
      void operation() override { /* 基本功能 */ }
  };
  class Decorator : public Component {
  protected:
      Component* component;
  public:
      Decorator(Component* c) : component(c) {}
      void operation() override { component->operation(); }
  };
  class ConcreteDecorator : public Decorator {
  public:
      ConcreteDecorator(Component* c) : Decorator(c) {}
      void operation() override {
          Decorator::operation();
          // 扩展功能
      }
  };
  ```



# 三、行为型模式

行为型模式关注对象间的职责分配以及它们之间如何协作。

## 3.1 观察者模式（Observer Pattern）

- **描述**：定义对象间的一对多依赖，当一个对象状态发生变化时，所有依赖它的对象都会收到通知并自动更新。
- **应用场景**：例如事件系统、GUI控件状态变化。
- **实现**：
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

- **描述**：将请求封装为一个对象，从而使您可以用不同的请求对客户端进行参数化。
- **应用场景**：例如操作历史记录、事务系统。
- **实现**：
  
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
- **描述**：允许对象在内部状态发生改变时改变其行为，看起来像是改变了类。
- **应用场景**：如状态机，应用于对象有多种状态，并且状态转换较复杂时。
- **实现**：
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
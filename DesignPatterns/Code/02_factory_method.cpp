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

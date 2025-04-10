#include <iostream>
#include <memory>

// 抽象产品：椅子
class Chair {
 public:
  virtual void sit() = 0;
  virtual ~Chair() = default;
};

// 抽象产品：沙发
class Sofa {
 public:
  virtual void lie() = 0;
  virtual ~Sofa() = default;
};

// 具体产品：现代风格椅子
class ModernChair : public Chair {
 public:
  void sit() override { std::cout << "坐在现代风格椅子上\n"; }
};

// 具体产品：现代风格沙发
class ModernSofa : public Sofa {
 public:
  void lie() override { std::cout << "躺在现代风格沙发上\n"; }
};

// 具体产品：古典风格椅子
class VictorianChair : public Chair {
 public:
  void sit() override { std::cout << "坐在古典雕花椅子上\n"; }
};

// 具体产品：古典风格沙发
class VictorianSofa : public Sofa {
 public:
  void lie() override { std::cout << "躺在古典真皮沙发上\n"; }
};

// 抽象工厂
class FurnitureFactory {
 public:
  virtual std::unique_ptr<Chair> createChair() = 0;
  virtual std::unique_ptr<Sofa> createSofa() = 0;
  virtual ~FurnitureFactory() = default;
};

// 现代风格工厂
class ModernFactory : public FurnitureFactory {
 public:
  std::unique_ptr<Chair> createChair() override {
    return std::make_unique<ModernChair>();
  }

  std::unique_ptr<Sofa> createSofa() override {
    return std::make_unique<ModernSofa>();
  }
};

// 古典风格工厂
class VictorianFactory : public FurnitureFactory {
 public:
  std::unique_ptr<Chair> createChair() override {
    return std::make_unique<VictorianChair>();
  }

  std::unique_ptr<Sofa> createSofa() override {
    return std::make_unique<VictorianSofa>();
  }
};

// 客户端代码
void createFurnitureSet(FurnitureFactory& factory) {
  auto chair = factory.createChair();
  auto sofa = factory.createSofa();

  chair->sit();
  sofa->lie();
}

int main() {
  // 创建现代风格家具
  ModernFactory modernFactory;
  std::cout << "现代风格家具组合:\n";
  createFurnitureSet(modernFactory);

  // 创建古典风格家具
  VictorianFactory victorianFactory;
  std::cout << "\n古典风格家具组合:\n";
  createFurnitureSet(victorianFactory);

  return 0;
}

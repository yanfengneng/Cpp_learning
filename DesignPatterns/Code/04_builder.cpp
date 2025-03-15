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

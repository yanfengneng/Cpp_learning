#include <iostream>
#include <string>

class Employee {
 public:
  std::string name;
};

void simulate_segmentation_fault(const std::string& name) {
  try {
    Employee* employee = new Employee();
    employee->name = name;
    std::cout << "Employee name = " << employee->name << std::endl;
    delete employee;
    std::cout << "After deletion, employee name = " << employee->name
              << std::endl;
  } catch (...) {
    std::cout << "Error occurred!" << std::endl;
  }
}

int main(int argc, char* argv[]) {
  std::string text = "hello world";
  std::cout << text << std::endl;
  simulate_segmentation_fault(text);
  return 0;
}
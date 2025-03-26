#include <algorithm>
#include <iostream>

// 旧版日志类
class OldLogger {
 public:
  void write_log(const std::string& msg) {
    std::cout << "Old Logger: " << msg << std::endl;
  }
};

// 新系统目标接口
class NewLogger {
 public:
  virtual void log(const std::string& msg) = 0;
};

// 适配器类（继承接口 + 组合旧对象）
class LoggerAdapter : public NewLogger {
 private:
  OldLogger* old_logger_;

 public:
  LoggerAdapter(OldLogger* logger) : old_logger_(logger) {}

  void log(const std::string& msg) override {
    std::string upper_msg = msg;
    std::transform(msg.begin(), msg.end(), upper_msg.begin(), ::toupper);
    old_logger_->write_log(upper_msg);
  }
};

// 使用
int main() {
  OldLogger old_logger;
  LoggerAdapter adapter(&old_logger);
  adapter.log("new message");  // 输出：Old Logger: NEW MESSAGE
  return 0;
}

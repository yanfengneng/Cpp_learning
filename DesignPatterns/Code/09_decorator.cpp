#include <iostream>

// 基础接口
class DataStream {
 public:
  virtual void write(const std::string& data) = 0;
};

// 具体组件
class FileStream : public DataStream {
 public:
  void write(const std::string& data) override {
    std::cout << "Write to file: " << data << std::endl;
  }
};

// 装饰器基类
class StreamDecorator : public DataStream {
 protected:
  DataStream* stream_;

 public:
  StreamDecorator(DataStream* stream) : stream_(stream) {}
};

// 加密装饰器
class EncryptedStream : public StreamDecorator {
 public:
  EncryptedStream(DataStream* stream) : StreamDecorator(stream) {}

  void write(const std::string& data) override {
    stream_->write("[ENCRYPTED] " + data);
  }
};

// 压缩装饰器
class CompressedStream : public StreamDecorator {
 public:
  CompressedStream(DataStream* stream) : StreamDecorator(stream) {}

  void write(const std::string& data) override {
    stream_->write("[COMPRESSED] " + data);
  }
};

// 使用
int main() {
  FileStream file;
  EncryptedStream encrypted(&file);
  CompressedStream compressed(&encrypted);

  compressed.write("Hello");
  // 输出：Write to file: [COMPRESSED] [ENCRYPTED] Hello
  return 0;
}
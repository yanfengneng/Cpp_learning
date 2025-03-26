#include <iostream>
#include <string>

// 真实主题
class Image {
 private:
  std::string filename_;

 public:
  Image(const std::string& filename) : filename_(filename) {}

  void display() {
    std::cout << "Displaying image: " << filename_ << std::endl;
  }
};

// 代理类
class ImageProxy {
 private:
  Image* real_image_ = nullptr;
  std::string filename_;

 public:
  ImageProxy(const std::string& filename) : filename_(filename) {}

  void display() {
    if (real_image_ == nullptr) {
      real_image_ = new Image(filename_);  // 延迟加载
    }
    real_image_->display();
  }
};

// 使用
int main() {
  ImageProxy proxy("large_image.jpg");
  proxy.display();  // 首次调用时加载真实图片
  return 0;
}

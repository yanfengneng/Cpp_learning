#include <iostream>

// 实现部分接口
class Renderer {
 public:
  virtual void render_circle(float radius) = 0;
};

// 具体实现：OpenGL
class OpenGLRenderer : public Renderer {
 public:
  void render_circle(float radius) override {
    std::cout << "OpenGL: Drawing circle (r=" << radius << ")\n";
  }
};

// 抽象部分基类
class Shape {
 protected:
  Renderer* renderer_;

 public:
  Shape(Renderer* renderer) : renderer_(renderer) {}
  virtual void draw() = 0;
};

// 具体形状
class Circle : public Shape {
 private:
  float radius_;

 public:
  Circle(Renderer* renderer, float r) : Shape(renderer), radius_(r) {}

  void draw() override { renderer_->render_circle(radius_); }
};

// 使用
int main() {
  OpenGLRenderer opengl;
  Circle circle(&opengl, 5.0f);
  circle.draw();  // 输出：OpenGL: Drawing circle (r=5)
}

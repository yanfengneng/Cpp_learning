#include <unistd.h>

#include <iostream>

#include "mutexlock.hpp"

#define NUM_THREADS 10000
using namespace std;

class person {
 public:
  person(const std::string name = "", int age = 0) : name_(name), age_(age) {
    std::cout << "Init a person!" << std::endl;
  }
  ~person() { std::cout << "Destory a person!" << std::endl; }
  const std::string& getname() const { return this->name_; }
  int getage() const { return this->age_; }

 private:
  const std::string name_;
  int age_;
};

int num=0;
Mutex mutex;

void *count(void *args) {
    MutexLock lock(&mutex);
    num++;
}

int main() {
  int t;
  pthread_t thread[NUM_THREADS];

  for (t = 0; t < NUM_THREADS; t++) {
    int ret = pthread_create(&thread[t], NULL, count, NULL);
    if (ret) {
      return -1;
    }
  }

  for (t = 0; t < NUM_THREADS; t++) pthread_join(thread[t], NULL);
  std::cout << num << std::endl;
  return 0;
}
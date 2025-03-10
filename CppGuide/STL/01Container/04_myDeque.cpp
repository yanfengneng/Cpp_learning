#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
 private:
  struct Node {
    T* data;
    Node* next;
    Node* prev;
    int capacity;
    int size;

    Node(int cap = 4) : capacity(cap), size(0), next(nullptr), prev(nullptr) {
      data = new T[capacity];
    }

    ~Node() { delete[] data; }
  };

  Node* head;
  Node* tail;
  int dequeSize;

 public:
  Deque() : head(nullptr), tail(nullptr), dequeSize(0) {}

  ~Deque() { clear(); }

  bool empty() const { return dequeSize == 0; }

  int size() const { return dequeSize; }

  void push_back(const T& value) {
    if (!tail || tail->size == tail->capacity) {
      Node* newNode = new Node();
      if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
      } else {
        head = newNode;
      }
      tail = newNode;
    }
    tail->data[tail->size++] = value;
    dequeSize++;
  }

  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (!tail || tail->size == tail->capacity) {
      Node* newNode = new Node();
      if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
      } else {
        head = newNode;
      }
      tail = newNode;
    }
    tail->data[tail->size++] = T(std::forward<Args>(args)...);
    dequeSize++;
  }

  void push_front(const T& value) {
    if (!head || head->size == head->capacity) {
      Node* newNode = new Node();
      if (head) {
        head->prev = newNode;
        newNode->next = head;
      } else {
        tail = newNode;
      }
      head = newNode;
    }
    for (int i = head->size; i > 0; --i) {
      head->data[i] = head->data[i - 1];
    }
    head->data[0] = value;
    head->size++;
    dequeSize++;
  }

  template <typename... Args>
  void emplace_front(Args&&... args) {
    if (!head || head->size == head->capacity) {
      Node* newNode = new Node();
      if (head) {
        head->prev = newNode;
        newNode->next = head;
      } else {
        tail = newNode;
      }
      head = newNode;
    }
    for (int i = head->size; i > 0; --i) {
      head->data[i] = head->data[i - 1];
    }
    head->data[0] = T(std::forward<Args>(args)...);
    head->size++;
    dequeSize++;
  }
  
  void pop_back() {
    if (empty()) throw std::out_of_range("Deque is empty");
    tail->size--;
    dequeSize--;
    if (tail->size == 0 && tail != head) {
      Node* temp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete temp;
    }
  }

  void pop_front() {
    if (empty()) throw std::out_of_range("Deque is empty");
    for (int i = 0; i < head->size - 1; ++i) {
      head->data[i] = head->data[i + 1];
    }
    head->size--;
    dequeSize--;
    if (head->size == 0 && head != tail) {
      Node* temp = head;
      head = head->next;
      head->prev = nullptr;
      delete temp;
    }
  }

  T& front() {
    if (empty()) throw std::out_of_range("Deque is empty");
    return head->data[0];
  }

  T& back() {
    if (empty()) throw std::out_of_range("Deque is empty");
    return tail->data[tail->size - 1];
  }

  void clear() {
    while (!empty()) pop_back();
  }

};

int main() {
  Deque<int> dq;
 

  return 0;
}

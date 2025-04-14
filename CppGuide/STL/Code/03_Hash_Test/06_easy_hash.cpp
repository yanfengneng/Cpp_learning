#include <functional>
#include <iostream>
#include <list>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
class SimpleHashMap {
 private:
  struct Node {
    Key key;
    Value value;
    Node(const Key& k, const Value& v) : key(k), value(v) {}
  };

  std::vector<std::list<Node>> buckets;
  size_t element_count = 0;
  Hash hasher;
  KeyEqual key_equal;
  double max_load = 0.75;

  // 获取哈希桶索引
  size_t get_bucket(const Key& key) const {
    return hasher(key) % buckets.size();
  }

  // 动态扩容
  void rehash() {
    size_t new_size = buckets.size() * 2 + 1;
    std::vector<std::list<Node>> new_buckets(new_size);

    for (auto& bucket : buckets) {
      for (auto& node : bucket) {
        size_t new_index = hasher(node.key) % new_size;
        new_buckets[new_index].push_back(node);
      }
    }

    buckets.swap(new_buckets);
  }

 public:
  // 构造函数
  explicit SimpleHashMap(size_t initial_size = 11) : buckets(initial_size) {}

  // 插入/更新键值对
  void insert(const Key& key, const Value& value) {
    // 检查是否需要扩容
    if ((double)element_count / buckets.size() >= max_load) {
      rehash();
    }

    size_t index = get_bucket(key);
    auto& bucket = buckets[index];

    // 查找是否已存在相同键
    for (auto& node : bucket) {
      if (key_equal(node.key, key)) {
        node.value = value;  // 更新现有值
        return;
      }
    }

    // 添加新节点
    bucket.emplace_back(key, value);
    ++element_count;
  }

  // 查找值（返回指针避免拷贝成本）
  Value* find(const Key& key) {
    size_t index = get_bucket(key);
    auto& bucket = buckets[index];

    for (auto& node : bucket) {
      if (key_equal(node.key, key)) {
        return &node.value;
      }
    }
    return nullptr;
  }

  // 删除键值对
  bool erase(const Key& key) {
    size_t index = get_bucket(key);
    auto& bucket = buckets[index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (key_equal(it->key, key)) {
        bucket.erase(it);
        --element_count;
        return true;
      }
    }
    return false;
  }

  // 键值访问运算符
  Value& operator[](const Key& key) {
    if (auto ptr = find(key)) {
      return *ptr;
    }
    insert(key, Value());
    return *find(key);
  }

  // 元素总数
  size_t size() const { return element_count; }
};

// 测试用例
int main() {
  SimpleHashMap<std::string, int> scores;

  // 插入测试
  scores.insert("Alice", 95);
  scores.insert("Bob", 85);

  // 更新测试
  scores["Bob"] = 88;  // operator[] 更新值

  // 自动扩容测试（多次插入触发rehash）
  for (int i = 0; i < 100; ++i) {
    scores.insert("User" + std::to_string(i), i);
  }

  // 查找测试
  if (auto ptr = scores.find("Alice")) {
    std::cout << "Alice: " << *ptr << std::endl;  // 95
  }

  // 删除测试
  scores.erase("Bob");
  std::cout << "find Bob: " << (scores.find("Bob") ? "Yes" : "No")
            << " (expect No)\n";

  // operator[] 测试（访问不存在的键）
  std::cout << "Charlie: " << scores["Charlie"] << std::endl;  // 默认构造0

  return 0;
}

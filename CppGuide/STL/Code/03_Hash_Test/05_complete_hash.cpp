#include <functional>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

template <class Key, class Value, class Hash = std::hash<Key>,
          class KeyEqual = std::equal_to<Key> >
class HashMap {
 private:
  // 桶中的节点
  struct Node {
    Key key;
    Value value;
    Node(const Key& k, const Value& v) : key(k), value(v) {}
  };

  using Bucket = std::list<Node>;  // 表示一个桶，支持链地址法解决哈希冲突
  std::vector<Bucket> buckets;     // 存储所有的桶
  size_t element_count = 0;        // 当前 hash 表中存储的元素数量
  float max_load_factor_ = 1.0;    // 最大负载因子，控制扩容的阈值
  Hash hasher;                     // hash 函数
  KeyEqual key_equal;              // key 比较函数

  // 获取键对应的桶索引
  size_t bucket_index(const Key& key) const {
    return hasher(key) % bucket_count();
  }

  // 触发扩容的负载因子阈值
  // 当负载因子超过最大值时，自动扩容并重新分配元素
  bool need_rehash() const { return load_factor() > max_load_factor_; }

  // 实际扩容逻辑
  void rehash(size_t new_bucket_count) {
    if (new_bucket_count < bucket_count()) return;

    // 当负载因子超过最大值时，自动扩容并重新分配元素
    std::vector<Bucket> new_buckets(new_bucket_count);
    for (auto& bucket : buckets) {
      for (auto& node : bucket) {
        // 获得新桶的索引
        size_t new_index = hasher(node.key) % new_bucket_count;
        // std::list::splice 是 std::list
        // 提供的一个高效操作，用于将一个链表的部分或全部元素移动到另一个链表中，而无需拷贝或重新分配内存
        // splice(pos, other, it)
        // pos 表示目标链表中插入位置的迭代器， other 表示原链表，it
        // 表示原链表中要移动元素的迭代器 splice
        // 是常数时间复杂度的操作，因为它只修改链表的指针，而不会拷贝或重新分配节点
        // 每次移动后，bucket.begin()
        // 会指向下一个节点，因此通过循环可以逐个移动所有节点 因此可以将 bucket
        // 这个桶中所有节点移动到新桶对应的桶号中
        new_buckets[new_index].splice(new_buckets[new_index].end(), bucket,
                                      bucket.begin());
      }
    }
    // 将旧的桶数组 buckets 与新的桶数组 new_buckets 进行交换
    // swap 只交换两个 std::vector
    // 的内部指针，而不会拷贝或重新分配元素，因此时间复杂度为 O(1)
    // 交换之后：buckets 指向新桶数组，哈希表的内部结构更新为扩容后的状态；
    // new_buckets 在交换后指向旧的桶数组，当 new_buckets
    // 离开作用域时，旧桶数组会被自动销毁，释放内存
    buckets.swap(new_buckets);
  }

 public:
  // 迭代器定义
  class iterator {
    using BucketIterator = typename Bucket::iterator;
    // 当前桶的迭代器，指向 buckets 中的某个桶
    typename std::vector<Bucket>::iterator bucket_it;
    // 指向桶数组 buckets 的末尾，用于判断是否遍历结束
    typename std::vector<Bucket>::iterator bucket_end;
    // 当前桶中的迭代器，指向桶中的某个节点
    BucketIterator node_it;

    void find_next_valid() {  // 跳过空桶，直到返回下一个非空桶的第一个节点
      // 当前桶中节点的迭代器等于当前桶中的尾后节点，则桶向后移动
      // 也就是要移动到下一个非空桶，然后返回这个非空桶的第一个节点
      while (bucket_it != bucket_end) {
        if (node_it == bucket_it->end()) {
          ++bucket_it;
          if (bucket_it != bucket_end) {
            node_it = bucket_it->begin();
          } else {
            node_it = BucketIterator();  // 标记为结束状态
            break;
          }
        } else {
          break;
        }
      }
      // while (node_it == bucket_it->end()) {
      //   if (++bucket_it == bucket_end) break;
      //   node_it = bucket_it->begin();
      // }
    }

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<const Key&, Value&>;  // 当前节点的键值对
    using difference_type = ptrdiff_t;

    iterator(typename std::vector<Bucket>::iterator b_it,
             typename std::vector<Bucket>::iterator b_end)
        : bucket_it(b_it), bucket_end(b_end) {
      // 如果当前桶不是空桶，则初始化 node_it 为当前桶的链表起始位置
      if (bucket_it != bucket_end) {
        node_it = bucket_it->begin();
        // 跳过空桶，找到第一个有效节点
        find_next_valid();
      } else {
        node_it = BucketIterator();  // 明确初始化结束迭代器
      }
    }

    // 解引用迭代器，返回当前节点的键值对
    value_type operator*() { return {node_it->key, node_it->value}; }

    // 前置递增操作，将迭代器移动到下一个节点
    iterator& operator++() {
      // 先将 node_it 移动到当前桶链表的下一个节点
      ++node_it;
      // 如果当前桶链表遍历完，则跳到下一个非空桶的第一个节点
      find_next_valid();
      // 返回自身，以支持链式调用
      return *this;
    }

    // 判断两个迭代器是否不相等
    bool operator!=(const iterator& other) const {
      return bucket_it != other.bucket_it || node_it != other.node_it;
    }
  };

  // 构造函数
  explicit HashMap(size_t initial_buckets = 11, const Hash& hash = Hash(),
                   const KeyEqual& equal = KeyEqual())
      : buckets(initial_buckets), hasher(hash), key_equal(equal) {}

  // 元素数量
  size_t size() const { return element_count; }

  // 桶数量
  size_t bucket_count() const { return buckets.size(); }

  // 负载因子
  float load_factor() const {
    // 负载因子 = 元素数量 /
    // 桶数量，元素数量表示哈希表中键值对的个数，桶数量为桶大小
    // 负载因子越高，说明每个桶中存储的元素越多，冲突的概率越大，查找、插入和删除操作的性能可能会下降
    // 负载因子越低，说明哈希表中有更多空桶，冲突概率较低，但可能浪费内存
    return static_cast<float>(size()) / bucket_count();
  }

  // 设置最大负载因子
  void max_load_factor(float ml) {
    if (ml <= 0) throw std::invalid_argument("Invalid max load factor");
    max_load_factor_ = ml;
  }

  // 插入元素
  std::pair<iterator, bool> insert(const Key& key, const Value& value) {
    // 当负载因子超过最大值时，自动扩容并重新分配元素
    if (need_rehash()) {
      rehash(bucket_count() * 2 + 1);
    }

    size_t index = bucket_index(key);  // 计算键的哈希值并取模，找到对应的桶索引
    // 遍历该桶的链表，检查是否存在相同的键
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
      if (key_equal(it->key, key)) {  // 存在相同的键，插入失败
        return {iterator(buckets.begin() + index, buckets.end()), false};
      }
    }

    // 键不存在，则将键值对追加到链表尾部
    // 冲突解决方法：链地址法（每个桶是一个链表）
    buckets[index].emplace_back(key, value);
    ++element_count;
    return {iterator(buckets.begin() + index, buckets.end()), true};
  }

  // 查找元素
  iterator find(const Key& key) {
    size_t index = bucket_index(key);  // 计算键的哈希值并取模，找到对应的桶索引
    // 遍历该桶的链表，逐一比较键，找到匹配的节点
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
      if (key_equal(it->key, key)) {
        return iterator(buckets.begin() + index, buckets.end());
      }
    }
    // 没找到 key 对应的 value 值，返回尾后节点
    return end();
  }

  // 删除元素
  size_t erase(const Key& key) {
    size_t index = bucket_index(key);  // 计算键的哈希值并取模，找到对应的桶索引
    // 遍历该桶的链表，找到匹配的节点并将其删除
    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
      if (key_equal(it->key, key)) {
        buckets[index].erase(it);
        --element_count;
        return 1;
      }
    }
    return 0;
  }

  // 访问元素（若不存在则插入默认值）
  Value& operator[](const Key& key) {
    auto it = find(key);
    if (it != end()) {
      return (*it).second;
    }
    auto result = insert(key, Value());
    return (*result.first).second;
  }

  // 迭代器
  iterator begin() { return iterator(buckets.begin(), buckets.end()); }
  iterator end() { return iterator(buckets.end(), buckets.end()); }
};

// 测试用例
int main() {
  HashMap<std::string, int> scores;

  // 插入数据
  scores.insert("Alice", 90);
  scores.insert("Bob", 85);
  scores["Charlie"] = 95;  // 使用operator[]

  // 查找测试
  if (auto it = scores.find("Bob"); it != scores.end()) {
    std::cout << "Bob's score: " << (*it).second << std::endl;  // 85
  }

  // 更新测试
  scores["Bob"] = 88;
  std::cout << "Updated Bob's score: " << scores["Bob"] << std::endl;

  // 删除测试
  scores.erase("Alice");
  std::cout << "After deletion, Alice exists? "
            << (scores.find("Alice") != scores.end() ? "Yes" : "No")
            << std::endl;

  // 遍历测试
  std::cout << "\nAll entries:" << std::endl;
  for (auto&& [key, value] : scores) {
    std::cout << key << ": " << value << std::endl;
  }

  return 0;
}

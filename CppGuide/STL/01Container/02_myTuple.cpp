#include <iostream>
#include <string>
#include <utility>

// tuple_end 是一个空类，表示元组的结束
struct tuple_end {};

// tuple_impl 是一个递归的模板类，用于存储元组的元素
template <std::size_t Index, typename Head, typename... Tail>
struct tuple_impl : tuple_impl<Index + 1, Tail...> {
  Head value;

  tuple_impl() = default;

  tuple_impl(Head&& v, Tail&&... tail)
      : tuple_impl<Index + 1, Tail...>(std::forward<Tail>(tail)...),
        value(std::forward<Head>(v)) {}

  Head& get_value(std::integral_constant<std::size_t, Index>) { return value; }

  const Head& get_value(std::integral_constant<std::size_t, Index>) const {
    return value;
  }
};

// 特化：递归基，当没有更多元素时使用 tuple_end
template <std::size_t Index>
struct tuple_impl<Index, tuple_end> {
  tuple_impl() = default;
};

// tuple 类，用于包装 tuple_impl
template <typename... Types>
struct tuple : tuple_impl<0, Types..., tuple_end> {
  tuple() = default;

  explicit tuple(Types&&... args)
      : tuple_impl<0, Types..., tuple_end>(std::forward<Types>(args)...) {}

  template <std::size_t N>
  decltype(auto) get() const {
    return this->get_value(std::integral_constant<std::size_t, N>{});
  }

  template <std::size_t N>
  decltype(auto) get() {
    return this->get_value(std::integral_constant<std::size_t, N>{});
  }
};

// 辅助函数模板，用于简化 get 函数的使用
template <std::size_t N, typename... Types>
decltype(auto) get(const tuple<Types...>& t) {
  return t.template get<N>();
}

template <std::size_t N, typename... Types>
decltype(auto) get(tuple<Types...>& t) {
  return t.template get<N>();
}

// 重载 == 运算符
template <typename... T1, typename... T2>
bool operator==(const tuple<T1...>& t1, const tuple<T2...>& t2) {
  return (get<0>(t1) == get<0>(t2)) && (get<1>(t1) == get<1>(t2)) &&
         (get<2>(t1) == get<2>(t2));
}

// 重载 < 运算符
template <typename... T1, typename... T2>
bool operator<(const tuple<T1...>& t1, const tuple<T2...>& t2) {
  return (get<0>(t1) < get<0>(t2)) ||
         (!(get<1>(t2) < get<1>(t1)) && (get<1>(t1) < get<1>(t2))) ||
         (!(get<2>(t2) < get<2>(t1)) && (get<2>(t1) < get<2>(t2)));
}

// tuple_cat 实现，用于连接两个 tuple
template <typename... T1, typename... T2>
auto tuple_cat(const tuple<T1...>& t1, const tuple<T2...>& t2) {
  return tuple<T1..., T2...>(get<0>(t1), get<1>(t1), get<2>(t1), get<0>(t2),
                             get<1>(t2), get<2>(t2));
}

int main() {
  tuple<int, double, std::string> t1(1, 2.5, "Hello");
  tuple<int, double, std::string> t2(3, 4.5, "World");

  auto t3 = tuple_cat(t1, t2);

  std::cout << "t1: " << get<0>(t1) << ", " << get<1>(t1) << ", " << get<2>(t1)
            << "\n";
  std::cout << "t2: " << get<0>(t2) << ", " << get<1>(t2) << ", " << get<2>(t2)
            << "\n";
  std::cout << "t3: " << get<0>(t3) << ", " << get<1>(t3) << ", " << get<2>(t3)
            << ", " << get<3>(t3) << ", " << get<4>(t3) << ", " << get<5>(t3)
            << "\n";

  return 0;
}

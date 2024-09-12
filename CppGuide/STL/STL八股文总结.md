留个坑，以后可以学习：
https://github.com/Alinshans/MyTinySTL/tree/master

[STL详解及常见面试题](https://blog.csdn.net/daaikuaichuan/article/details/80717222)

[C++面试-STL篇，细节有点多](https://zhuanlan.zhihu.com/p/614287445)

[C++ STL面试题](https://blog.csdn.net/weixin_46645965/article/details/136228103)

[60道C++STL高频题整理（附答案背诵版）](https://blog.csdn.net/tailonh/article/details/139308471)

# 一、大根堆、小根堆

>https://xiaoneng.blog.csdn.net/article/details/103206628

**`std::priority_queue` 的构建逻辑**

`std::priority_queue` 的底层实现依赖于堆（通常是用 `std::vector` 实现的二叉堆）。关键在于，优先队列是通过一个比较函数来决定元素的优先级的，而这个比较函数决定了堆中元素的排列方式。

1. **大根堆** (`std::less`)：
   - 默认的比较器是 `std::less<T>`。对于两个元素 `a` 和 `b`，`std::less` 的意思是“如果 `a < b` 为真，则 `a` 的优先级低于 `b`”。**这里总结一下：使用 less 就表示小的元素优先级低，在队列后面，大的元素优先级高，在队列前面，所以使用 less 表示的就是大根堆。**
   - 在构建堆时，较大的元素会被放到前面（即堆顶），因为它的优先级更高。因此，默认的优先队列是大根堆。
2. **小根堆** (`std::greater`)：
   - 当使用 `std::greater<T>` 作为比较器时，意思是“如果 `a > b` 为真，则 `a` 的优先级低于 `b`”。**这里总结一下：使用 greater 就表示大的元素优先级低，在队列后面，小的元素优先级高，在队列前面，所以使用 greater 表示的就是小根堆。**
   - 在构建堆时，较小的元素会被放到前面（即堆顶），因为它的优先级更高。因此，这样的优先队列是小根堆。
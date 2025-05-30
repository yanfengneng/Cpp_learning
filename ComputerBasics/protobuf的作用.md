- [一、概念](#一概念)

# 一、概念

**三种数据交互格式的对比：**

* `JSON`：是一种**用于 Web 应用程序中传递消息的消息传递格式**。与 XML 相比，JSON 是人类可读的、高效的且易于使用的。NodeJS 等后端框架、Chrome 等客户端应用程序也支持原生的 JSON，这使得 JSON 序列化和反序列化在 JavaScript 环境中快速应用。
* `XML`：在 `WebService` 中应用的比较多，相比于 JSON，XML 的数据更加冗余。**XML 需要成对的闭合标签，而 JSON 使用了键值对的方式，不仅压缩了一定的数据空间，同时也有更好的可读性**。
* `Protobuf`：是谷歌开发的一种数据格式，适合高性能，对响应速度有要求的数据传输场景。因为 **`Protobuf` 是二进制格式的数据，需要编码和解码。其数据本身不具有可读性，因此只能反序列化得到可读数据**。

****

**`Protobuf` 的优势**：

* **效率高**：`Protobuf` 以二进制格式存储数据，比 XML 和 JSON 等数据格式更紧凑、也更快。序列化与分序列化的速度快，比 JSON 的处理速度快。
* **清晰的结构定义**：使用 `Protobuf`，可以清晰地定义数据的结构，这有助于维护和理解。
* **向后兼容性**：可以添加或删除字段，但不会破坏老的应用程序。这对于长期维护的项目来说是非常有价值的。
* **跨语言支持**：`Protobuf` 支持多种编程语言，包括 C++、Java、Python 等。

**缺点：**

* **不直观**：由于 `Protobuf` 是二进制格式，人不能直接阅读和修改它。这对于调试和测试来说可能会有些困难。
* **缺乏一些数据类型**：没有内建的日期、时间类型，对于这些类型的数据，需要手动转换成可以支持的类型，如 string 或 int。
* **需要额外的编译步骤**：首先需要定义数据结构，然后使用 `protobuf` 的编译器将其编译成目标语言的代码，这是一个额外的步骤，可能会影响开发流程。

总的来说，`Protobuf` 是一个强大而高效的数据序列化工具，一方面我们看重它的性能以及兼容性，除此之外就是它强制要求清晰的定义出来，以文件的形式呈现出来方便我们进行维护与管理。


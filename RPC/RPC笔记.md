- [一、Protobuf](#一protobuf)
- [二、本地过程调用](#二本地过程调用)
- [三、远程过程调用](#三远程过程调用)

[谁能用通俗的语言解释一下什么是 RPC 框架？](https://www.zhihu.com/question/25536695/answer/221638079)



# 一、Protobuf

>[Protobuf 教程：基于C++](https://blog.csdn.net/baidu_32237719/article/details/99956972)

## 1.1 基本概念

**Protocol Buffers (protobuf)** 是一种由 Google 开发的数据序列化协议，用于在不同服务之间高效地交换结构化数据。**protobuf 使用二进制格式，提供了一种语言中立、平台中立的方式来定义和序列化数据结构**。相比于 JSON 和 XML，protobuf 通常具有更小的消息体和更快的序列化/反序列化速度。

**Q1：protobuf 相比 JSON、XML 有什么优缺点？**

优点：

* **高效性**：protobuf 使用二进制格式，消息体通常比 JSON 或 XML 更小，序列化和反序列化速度更快。

* **强类型**：protobuf 使用明确的类型系统，减少了因类型不匹配导致的错误。

* **自动生成代码**：protobuf 可以自动生成多种编程语言的代码，简化了跨语言的数据交换。

* **版本兼容性**：支持向前和向后兼容，允许在保留旧版本兼容性的情况下扩展消息格式。

缺点：

* **可读性差**：由于使用二进制格式，protobuf 消息不如 JSON 或 XML 那样易于人类阅读和调试。

* **复杂性**：使用 protobuf 需要定义 `.proto` 文件并进行编译，增加了一些开发和构建的复杂性。

* **无元数据**：protobuf 消息中不包含字段的元数据（如字段名称），可能在调试时不如 JSON 方便。

**Q2：protobuf 如何实现高效的序列化？**

* protobuf 使用二进制编码格式，避免了像 JSON 和 XML 那样的冗余标签。**每个字段使用一个唯一的字段号进行标识，并采用了可变长度的编码方式，使得数字等常见数据类型能够以较少的字节表示**。这种紧凑的编码方式大幅减少了数据的体积，提升了序列化和反序列化的速度。

**Q3：如何在 protobuf 中实现向后兼容性？**

* **保留旧字段**：旧字段不会被删除，而是标记为 `optional`（可选）。
* **添加新字段**：可以向消息添加新的字段，只要不使用已经存在的字段号即可。未识别的字段将被忽略，但在反序列化后仍然保留，保证向后兼容性。
* **移除字段**：如果字段不再需要，可以将其标记为废弃（deprecate），但不应完全删除以避免破坏旧的客户端。

***

**`optional`**：字段是可选的，可以不出现在消息中。如果没有提供，则采用默认值。Proto3 默认所有字段都是 `optional`。

**`required`**：字段是必需的，必须出现在消息中。Proto3 中不再支持 `required` 字段，因其强制性可能导致难以保持向后兼容性。

**`repeated`**：表示一个字段可以出现多次，通常用于数组或列表。

```protobuf
syntax = "proto2";

package tutorial;

message Person {
  required string name = 1;
  required int32 id = 2;
  optional string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    required string number = 1;
    optional PhoneType type = 2 [default = HOME];
  }

  repeated PhoneNumber phones = 4;
}

message AddressBook {
  repeated Person people = 1;
}
```

## 1.2 序列化与反序列化

**序列化函数：**

* `bool SerializeToString(string* output) const;`：序列化消息并将字节存储在给定的字符串中。注意，字节是二进制的，而不是文本；我们只使用字符串类作为方便的容器。
* `bool SerializeToOstream(ostream* output) const;`：将消息写入给定的 C++ 的`ostream`。
* `bool SerializeToArray(void* data, int size) const;`：将消息序列化为原始字节数组。

**反序列化函数：**

* `bool ParseFromString(const string& data);`：解析给定字符串中的消息。
* `bool ParseFromIstream(istream* input);`；从给定的 C++  的`istream`解析消息。
* `bool ParseFromArray(const void* data, int size);`：从原始字节数组中反序列化消息。

**额外功能：**

* `ByteSizeLong();`：返回序列化后的消息大小（以字节为单位）。
* `Clear();`：清除消息的所有字段，将消息重置为默认状态。
* `IsInitialized();`：检查消息的所有必需字段是否已初始化。



## 1.3 protobuf 的应用

gRPC 是一个基于 HTTP/2 协议的高性能 RPC 框架，它由 Google 开发，并且广泛使用 protobuf 作为其接口定义语言（IDL）和数据序列化格式。gRPC 依赖 protobuf 来定义服务和消息，并通过生成的代码实现跨语言的远程调用。

**gRPC 中 protobuf 的角色：**

- **定义接口**：使用 protobuf 来定义 RPC 服务接口。例如，在 `.proto` 文件中，你可以定义一个服务和其对应的方法：

  ```protobuf
  service Greeter {
    rpc SayHello (HelloRequest) returns (HelloReply);
  }
  
  message HelloRequest {
    string name = 1;
  }
  
  message HelloReply {
    string message = 1;
  }
  ```

  在这个例子中，`SayHello` 方法接受 `HelloRequest` 消息，并返回 `HelloReply` 消息。

- **生成代码**：通过 `protoc` 编译器，你可以从 `.proto` 文件生成相应语言的客户端和服务器代码，这些代码包含了服务接口和消息类的定义。客户端通过调用生成的代码与服务器通信，而服务器通过实现这些接口来处理客户端请求。

- **序列化和反序列化**：gRPC 使用 protobuf 来序列化客户端请求的数据，并将其通过网络发送到服务器。服务器接收到数据后，通过 protobuf 反序列化为消息对象，处理后再序列化响应消息返回客户端。

# 二、本地过程调用

RPC（Remote Procedure Call Protocal）：远程过程调用协议。

`RPC` 就是要像调用本地的函数一样去调远程函数 。在研究 `RPC` 前，先看看本地调用是怎么调的。假设要调用函数 `Multiply` 来计算 `Ivalue * rvalue`的结果:

```cpp
int Multiply(int l, int r) {
   int y = l * r;
   return y;
}
 
int lvalue = 10;
int rvalue = 20;
int l_times_r = Multiply(lvalue, rvalue);
```

在最后一行时，实际上执行了以下操作：

* 1）将 `lvalue` 和 `rvalue` 的值压栈；

* 2）进入Multiply函数，取出栈中的值10 和 20，将其赋予 l 和 r；

* 3）执行第2行代码，计算 l * r ，并将结果存在 y；

* 4）将 y 的值压栈，然后从 Multiply 返回；
* 5）最后一行，从栈中取出返回值 200 ，并赋值给 l_times_r；

以上5步就是执行本地调用的过程。



# 三、远程过程调用

在远程调用时，我们需要执行的函数体是在远程的机器上的，也就是说，Multiply是在另一个进程中执行的。这就带来了几个新问题：

1. **Call ID映射**。我们怎么告诉远程机器我们要调用 `Multiply`，而不是 `Add` 或者 `FooBar` 呢？在本地调用中，函数体是直接通过函数指针来指定的，我们调用 `Multiply`，编译器就自动帮我们调用它相应的函数指针。但是在远程调用中，函数指针是不行的，因为两个进程的地址空间是完全不一样的。所以在 `RPC` 中所有的函数都必须有自己的一个ID。这个ID在所有进程中都是唯一确定的。客户端在做远程过程调用时，必须附上这个ID。然后我们还需要在客户端和服务端**分别维护一个 {函数 <--> Call ID} 的对应表**。两者的表不一定需要完全相同，但相同的函数对应的Call ID必须相同。当客户端需要进行远程调用时，它就查一下这个表，找出相应的Call ID，然后把它传给服务端，服务端也通过查表，来确定客户端需要调用的函数，然后执行相应函数的代码。
2. **序列化和反序列化**。客户端怎么把参数值传给远程的函数呢？在本地调用中，我们只需要把参数压到栈里，然后让函数自己去栈里读就行。但是在远程过程调用时，客户端跟服务端是不同的进程，不能通过内存来传递参数。甚至有时候客户端和服务端使用的都不是同一种语言（比如服务端用C++，客户端用Java或者Python）。这时候就需要客户端把参数先转成一个字节流，传给服务端后，再把字节流转成自己能读取的格式。这个过程叫序列化和反序列化。同理，从服务端返回的值也需要序列化反序列化的过程。
3. **网络传输**。远程调用往往用在网络上，客户端和服务端是通过网络连接的。所有的数据都需要通过网络传输，因此就需要有一个网络传输层。**网络传输层需要把Call ID和序列化后的参数字节流传给服务端，然后再把序列化后的调用结果传回客户端**。只要能完成这两者的，都可以作为传输层使用。因此，它所使用的协议其实是不限的，能完成传输就行。尽管大部分RPC框架都使用TCP协议，但其实UDP也可以，而gRPC干脆就用了HTTP2。Java的Netty也属于这层的东西。

有了以上三个机制，RPC 具体实现过程如下：

```cpp
// Client端 
//    int l_times_r = Call(ServerAddr, Multiply, lvalue, rvalue)
1. 将这个调用映射为Call ID。这里假设用最简单的字符串当Call ID的方法
2. 将Call ID，lvalue和rvalue序列化。可以直接将它们的值以二进制形式打包
3. 把2中得到的数据包发送给ServerAddr，这需要使用网络传输层
4. 等待服务器返回结果
5. 如果服务器调用成功，那么就将结果反序列化，并赋给l_times_r

// Server端
1. 在本地维护一个Call ID到函数指针的映射call_id_map，可以用std::map<std::string, std::function<>>
2. 等待请求
3. 得到一个请求后，将其数据包反序列化，得到Call ID
4. 通过在call_id_map中查找，得到相应的函数指针
5. 将lvalue和rvalue反序列化后，在本地调用Multiply函数，得到结果
6. 将结果序列化后通过网络返回给Client
```

所以要实现一个RPC框架，其实只需要按以上流程实现就基本完成了。

其中：

- Call ID映射可以直接使用函数字符串，也可以使用整数ID。映射表一般就是一个哈希表。
- 序列化反序列化可以自己写，也可以使用Protobuf或者FlatBuffers之类的。
- 网络传输库可以自己写 socket，或者用asio，ZeroMQ，Netty之类。

当然，这里面还有一些细节可以填充，比如如何处理网络错误，如何防止攻击，如何做流量控制，等等。但有了以上的架构，这些都可以持续加进去。


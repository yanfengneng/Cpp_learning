- [一、本地过程调用](#一本地过程调用)
- [二、远程过程调用](#二远程过程调用)

[谁能用通俗的语言解释一下什么是 RPC 框架？](https://www.zhihu.com/question/25536695/answer/221638079)

RPC（Remote Procedure Call Protocal）：远程过程调用协议。



# 一、本地过程调用

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



# 二、远程过程调用

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


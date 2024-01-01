#include<iostream>
#include <functional>
using namespace std;
 
using FuncCallback = std::function<void(void)>;
 
void DataCallback(FuncCallback callback)
{
	std::cout << "Start FuncCallback!" << std::endl;
	callback();
	std::cout << "End FuncCallback!" << std::endl;
}
 
static auto callback_handler = [](){
	std::cout << "This is callback_handler"<<endl;
    return 0;
}();

auto __ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cout << "hello world" << endl;
    return nullptr;
}();

vector<std::function<bool(int)>> vec;
void Func()
{
	srand((unsigned)time(nullptr));
	//产生0-5之间的随机数
	static int temp = 4;	//静态局部变量不需要被捕获，也捕获不到
	vec.push_back([](auto v) {
		cout << temp << endl;
		if (v % temp == 0)
		{
			return true;
		}
		return false;
		});
	temp++;
}

int main(int argc, const char* argv[]) 
{
	Func();
	cout << vec[0](10) << endl;	//5,1
	
	return 0;
}
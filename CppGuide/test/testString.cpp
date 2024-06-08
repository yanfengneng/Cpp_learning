#include <iostream>
#include <string>
#include <bits/stdc++.h>

const char* getSomeStrByCStr() {
    std::string str = "Hello, world!";
    char* c_str = new char[str.size() + 1];

    std::strcpy(c_str, str.c_str());
    return c_str;
}

int main() {
    const char* str_c_str = getSomeStrByCStr();

    std::cout << "Get by c_str(): addr: " << (void*)str_c_str << ", content: " << str_c_str << std::endl;

    // Remember to free the allocated memory
    delete[] str_c_str;

    return 0;
}


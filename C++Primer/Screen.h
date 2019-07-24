#pragma once
#include <string>

class Screen {
public:
	//使用类型别名等价地声明一个类型名字
	//using pos = std::string::size_type;
	typedef std::string::size_type pos;
	Screen() = default; //因为 Screen 有另外一个构造函数，所以本函数是必须的
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht* wd, c) { };
	char get() const {						//读取光标处的字符
		return contents[cursor];			//隐式内联	
	}
	inline char get(pos ht, pos wd) const;	//显式内联
	Screen& move(pos r, pos c);				//能在之后被设为内联
	void some_member() const;
	Screen& set(char);
	Screen& set(pos, pos, char);
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable size_t access_ctr = 0;	//即使在一个 const 对象内也能被修改
};


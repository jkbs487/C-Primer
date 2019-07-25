/*
			动态内存管理类（C++primer p.464）
	一个只用于 string ，不使用模板的标准库 vector 的简化版本

	-------------------------------------
	| 0 | 1 | 2 | 3 | 4 |  未构造的元素  |
	-------------------------------------
	|                    |               |       
 element             first_free         cap

*/

#pragma once
#include <string>
#include <memory>
#include <utility>

static std::allocator<std::string> alloc;//分配元素
//表 vector 类内存分配策略的简化实现
class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){ };
	StrVec(std::initializer_list<std::string> il);
	//拷贝构造函数
	StrVec(const StrVec&);
	//移动拷贝构造函数
	StrVec(StrVec&& s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap) {
		s.elements = s.first_free = s.cap = nullptr;
	}
	//赋值运算符重载
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	std::string operator[](std::size_t);
	~StrVec();
	void push_back(const std::string&);	//拷贝元素
	void push_back(std::string&&);		//移动元素
	std::size_t size() const{ return first_free - elements; }
	std::size_t capacity() { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
	void reserve(std::size_t n);
	void resize(std::size_t n);
	bool empty() { return (elements == first_free); }
private:
	void chk_n_alloc() { if (size() == capacity()) reallocate();}
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();		//销毁元素并释放内存
	void reallocate();	//获得更多内存并拷贝已有元素
	std::string* elements;	//指向数组首元素的指针
	std::string* first_free;	//指向数组第一个空闲元素的指针
	std::string* cap;		//指向数组尾后位置的指针
};


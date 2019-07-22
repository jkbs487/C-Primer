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
using namespace std;
//表 vector 类内存分配策略的简化实现
class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){ };
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	~StrVec();
	void push_back(const string&);
	size_t size() const{
		return first_free - elements;
	}
	size_t capacity() {
		return cap - elements;
	}
	string* begin() const {
		return elements;
	}
	string* end() const {
		return first_free;
	}
private:
	static allocator<string> alloc;//分配元素
	void chk_n_alloc() {
		if (size() == capacity())
			reallocate();
	}
	pair<string*, string*> alloc_n_copy(const string*, const string*);
	void free();		//销毁元素并释放内存
	void reallocate();	//获得更多内存并拷贝已有元素
	string* elements;	//指向数组首元素的指针
	string* first_free;	//指向数组第一个空闲元素的指针
	string* cap;		//指向数组尾后位置的指针
};


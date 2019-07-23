#include "strVec.h"

void StrVec::push_back(const string& s) {
	chk_n_alloc();	//确保有空间容纳新元素
	//在 first_free 指向的元素中构造 s 的副本
	alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
	//分配空间保存给定范围中的元素
	auto data = alloc.allocate(e - b);
	//初始化并返回一个 pair，该 pair 由 data 和 unitialized_copy 的返回值构成
	return { data, uninitialized_copy(b, e, data) };
}

void StrVec::free() {
	//不能传递给 deallocate 一个空指针，如果 elements 为 0，函数什么也不做
	if (elements) {
		//逆序销毁元素
		for (auto p = first_free; p != elements;) {
			alloc.destroy(--p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec& s) {
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() {
	free();
}

StrVec& StrVec::operator=(const StrVec& rhs) {
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
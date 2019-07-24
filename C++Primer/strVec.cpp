/*
			动态内存管理类（C++primer p.464）
	一个只用于 string ，不使用模板的标准库 vector 的简化版本

	-------------------------------------
	| 0 | 1 | 2 | 3 | 4 |  未构造的元素  |
	-------------------------------------
	|                    |               |
 element             first_free         cap

*/

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
	//调用 alloc_n_copy 分配内存，大小与 rhs 中元素占用空间一样多
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); i++) {
		alloc.construct(dest++, std::move(*elem++));
	}
	//还可以使用移动迭代器移动元素
	//auto first = alloc.allocate(newcapacity);
	//auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
void StrVec::reserve(size_t n) {
	//只有 reserve 的空间大于总容量的时候才执行
	if (n > capacity()) {
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto elem = elements;
		//将原先空间的元素移动到新分配的空间
		for (size_t i = 0; i != size(); i++) {
			alloc.construct(dest++, move(*elem++));
		}
		free();				//释放原先的空间
		elements = newdata;
		first_free = dest;
		cap = elements + n;
	}
	return;
}

void StrVec::resize(size_t n) {
	// resize 的空间大于元素已使用空间的情况
	if (n > size() && n <= capacity()) {
		auto m = n - size();
		for (size_t i = 0; i != m; i++)
			//构造多余出的空间
			alloc.construct(first_free++);
	}
	// resize 的空间小于元素已使用空间的情况
	else if (n < size()) {
		auto m = size() - n;
		for (size_t i = 0; i != m; i++) {
			//销毁不需要的空间
			alloc.destroy(--first_free);
		}
	}
	return;
}

string StrVec::operator[](size_t n) {
	return *(elements + n);
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
	//检测自赋值
	if (this != &rhs) {
		free();			//释放已有元素
		//从 rhs 接管资源
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		//将 rhs 置于可析构状态
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::push_back(string&& s) {
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}
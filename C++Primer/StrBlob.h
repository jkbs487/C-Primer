/*
				动态内存示例（p.404）
	一个通过动态内存来管理的简单 string 标准库容器
*/
#pragma once
#include <string>
#include <vector>
#include <memory>

class StrBlobPtr;
class StrBlob {
	typedef std::vector<std::string>::size_type size_type;
	friend class StrBlobPtr;
public:
	StrBlob() : data(std::make_shared<std::vector<std::string>>()) { };
	StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { };
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string& t) { data->push_back(t); }
	void pop_back();
	//元素访问
	std::string& front();
	std::string& back();
	//重载 const 版本
	const std::string& front() const;
	const std::string& back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	//如果 data[i] 不合法，抛出一个异常
	void check(size_type i, const std::string& msg) const;
};

class StrBlobPtr {
public:
	StrBlobPtr() : curr(0) { }
	StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) { }
	std::string& deref() const;
	StrBlobPtr& incr();//前缀递增
	//递增和递减运算符（前置版本）
	StrBlobPtr& operator++();
	StrBlobPtr& operator--();
	//递增和递减运算符（后置版本）
	StrBlobPtr operator++(int);
	StrBlobPtr operator--(int);
private:
	//若检查成功，check 返回一个指向 vector 的 shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	//保存一个 weak_ptr，意味着底层 vector 可能会被销毁
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;	//在数组中的当前位置
};
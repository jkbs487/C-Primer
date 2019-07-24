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
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
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
	StrBlobPtr begin() { return StrBlobPtr(*this); }
	StrBlobPtr end() { 
		auto ret = StrBlobPtr(*this, data->size());
		return ret; 
	}
private:
	std::shared_ptr<std::vector<std::string>> data;
	//如果 data[i] 不合法，抛出一个异常
	void check(size_type i, const std::string& msg) const;
};


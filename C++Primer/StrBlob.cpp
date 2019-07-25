#include "StrBlob.h"
#include <stdexcept>

void StrBlob::check(size_type i, const std::string& msg) const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}

std::string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

const std::string& StrBlob::front() const {
	check(0, "front on empty StrBlob");
	return data->front();
}

const std::string& StrBlob::back() const {
	check(0, "back on empty StrBlob");
	return data->back();
}

StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string& msg) const {
	auto ret = wptr.lock();	//vector 是否还存在 
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;	//否则，返回指向 vector 的 shared_ptr
}

std::string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];	//(*p)是对象所指向的 vector
}

StrBlobPtr& StrBlobPtr::incr() {
	//如果 curr 已经指向容器的尾后位置，就不能递增它
	auto p = check(curr, "increment past end of StrBlobPtr");
	++curr;			//推进当前位置
	return *this;
}

StrBlobPtr& StrBlobPtr::operator++() {
	auto p = check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlobPtr& StrBlobPtr::operator--() {
	--curr;
	auto p = check(curr, "increment past begin of StrBlobPtr");
	return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
	StrBlobPtr ret = *this;
	++*this;
	return *this;
}

StrBlobPtr StrBlobPtr::operator--(int) {
	StrBlobPtr ret = *this;
	--*this;
	return *this;
}
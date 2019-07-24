#include "StrBlobPtr.h"
#include <stdexcept>

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


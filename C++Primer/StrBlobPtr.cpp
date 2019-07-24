#include "StrBlobPtr.h"
#include <stdexcept>

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string& msg) const {
	auto ret = wptr.lock();	//vector �Ƿ񻹴��� 
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;	//���򣬷���ָ�� vector �� shared_ptr
}

std::string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];	//(*p)�Ƕ�����ָ��� vector
}

StrBlobPtr& StrBlobPtr::incr() {
	//��� curr �Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
	auto p = check(curr, "increment past end of StrBlobPtr");
	++curr;			//�ƽ���ǰλ��
	return *this;
}


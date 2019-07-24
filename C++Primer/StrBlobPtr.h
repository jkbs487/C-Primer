/*
				动态内存示例（p.404）
	作为StrBlob类的伴随指针类，为了展示week_ptr的作用
*/
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "StrBlob.h"

class StrBlobPtr {
public:
	StrBlobPtr() : curr(0) { }
	StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) { }
	std::string& deref() const;
	StrBlobPtr& incr();//前缀递增
private:
	//若检查成功，check 返回一个指向 vector 的 shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	//保存一个 weak_ptr，意味着底层 vector 可能会被销毁
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;	//在数组中的当前位置
};


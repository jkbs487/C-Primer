/*
				��̬�ڴ�ʾ����p.404��
	��ΪStrBlob��İ���ָ���࣬Ϊ��չʾweek_ptr������
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
	StrBlobPtr& incr();//ǰ׺����
private:
	//�����ɹ���check ����һ��ָ�� vector �� shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	//����һ�� weak_ptr����ζ�ŵײ� vector ���ܻᱻ����
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;	//�������еĵ�ǰλ��
};


#include "strVec.h"

void StrVec::push_back(const string& s) {
	chk_n_alloc();	//ȷ���пռ�������Ԫ��
	//�� first_free ָ���Ԫ���й��� s �ĸ���
	alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e) {
	//����ռ䱣�������Χ�е�Ԫ��
	auto data = alloc.allocate(e - b);
	//��ʼ��������һ�� pair���� pair �� data �� unitialized_copy �ķ���ֵ����
	return { data, uninitialized_copy(b, e, data) };
}

void StrVec::free() {
	//���ܴ��ݸ� deallocate һ����ָ�룬��� elements Ϊ 0������ʲôҲ����
	if (elements) {
		//��������Ԫ��
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
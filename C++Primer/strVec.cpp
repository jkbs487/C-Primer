/*
			��̬�ڴ�����ࣨC++primer p.464��
	һ��ֻ���� string ����ʹ��ģ��ı�׼�� vector �ļ򻯰汾

	-------------------------------------
	| 0 | 1 | 2 | 3 | 4 |  δ�����Ԫ��  |
	-------------------------------------
	|                    |               |
 element             first_free         cap

*/

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
	//���� alloc_n_copy �����ڴ棬��С�� rhs ��Ԫ��ռ�ÿռ�һ����
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
		alloc.construct(dest++, move(*elem++));
	}
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
void StrVec::reserve(size_t n) {
	if (n > capacity()) {
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto elem = elements;
		for (size_t i = 0; i != size(); i++) {
			alloc.construct(dest++, move(*elem++));
		}
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + n;
	}
	return;
}

void StrVec::resize(size_t n) {
	if (n > size() && n <= capacity()) {
		auto m = n - size();
		for (size_t i = 0; i != m; i++)
			alloc.construct(first_free++);
	//	first_free = elements + n;
	}
	else if (n < size()) {
		auto m = size() - n;
		for (size_t i = 0; i != m; i++) {
			alloc.destroy(--first_free);
		}
	//	first_free = elements + n;
	}
	return;
}

string StrVec::operator[](size_t n) {
	return *(elements + n);
}
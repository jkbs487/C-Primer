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
		alloc.construct(dest++, std::move(*elem++));
	}
	//������ʹ���ƶ��������ƶ�Ԫ��
	//auto first = alloc.allocate(newcapacity);
	//auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
void StrVec::reserve(size_t n) {
	//ֻ�� reserve �Ŀռ������������ʱ���ִ��
	if (n > capacity()) {
		auto newdata = alloc.allocate(n);
		auto dest = newdata;
		auto elem = elements;
		//��ԭ�ȿռ��Ԫ���ƶ����·���Ŀռ�
		for (size_t i = 0; i != size(); i++) {
			alloc.construct(dest++, move(*elem++));
		}
		free();				//�ͷ�ԭ�ȵĿռ�
		elements = newdata;
		first_free = dest;
		cap = elements + n;
	}
	return;
}

void StrVec::resize(size_t n) {
	// resize �Ŀռ����Ԫ����ʹ�ÿռ�����
	if (n > size() && n <= capacity()) {
		auto m = n - size();
		for (size_t i = 0; i != m; i++)
			//���������Ŀռ�
			alloc.construct(first_free++);
	}
	// resize �Ŀռ�С��Ԫ����ʹ�ÿռ�����
	else if (n < size()) {
		auto m = size() - n;
		for (size_t i = 0; i != m; i++) {
			//���ٲ���Ҫ�Ŀռ�
			alloc.destroy(--first_free);
		}
	}
	return;
}

string StrVec::operator[](size_t n) {
	return *(elements + n);
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
	//����Ը�ֵ
	if (this != &rhs) {
		free();			//�ͷ�����Ԫ��
		//�� rhs �ӹ���Դ
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		//�� rhs ���ڿ�����״̬
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::push_back(string&& s) {
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}
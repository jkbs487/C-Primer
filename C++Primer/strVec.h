/*
			��̬�ڴ�����ࣨC++primer p.464��
	һ��ֻ���� string ����ʹ��ģ��ı�׼�� vector �ļ򻯰汾

	-------------------------------------
	| 0 | 1 | 2 | 3 | 4 |  δ�����Ԫ��  |
	-------------------------------------
	|                    |               |       
 element             first_free         cap

*/

#pragma once
#include <string>
#include <memory>
#include <utility>
using namespace std;
static allocator<string> alloc;//����Ԫ��
//�� vector ���ڴ������Եļ�ʵ��
class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){ };
	//�������캯��
	StrVec(const StrVec&);
	//�ƶ��������캯��
	StrVec(StrVec&& s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap) {
		s.elements = s.first_free = s.cap = nullptr;
	}
	//��ֵ���������
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	string operator[](size_t);
	~StrVec();
	void push_back(const string&);	//����Ԫ��
	void push_back(string&&);		//�ƶ�Ԫ��
	size_t size() const{
		return first_free - elements;
	}
	size_t capacity() {
		return cap - elements;
	}
	string* begin() const {
		return elements;
	}
	string* end() const {
		return first_free;
	}
	void reserve(size_t n);
	void resize(size_t n);
	bool empty() {
		return (elements == first_free);
	}
private:
	void chk_n_alloc() {
		if (size() == capacity())
			reallocate();
	}
	pair<string*, string*> alloc_n_copy(const string*, const string*);
	void free();		//����Ԫ�ز��ͷ��ڴ�
	void reallocate();	//��ø����ڴ沢��������Ԫ��
	string* elements;	//ָ��������Ԫ�ص�ָ��
	string* first_free;	//ָ�������һ������Ԫ�ص�ָ��
	string* cap;		//ָ������β��λ�õ�ָ��
};


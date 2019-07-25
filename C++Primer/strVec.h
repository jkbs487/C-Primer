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

static std::allocator<std::string> alloc;//����Ԫ��
//�� vector ���ڴ������Եļ�ʵ��
class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){ };
	StrVec(std::initializer_list<std::string> il);
	//�������캯��
	StrVec(const StrVec&);
	//�ƶ��������캯��
	StrVec(StrVec&& s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap) {
		s.elements = s.first_free = s.cap = nullptr;
	}
	//��ֵ���������
	StrVec& operator=(const StrVec&);
	StrVec& operator=(StrVec&&) noexcept;
	std::string operator[](std::size_t);
	~StrVec();
	void push_back(const std::string&);	//����Ԫ��
	void push_back(std::string&&);		//�ƶ�Ԫ��
	std::size_t size() const{ return first_free - elements; }
	std::size_t capacity() { return cap - elements; }
	std::string* begin() const { return elements; }
	std::string* end() const { return first_free; }
	void reserve(std::size_t n);
	void resize(std::size_t n);
	bool empty() { return (elements == first_free); }
private:
	void chk_n_alloc() { if (size() == capacity()) reallocate();}
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();		//����Ԫ�ز��ͷ��ڴ�
	void reallocate();	//��ø����ڴ沢��������Ԫ��
	std::string* elements;	//ָ��������Ԫ�ص�ָ��
	std::string* first_free;	//ָ�������һ������Ԫ�ص�ָ��
	std::string* cap;		//ָ������β��λ�õ�ָ��
};


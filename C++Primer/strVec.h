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
using namespace std;
//�� vector ���ڴ������Եļ�ʵ��
class StrVec {
public:
	StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr){ };
	StrVec(const StrVec&);
	StrVec& operator=(const StrVec&);
	~StrVec();
	void push_back(const string&);
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
private:
	static allocator<string> alloc;//����Ԫ��
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


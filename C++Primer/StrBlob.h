/*
				��̬�ڴ�ʾ����p.404��
	һ��ͨ����̬�ڴ�������ļ� string ��׼������
*/
#pragma once
#include <string>
#include <vector>
#include <memory>

class StrBlobPtr;
class StrBlob {
	typedef std::vector<std::string>::size_type size_type;
	friend class StrBlobPtr;
public:
	StrBlob() : data(std::make_shared<std::vector<std::string>>()) { };
	StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { };
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string& t) { data->push_back(t); }
	void pop_back();
	//Ԫ�ط���
	std::string& front();
	std::string& back();
	//���� const �汾
	const std::string& front() const;
	const std::string& back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	//��� data[i] ���Ϸ����׳�һ���쳣
	void check(size_type i, const std::string& msg) const;
};

class StrBlobPtr {
public:
	StrBlobPtr() : curr(0) { }
	StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) { }
	std::string& deref() const;
	StrBlobPtr& incr();//ǰ׺����
	//�����͵ݼ��������ǰ�ð汾��
	StrBlobPtr& operator++();
	StrBlobPtr& operator--();
	//�����͵ݼ�����������ð汾��
	StrBlobPtr operator++(int);
	StrBlobPtr operator--(int);
private:
	//�����ɹ���check ����һ��ָ�� vector �� shared_ptr
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	//����һ�� weak_ptr����ζ�ŵײ� vector ���ܻᱻ����
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;	//�������еĵ�ǰλ��
};
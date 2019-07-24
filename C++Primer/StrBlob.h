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
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
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
	StrBlobPtr begin() { return StrBlobPtr(*this); }
	StrBlobPtr end() { 
		auto ret = StrBlobPtr(*this, data->size());
		return ret; 
	}
private:
	std::shared_ptr<std::vector<std::string>> data;
	//��� data[i] ���Ϸ����׳�һ���쳣
	void check(size_type i, const std::string& msg) const;
};


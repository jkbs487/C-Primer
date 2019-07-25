#pragma once
#include <string>
#include <iostream>

class Screen {
public:
	//ʹ�����ͱ����ȼ۵�����һ����������
	//using pos = std::string::size_type;
	typedef std::string::size_type pos;
	Screen() = default; //��Ϊ Screen ������һ�����캯�������Ա������Ǳ����
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht* wd, c) { };
	char get() const {						//��ȡ��괦���ַ�
		return contents[cursor];			//��ʽ����	
	}
	inline char get(pos ht, pos wd) const;	//��ʽ����
	Screen& move(pos r, pos c);				//����֮����Ϊ����
	void some_member() const;
	Screen& set(char);
	Screen& set(pos, pos, char);
	//���ݶ����Ƿ��� const ������ display ����
	Screen& display(std::ostream& os) { do_display(os); return *this; }
	const Screen& display(std::ostream& os) const { do_display(os); return *this; }
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable size_t access_ctr = 0;	//��ʹ��һ�� const ������Ҳ�ܱ��޸�
	void do_display(std::ostream& os) const { os << contents; }
};


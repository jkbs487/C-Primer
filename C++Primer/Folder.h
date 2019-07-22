#pragma once
#include <set>
#include <iostream>
#include <string>
using namespace std;
class Message;

class Folder {
public:
	//messages ����ʽ��ʼ��Ϊ�ռ���
	explicit Folder(const string& name = ""): m_name(name) {};
	//Folder(const Folder&);
	//~Folder();
	string getName() {		//��ȡ�ļ�������
		return m_name;
	}
	void addMsg(Message*);
	void remMsg(Message*);
private:
	//void add_to_Msgs(const Folder&);
	//void remove_from_Msgs();
	set<Message*> messages;
	string m_name;
};


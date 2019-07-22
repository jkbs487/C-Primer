#pragma once
#include <set>
#include <iostream>
#include <string>
using namespace std;
class Message;

class Folder {
public:
	//messages 被隐式初始化为空集合
	explicit Folder(const string& name = ""): m_name(name) {};
	//Folder(const Folder&);
	//~Folder();
	string getName() {		//获取文件夹名称
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


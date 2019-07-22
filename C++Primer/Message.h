/*
					拷贝控制示例(C++Primer p.460)

	class Message(Message.h): 电子邮件（或者其他类型的消息）
		save(Folder&): 在指定文件夹保存本消息
		remove(Folder&): 在指定文件夹删除本消息
		print(): 打印本消息所在的所有文件夹名称
		add_to_Folders(const Message&): 将本消息添加到目标文件夹
		remove_from_Folders(): 从本消息所在的所有文件夹中删除本消息
	class Fold(Fold.h)：消息目录
		addMsg(): 本文件夹中增加给定的消息
		remMsg(): 从本文件夹中删除给定的消息
*/

#pragma once
#include<string>
#include<set>
#include <iostream>
#include "Folder.h"
using namespace std;

class Message {
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	//folders被隐式初始化为空集合
	explicit Message(const string& str = ""): contents(str) { }
	//拷贝控制成员，用来管理指向本 Message 的指针
	Message(const Message&);			//拷贝构造函数
	Message& operator=(const Message&);	//拷贝赋值运算符
	~Message();							//析构函数
	//从给定 Folder 集合中添加/删除本 Message
	void save(Folder&);
	void remove(Folder&);

	//void addFold(Folder*);
	//void remFold(Folder*);

	void print();
private:
	string contents;					//实际消息文本
	set <Folder*> folders;				//包含本 Message 的 Folder
	//拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
	//将本 Message 添加到指向参数的 Folder 中
	void add_to_Folders(const Message&);
	//从 folders 中的每个 Folder 中删除本 Message
	void remove_from_Folders();
};

void swap(Message&, Message&);
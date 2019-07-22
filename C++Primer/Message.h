/*
					��������ʾ��(C++Primer p.460)

	class Message(Message.h): �����ʼ��������������͵���Ϣ��
		save(Folder&): ��ָ���ļ��б��汾��Ϣ
		remove(Folder&): ��ָ���ļ���ɾ������Ϣ
		print(): ��ӡ����Ϣ���ڵ������ļ�������
		add_to_Folders(const Message&): ������Ϣ��ӵ�Ŀ���ļ���
		remove_from_Folders(): �ӱ���Ϣ���ڵ������ļ�����ɾ������Ϣ
	class Fold(Fold.h)����ϢĿ¼
		addMsg(): ���ļ��������Ӹ�������Ϣ
		remMsg(): �ӱ��ļ�����ɾ����������Ϣ
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
	//folders����ʽ��ʼ��Ϊ�ռ���
	explicit Message(const string& str = ""): contents(str) { }
	//�������Ƴ�Ա����������ָ�� Message ��ָ��
	Message(const Message&);			//�������캯��
	Message& operator=(const Message&);	//������ֵ�����
	~Message();							//��������
	//�Ӹ��� Folder ���������/ɾ���� Message
	void save(Folder&);
	void remove(Folder&);

	//void addFold(Folder*);
	//void remFold(Folder*);

	void print();
private:
	string contents;					//ʵ����Ϣ�ı�
	set <Folder*> folders;				//������ Message �� Folder
	//�������캯����������ֵ�����������������ʹ�õĹ��ߺ���
	//���� Message ��ӵ�ָ������� Folder ��
	void add_to_Folders(const Message&);
	//�� folders �е�ÿ�� Folder ��ɾ���� Message
	void remove_from_Folders();
};

void swap(Message&, Message&);
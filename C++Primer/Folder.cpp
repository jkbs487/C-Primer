#include "Folder.h"
//#include "Message.h"

void Folder::addMsg(Message *m) {
	messages.insert(m);
}

void Folder::remMsg(Message *m) {
	messages.erase(m);
}

//void Folder::add_to_Msgs(const Folder& m) {
//	for (auto f : m.messages)	//��ÿ������ m �� Folder
//		f->save(*this);		//��� Folder ���һ��ָ�� Message ��ָ��
//}
//
//Folder::Folder(const Folder& m) : m_name(m.m_name), messages(m.messages) {
//	add_to_Msgs(m);			//������Ϣ��ӵ�ָ�� m �� Folder ��
//}
//
//void Folder::remove_from_Msgs() {
//	for (auto f : messages)		//��ÿ������ m �� Folder
//		f->remove(*this);		//�Ӹ� Folder ɾ���� Message 
//}
//
//Folder::~Folder() {
//	remove_from_Msgs();		////������Ϣ�� Folder ��ɾ��
//}
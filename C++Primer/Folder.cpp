#include "Folder.h"
//#include "Message.h"

void Folder::addMsg(Message *m) {
	messages.insert(m);
}

void Folder::remMsg(Message *m) {
	messages.erase(m);
}

//void Folder::add_to_Msgs(const Folder& m) {
//	for (auto f : m.messages)	//对每个包含 m 的 Folder
//		f->save(*this);		//向该 Folder 添加一个指向本 Message 的指针
//}
//
//Folder::Folder(const Folder& m) : m_name(m.m_name), messages(m.messages) {
//	add_to_Msgs(m);			//将本信息添加到指向 m 的 Folder 中
//}
//
//void Folder::remove_from_Msgs() {
//	for (auto f : messages)		//对每个包含 m 的 Folder
//		f->remove(*this);		//从该 Folder 删除本 Message 
//}
//
//Folder::~Folder() {
//	remove_from_Msgs();		////将本信息从 Folder 中删除
//}
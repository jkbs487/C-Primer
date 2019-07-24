#include "Message.h"

void Message::save(Folder &f) {
	folders.insert(&f);	//������ Folder ��ӵ����ǵ� Folder �б���
	f.addMsg(this);		//���� Message ��ӵ� f �� Message ������
}

void Message::remove(Folder &f) {
	folders.erase(&f);	//������ Folder �����ǵ� Folder �б���ɾ��
	f.remMsg(this);		//���� Message �� Message ������ɾ��
}

void Message::add_to_Folders(const Message& m) {
	for (auto f : m.folders)	//��ÿ������ m �� Folder
		f->addMsg(this);		//��� Folder ���һ��ָ�� Message ��ָ��
}

Message::Message(const Message &m): contents(m.contents), folders(m.folders) {
	add_to_Folders(m);			//������Ϣ��ӵ�ָ�� m �� Folder ��
}

void Message::remove_from_Folders() {
	for (auto f : folders)		//��ÿ������ m �� Folder
		f->remMsg(this);		//�Ӹ� Folder ɾ���� Message 
}

Message::~Message() {
	remove_from_Folders();		////������Ϣ�� Folder ��ɾ��
}

Message& Message::operator=(const Message& rhs) {
	//ͨ����ɾ��ָ���ٲ������������� �Ը�ֵ ���
	remove_from_Folders();		//�������� Folder
	contents = rhs.contents;	//�� rhs ������Ϣ����
	folders = rhs.folders;		//�� rhs ���� Folder ָ��
	add_to_Folders(rhs);		//���� Message ��ӵ���Щ Folder ��
	return *this;
}
void Message::print() {
	for (auto f : folders) {
		cout << f->getName() << " ";
	}
}

//��дswap����
void swap(Message& lhs, Message& rhs) {
	using std::swap;		//����һ����ϰ��
	//��ÿ����Ϣ��ָ��������ڵ� Folder ��ɾ��
	for (auto f : lhs.folders) {
		f->remMsg(&lhs);
	}
	for (auto f : rhs.folders) {
		f->remMsg(&rhs);
	}
	//��������
	swap(lhs.folders, rhs.folders);		//swap(set&, set&);
	swap(lhs.contents, rhs.contents);	//swap(string&, string&);
	//��ÿ�� Message ��ָ����ӵ����µ� Folder ��
	for (auto f : lhs.folders) {
		f->addMsg(&lhs);
	}
	for (auto f : rhs.folders) {
		f->addMsg(&rhs);
	}
}

//�ӱ� Message �ƶ� Folder ָ��
void Message::move_Folders(Message* m) {
	folders = std::move(m->folders);	//ʹ�� set ���ƶ���ֵ�����
	for (auto f : folders) {			//��ÿ�� Folder
		f->remMsg(m);					//�� Folder ��ɾ���� Message
		f->addMsg(this);				//���� Message ��ӵ� Folder ��
	}
	m->folders.clear();					//ȷ������ m ���޺���
}

Message& Message::operator=(Message&& rhs) noexcept {
	if (this != &rhs) {
		remove_from_Folders();
		contents = std::move(rhs.contents);
		move_Folders(&rhs);
	}
	return *this;
}
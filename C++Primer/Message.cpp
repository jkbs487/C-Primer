#include "Message.h"

void Message::save(Folder &f) {
	folders.insert(&f);	//将给的 Folder 添加到我们的 Folder 列表中
	f.addMsg(this);		//将本 Message 添加到 f 的 Message 集合中
}

void Message::remove(Folder &f) {
	folders.erase(&f);	//将给的 Folder 从我们的 Folder 列表中删除
	f.remMsg(this);		//将本 Message 从 Message 集合中删除
}

void Message::add_to_Folders(const Message& m) {
	for (auto f : m.folders)	//对每个包含 m 的 Folder
		f->addMsg(this);		//向该 Folder 添加一个指向本 Message 的指针
}

Message::Message(const Message &m): contents(m.contents), folders(m.folders) {
	add_to_Folders(m);			//将本信息添加到指向 m 的 Folder 中
}

void Message::remove_from_Folders() {
	for (auto f : folders)		//对每个包含 m 的 Folder
		f->remMsg(this);		//从该 Folder 删除本 Message 
}

Message::~Message() {
	remove_from_Folders();		////将本信息从 Folder 中删除
}

Message& Message::operator=(const Message& rhs) {
	//通过先删除指针再插入它们来处理 自赋值 情况
	remove_from_Folders();		//更新已有 Folder
	contents = rhs.contents;	//从 rhs 拷贝消息内容
	folders = rhs.folders;		//从 rhs 拷贝 Folder 指针
	add_to_Folders(rhs);		//将本 Message 添加到那些 Folder 中
	return *this;
}
void Message::print() {
	for (auto f : folders) {
		cout << f->getName() << " ";
	}
}

//重写swap函数
void swap(Message& lhs, Message& rhs) {
	using std::swap;		//这是一个好习惯
	//将每个消息的指针从它所在的 Folder 中删除
	for (auto f : lhs.folders) {
		f->remMsg(&lhs);
	}
	for (auto f : rhs.folders) {
		f->remMsg(&rhs);
	}
	//交换内容
	swap(lhs.folders, rhs.folders);		//swap(set&, set&);
	swap(lhs.contents, rhs.contents);	//swap(string&, string&);
	//将每个 Message 的指针添加到其新的 Folder 中
	for (auto f : lhs.folders) {
		f->addMsg(&lhs);
	}
	for (auto f : rhs.folders) {
		f->addMsg(&rhs);
	}
}

//从本 Message 移动 Folder 指针
void Message::move_Folders(Message* m) {
	folders = std::move(m->folders);	//使用 set 的移动赋值运算符
	for (auto f : folders) {			//对每个 Folder
		f->remMsg(m);					//从 Folder 中删除旧 Message
		f->addMsg(this);				//将本 Message 添加到 Folder 中
	}
	m->folders.clear();					//确保销毁 m 是无害的
}

Message& Message::operator=(Message&& rhs) noexcept {
	if (this != &rhs) {
		remove_from_Folders();
		contents = std::move(rhs.contents);
		move_Folders(&rhs);
	}
	return *this;
}
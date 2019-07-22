/*
--------------------���Ժ���---------------------

	Ŀǰӵ�еĳ���ʾ����
		WordAnalysis��
		TextQuery & QueryResult���ı���ѯ����
		word_transform���ı�ת������
		Message & Folder���������Ƴ���

-------------------------------------------------
*/

#include "WordAnalysis.h"
#include "TextQuery.h"
#include "word_transform.h"
#include "Message.h"
using namespace std;

//���ʷָ����
void WordAnalysis_test() {
	string str = "the quick red fox jumps over the slow red turtle";
	WordAnalysis story(str);
	story.print();
}

//�ı���ѯ����
void TextQuery_test() {
	ifstream in("./static/test.txt");
	TextQuery story(in);
	print(cout, story.query("or"));
}

//�ı�ת������
void word_transform_test() {
	ifstream file("./static/map_file.txt");
	ifstream input("./static/input.txt");
	word_transform(file, input);
}

//�������Ʋ���
void Message_test() {
	Message str("string string string");
	Folder nf1("newFolder1");
	Folder nf2("newFolder2");
	Folder nf3("newFolder3");
	str.save(nf1);
	str.save(nf2);
	str.save(nf3);
	str.print();
	return;
}

int main()
{
	string command;
	cout << "------------���Ժ���---------------" << endl;
	cout << "           1.���ʷָ�              " << endl;
	cout << "           2.�ı���ѯ              " << endl;
	cout << "           3.�ı�ת��              " << endl;
	cout << "           4.��������              " << endl;
	cout << "-----------------------------------" << endl;
	while (getline(cin, command)) {
		switch (stoi(command)) {
			case 1: 
				cout << "------------���ʷָ����--------------- " << endl;
				WordAnalysis_test();
				break;
			case 2: 
				cout << "------------�ı���ѯ����--------------- " << endl;
				TextQuery_test();
				break;
			case 3: 
				cout << "------------�ı�ת������--------------- " << endl;
				word_transform_test();
				break;
			case 4: 
				cout << "------------�������Ʋ���--------------- " << endl;
				Message_test();
				break;
			default:
				cout << "�������" << endl;
		}
	}
}

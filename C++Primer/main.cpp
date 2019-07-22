/*
--------------------测试函数---------------------

	目前拥有的程序示例：
		WordAnalysis：
		TextQuery & QueryResult：文本查询程序
		word_transform：文本转换程序
		Message & Folder：拷贝控制程序

-------------------------------------------------
*/

#include "WordAnalysis.h"
#include "TextQuery.h"
#include "word_transform.h"
#include "Message.h"
using namespace std;

//单词分割测试
void WordAnalysis_test() {
	string str = "the quick red fox jumps over the slow red turtle";
	WordAnalysis story(str);
	story.print();
}

//文本查询测试
void TextQuery_test() {
	ifstream in("./static/test.txt");
	TextQuery story(in);
	print(cout, story.query("or"));
}

//文本转换测试
void word_transform_test() {
	ifstream file("./static/map_file.txt");
	ifstream input("./static/input.txt");
	word_transform(file, input);
}

//拷贝控制测试
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
	cout << "------------测试函数---------------" << endl;
	cout << "           1.单词分割              " << endl;
	cout << "           2.文本查询              " << endl;
	cout << "           3.文本转换              " << endl;
	cout << "           4.拷贝控制              " << endl;
	cout << "-----------------------------------" << endl;
	while (getline(cin, command)) {
		switch (stoi(command)) {
			case 1: 
				cout << "------------单词分割测试--------------- " << endl;
				WordAnalysis_test();
				break;
			case 2: 
				cout << "------------文本查询测试--------------- " << endl;
				TextQuery_test();
				break;
			case 3: 
				cout << "------------文本转换测试--------------- " << endl;
				word_transform_test();
				break;
			case 4: 
				cout << "------------拷贝控制测试--------------- " << endl;
				Message_test();
				break;
			default:
				cout << "输入错误！" << endl;
		}
	}
}

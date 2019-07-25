/*
				关联容器示例（C++Primer p.391）

	    给定一个string，将其转换成另外一个string，程序的
	输入是两个文件。第一个文件保存的是一些规则，用来转换
	第二个文件中的文本。每条规则由两部分组成：一个可能出
	现在输入文件中的单词和一个用来替换它的短语。第二个输
	入文件包含要转换的文本。

*/

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

//word_transform: 提供单词转换功能
map<string, string> buildMap(ifstream& map_file) {
	map<string, string> trans_map;	//保存转换规则
	string key;						//要转换的单词
	string value;					//替换后的内容
	//读取第一个单词存入 key 中，行中剩余内容存入 value
	while (map_file >> key && getline(map_file, value)) {
		if (value.size() > 1)		//检查是否有转换规则
			trans_map[key] = value.substr(1);	//跳过前导空格
		else
			throw runtime_error("no rule for " + key);
	}
	return trans_map;
}

const string& transform(const string& s, const map<string, string>& m) {
	//实际的转换工作，此部分是程序的核心
	auto map_it = m.find(s);
	//如果单词在转换规则 map 中
	if (map_it != m.cend())
		return map_it->second;		//使用替换短语
	else
		return s;					//否则返回原 string
}

/**
* 单词转换主函数
* @param map_file - 单词转换规则文件, input - 待转换的输入文件
* @return
*/
void word_transform(ifstream &map_file, ifstream &input) {
	auto trans_map = buildMap(map_file);	//保存转换规则
	string text;							//保存输入中的每一行
	while (getline(input, text)) {			//读取一行输入
		istringstream stream(text);			//读取每个单词
		string word;						
		bool firstword = true;				//控制是否打印空格
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";				//在单词间打印一个空格
			//transform 返回它的第一个参数或其转换形式
			cout << transform(word, trans_map);	//打印输出
		}
		cout << endl;						//完成一行的转换
	}
}

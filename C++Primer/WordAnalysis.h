#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
* 处理输入的字符串，以单词为单位
*/
class WordAnalysis {
private:
	vector<string> words;
	
	/**
	* 处理输入的字符串，以单词为单位
	* @param str
	* @return 
	*/
	void words_init(const string str);

public:
	/**
	* 默认构造函数
	*/
	WordAnalysis() = default;
	/**
	* 构造函数
	* @param str - 输入的字符串
	*/
	WordAnalysis(string str) {
		words_init(str);
	}

	/**
	* 查找单词
	* @param str - 待查找的字符串
	* @return 字符串下标，如果查找失败返回 -1
	*/
	int find(string str);

	/**
	* 删除单词
	* @param str - 待删除的字符串
	* @return
	*/
	void del(string str);

	/**
	* 打印word内容
	* @param 
	* @return 
	*/
	void print() {
		for (auto it = words.begin(); it != words.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	/**
	* 消除重复单词
	* @param
	* @return
	*/
	void elimDups();
};
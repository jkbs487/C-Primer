#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
* ����������ַ������Ե���Ϊ��λ
*/
class WordAnalysis {
private:
	vector<string> words;
	
	/**
	* ����������ַ������Ե���Ϊ��λ
	* @param str
	* @return 
	*/
	void words_init(const string str);

public:
	/**
	* Ĭ�Ϲ��캯��
	*/
	WordAnalysis() = default;
	/**
	* ���캯��
	* @param str - ������ַ���
	*/
	WordAnalysis(string str) {
		words_init(str);
	}

	/**
	* ���ҵ���
	* @param str - �����ҵ��ַ���
	* @return �ַ����±꣬�������ʧ�ܷ��� -1
	*/
	int find(string str);

	/**
	* ɾ������
	* @param str - ��ɾ�����ַ���
	* @return
	*/
	void del(string str);

	/**
	* ��ӡword����
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
	* �����ظ�����
	* @param
	* @return
	*/
	void elimDups();
};
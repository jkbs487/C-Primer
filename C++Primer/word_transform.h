/*
				��������ʾ����C++Primer p.391��

	    ����һ��string������ת��������һ��string�������
	�����������ļ�����һ���ļ��������һЩ��������ת��
	�ڶ����ļ��е��ı���ÿ����������������ɣ�һ�����ܳ�
	���������ļ��еĵ��ʺ�һ�������滻���Ķ���ڶ�����
	���ļ�����Ҫת�����ı���

*/

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

//word_transform: �ṩ����ת������
map<string, string> buildMap(ifstream& map_file) {
	map<string, string> trans_map;	//����ת������
	string key;						//Ҫת���ĵ���
	string value;					//�滻�������
	//��ȡ��һ�����ʴ��� key �У�����ʣ�����ݴ��� value
	while (map_file >> key && getline(map_file, value)) {
		if (value.size() > 1)		//����Ƿ���ת������
			trans_map[key] = value.substr(1);	//����ǰ���ո�
		else
			throw runtime_error("no rule for " + key);
	}
	return trans_map;
}

const string& transform(const string& s, const map<string, string>& m) {
	//ʵ�ʵ�ת���������˲����ǳ���ĺ���
	auto map_it = m.find(s);
	//���������ת������ map ��
	if (map_it != m.cend())
		return map_it->second;		//ʹ���滻����
	else
		return s;					//���򷵻�ԭ string
}

/**
* ����ת��������
* @param map_file - ����ת�������ļ�, input - ��ת���������ļ�
* @return
*/
void word_transform(ifstream &map_file, ifstream &input) {
	auto trans_map = buildMap(map_file);	//����ת������
	string text;							//���������е�ÿһ��
	while (getline(input, text)) {			//��ȡһ������
		istringstream stream(text);			//��ȡÿ������
		string word;						
		bool firstword = true;				//�����Ƿ��ӡ�ո�
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " ";				//�ڵ��ʼ��ӡһ���ո�
			//transform �������ĵ�һ����������ת����ʽ
			cout << transform(word, trans_map);	//��ӡ���
		}
		cout << endl;						//���һ�е�ת��
	}
}

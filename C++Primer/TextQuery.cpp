#include "TextQuery.h"
#include <iostream>
#include <fstream>
#include <sstream>

//��ȡ�����ļ����������ʵ��кŵ�ӳ��
TextQuery::TextQuery(ifstream& is) : file(new vector<string>) {
	string text;
	while (getline(is, text)) {			//���ı��е�ÿһ��
		file->push_back(text);			//��������ı�
		int n = file->size() - 1;		//��ǰ�к�
		istringstream line(text);		//���ı��зֽ�Ϊ����
		string word;
		while (line >> word) {			//�����е�ÿ������
			//������ʲ��� wm �У���֮Ϊ�±��� wm �����һ��
			auto &lines = wm[word];		//lines��һ�� shared_ptr
			if (!lines)					//�����ǵ�һ�������������ʱ����ָ��Ϊ��
				lines.reset(new set < line_no >); //����һ���µ� set
			lines->insert(n);			//�����кŲ��� set ��
		}
	}
}

QueryResult
TextQuery::query(const string& sought) const {
	//���δ�ҵ� sought�����ǽ�����һ��ָ��� set ��ָ�� 
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	//ʹ�� find �������±������ҵ��ʣ����⽫������ӵ� wm ��
	auto loc = wm.find(sought);
	if (loc == wm.end())
		//δ�ҵ�
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}
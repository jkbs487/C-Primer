#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <iostream>

using namespace std;
//���ʲ�ѯ��
class QueryResult
{
friend ostream &print(ostream &, const QueryResult&);
public:
	using line_no = vector<string>::size_type;
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) : sought(s), lines(p), file(f) {	}
private:
	string sought;						//��ѯ����
	shared_ptr<set<line_no>> lines;		//���ֵ��к�
	shared_ptr<vector<string>> file;	//�����ļ�

};

//��ӡ����
ostream& print(ostream&, const QueryResult&);

//�ж���� time ���� times
string make_plural(size_t, const string&, const string&);
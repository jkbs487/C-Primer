/*
				�ı���ѯʾ����C++primer p.430��
	


*/









#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include "QueryResult.h"
using namespace std;

//class TextQuery: ͨ����ȡһ���ļ������Բ�ѯ���еĵ��ʳ��ִ���������ʾ������
class TextQuery
{
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	//�����ļ�
	shared_ptr<vector<string>> file;	
	//ÿ�����ʵ������ڵ��кŵļ��ϵ�ӳ��
	map<string, shared_ptr< set< line_no > >> wm;
};


/*
				文本查询示例（C++primer p.430）
	


*/









#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include "QueryResult.h"
using namespace std;

//class TextQuery: 通过读取一个文件，可以查询其中的单词出现次数，并显示其行数
class TextQuery
{
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	//输入文件
	shared_ptr<vector<string>> file;	
	//每个单词到它所在的行号的集合的映射
	map<string, shared_ptr< set< line_no > >> wm;
};


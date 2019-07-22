#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <iostream>

using namespace std;
//单词查询类
class QueryResult
{
friend ostream &print(ostream &, const QueryResult&);
public:
	using line_no = vector<string>::size_type;
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) : sought(s), lines(p), file(f) {	}
private:
	string sought;						//查询单词
	shared_ptr<set<line_no>> lines;		//出现的行号
	shared_ptr<vector<string>> file;	//输入文件

};

//打印内容
ostream& print(ostream&, const QueryResult&);

//判断输出 time 还是 times
string make_plural(size_t, const string&, const string&);
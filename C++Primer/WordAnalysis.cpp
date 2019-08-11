#include "WordAnalysis.h"

void WordAnalysis::words_init(const string str) {
	istringstream is(str);
	string word;
	while (is >> word) {
		words.push_back(word);
	}
}

int WordAnalysis::find(string str) {
	for (int i = 0; i < words.size(); ++i) {
		if (words[i] == str) {
			return i;
		}
	}
	return -1;
}

void WordAnalysis::del(string str) {
	int index = find(str);
	words.erase(words.begin() + index);
}

void WordAnalysis::elimDups() {
	//按字典序排序words，以便查找重复单词
	sort(words.begin(), words.end());
	//unique重排输入范围，使得每个单词只出现一次
	//排列在范围的前部，返回指向不重复区域之后一个位置的迭代器
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

bool check_size(const string& s, string::size_type sz) {
	return s.size() >= sz;
}

ostream& sprint(ostream& os, const string& s, char c) {
	return os << s << c;
}

void WordAnalysis::biggies(vector<string>::size_type sz, ostream& os, char c) {
	elimDups();		//按字典序排序 words，删除重复单词
	//按长度排序，长度相同的单词维持字典序
	stable_sort(words.begin(), words.end(), [](const string& a, const string& b) { return a.size() < b.size(); });
	//获取一个迭代器，指向第一个满足 size()>=sz 的元素(lambda表达式)
	//auto wc = find_if(words.begin(), words.end(), [=](const string& a) { return a.size() >= sz; });
	//获取一个迭代器，指向第一个满足 size()>=sz 的元素(bind函数)
	auto wc = find_if(words.begin(), words.end(), bind(check_size, placeholders::_1, sz));
	//计算满足 size >= sz 的元素的数目
	auto count = words.end() - wc;
	cout << count << " " << "words" << " of length " << sz << " or longer" << endl;
	//打印长度大于等于给定值的单词，每个单词后面接一个空格(lambda表达式)
	//os隐式捕获，引用捕获方式；c显示捕获，值捕获方式
	//for_each(wc, words.end(), [&, c](const string& s) { os << s << c; });
	//os显示捕获，引用捕获方式；c隐式捕获，值捕获方式
	//for_each(wc, words.end(), [=, &os](const string& s) { os << s << c; });
	//打印长度大于等于给定值的单词，每个单词后面接一个空格(bind函数)
	for_each(wc, words.end(), bind(sprint, ref(os), placeholders::_1, ' '));
	cout << endl;
}

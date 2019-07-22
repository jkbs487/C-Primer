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



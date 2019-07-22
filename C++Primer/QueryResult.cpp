#include "QueryResult.h"

string make_plural(size_t ctr, const string& word, const string& ending) {
	return (ctr == 1) ? word : word + ending;
}

ostream& print(ostream& os, const QueryResult& qr) {
	//����ҵ��˵��ʣ���ӡ���ִ��������г��ֵ�λ��
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl;
	//��ӡ���ʳ��ֵ�ÿһ��
	for (auto num : *qr.lines)	//�� set ��ÿ������
		//�����кŴ�0��ʼ���û�����������
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
	return os;
}
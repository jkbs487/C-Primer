#include "strVec.h"

void StrVec::push_back(const string& s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}


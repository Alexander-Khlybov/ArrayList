#include "array_list.h"

List::List(int maxSize){
	if (maxSize < 0)
		throw
			length_error("Length error");

	maxSize_ = maxSize + _BUF_;
	data_ = new KeyType[maxSize_];
	nextRefs_ = new int[maxSize_];

    for (int i = _BUF_ ; i < maxSize_ ; i++)
		nextRefs_[i] = 1;
	nextRefs_[0] = 0;
	nextRefs_[1] = -1;
}

List::List(const List& list){
	maxSize_ = list.maxSize_;
	data_ = new KeyType[maxSize_];
	nextRefs_ = new int[maxSize_];

	for(int i = _BUF_ ; i < maxSize_ ; i++)
		nextRefs_[i] = 1;
	nextRefs_[1] = -1;
	
	int tmp = list.nextRefs_[0];
	nextRefs_[0] = tmp;
	while(tmp != 0){
		data_[tmp] = list.data_[tmp];
		nextRefs_[tmp] = list.nextRefs_[tmp];
		tmp = list.nextRefs_[tmp];
	}
}

List::~List(void){
	delete [] data_;
	delete [] nextRefs_;
}
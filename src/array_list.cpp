#include "array_list.h"

List::List(int maxSize){
	if (maxSize < 0)
		throw("Size of the buffer memory cannot be negative");

	maxSize_ = maxSize + _BUF_;
	data_ = new KeyType[maxSize_];
	nextRefs_ = new int[maxSize_];
	if ((data_ == 0) || (nextRefs_ == 0))
		throw("Failed to allocate memory");

    for (int i = _BUF_ ; i < maxSize_ ; i++)
		nextRefs_[i] = 1;
	nextRefs_[0] = 0;
	nextRefs_[1] = -1;
}

List::List(const List& list){
	maxSize_ = list.maxSize_;
	data_ = new KeyType[maxSize_];
	nextRefs_ = new int[maxSize_];
	if ((data_ == 0) || (nextRefs_ == 0))
		throw("Failed to allocate memory");

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

int getFreeMemorySlot(void){
	int i = _BUF_;

	while (i < maxSize_){ 
		if (nextRefs[i] == 1)
			break;
		i++;
	}

	if (i == maxSize_)
		i == -1;
	return i;
}

int find(const KeyType& findKey) const{
	int tmp = nextRefs_[0];

	while ((tmp != 0) && (data_[tmp] != findKey))
		tmp = nextRefs_[tmp];

	if (data_[tmp] != key)
		throw("Key hasn't been found");
	return tmp;
}


#include "array_list.h"

List::List(int maxSize){
	if (maxSize < 0)
		throw("Size of the buffer memory cannot be negative");

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

int List::getFreeMemorySlot(void) const{
	int i = _BUF_;

	while (i < maxSize_){ 
		if (nextRefs_[i] == 1)
			break;
		i++;
	}

	if (i == maxSize_)
		i = -1;
	return i;
}

int List::getAddressOfPenultimateNode(void) const{
    if (nextRefs_[0] == 0)
        throw("List is empty");

	int address = 0;

    if ((nextRefs_[nextRefs_[0]] == 0) && (nextRefs_[0] != 0)) {
        address = -1;
    } else {
		while(nextRefs_[nextRefs_[address]] != 0)
			address = nextRefs_[address];
	}

	return address;
}

int List::getAddressOfPreviousKey(const KeyType& findKey) const{
    if (nextRefs_[0] == 0)
        throw("List is empty");

	int tmp = 0;

	while ((nextRefs_[tmp] != 0) && (data_[nextRefs_[tmp]] != findKey))
		tmp = nextRefs_[tmp];

	if (tmp == 0)
		tmp = -1;

	if (data_[nextRefs_[tmp]] != findKey)
		throw("Key hasn't been found");
	

	return tmp;
}

int List::find(const KeyType& findKey) const{
    if (nextRefs_[0] == 0)
        throw("List is empty");

	int findAddress = nextRefs_[0];

	while ((findAddress != 0) && (data_[findAddress] != findKey))
		findAddress = nextRefs_[findAddress];

	if (data_[findAddress] != findKey)
		throw("Key hasn't been found");
	return findAddress;
}

void List::remove(const KeyType& findKey){
	int temporaryAddress = getAddressOfPreviousKey(findKey);

	if (temporaryAddress == -1){
		nextRefs_[nextRefs_[0]] = 1;
		nextRefs_[0] = 0;
	} else {
		int tmp = nextRefs_[temporaryAddress];
		nextRefs_[temporaryAddress] = nextRefs_[tmp];
		nextRefs_[tmp] = 1;
	}
}

void List::removeBefore(const KeyType& findKey){
	int temporaryAddress = getAddressOfPreviousKey(data_[getAddressOfPreviousKey(findKey)]);

	if (temporaryAddress == -1){
		int tmp = nextRefs_[0];
		nextRefs_[0] = nextRefs_[nextRefs_[0]];
		nextRefs_[tmp] = 1;
	} else {
		int tmp = nextRefs_[temporaryAddress];
		nextRefs_[temporaryAddress] = nextRefs_[tmp];
		nextRefs_[tmp] = 1;
	}
}

void List::removeAfter(const KeyType& findKey){
	int temporaryAddress = find(findKey);

	int i = nextRefs_[temporaryAddress];
	nextRefs_[temporaryAddress] = nextRefs_[nextRefs_[temporaryAddress]];
	nextRefs_[i] = 1;
}

void List::removeEnd(void){
	int temporaryAddress = getAddressOfPenultimateNode();

	if (temporaryAddress == -1){
		nextRefs_[nextRefs_[0]] = 1;
		nextRefs_[0] =0;
	} else {
		nextRefs_[nextRefs_[temporaryAddress]] = 1;
		nextRefs_[temporaryAddress] = 0;
	}
}

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

int List::getAddressFreeMemorySlot(void) const{
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

    if (nextRefs_[nextRefs_[0]] == 0) {
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

List& List::operator= (const List& list){
	if (this != &list){
		delete[]data_;
		delete[]nextRefs_;

		maxSize_ = list.maxSize_;
		data_ = new KeyType[maxSize_];
		nextRefs_ = new int[maxSize_];
		nextRefs_[0] = 0;
		nextRefs_[1] = -1;
		for (int i = 2; i < maxSize_;i++)
			nextRefs_[i] = 1;

		int first = list.nextRefs_[0];
		while(first != 0){
			pushEnd(list.data_[first]);
			first = list.nextRefs_[first];
		}
	}
	return *this;
}


int List::operator== (const List& list)const{
	int first1 = nextRefs_[0];
	int first2 = list.nextRefs_[0];
	while ((first1 != 0) && (first2 != 0)){
		if (data_[first1] != list.data_[first2])
			return 0;
		first1 = nextRefs_[first1];
		first2 = list.nextRefs_[first2];
	}
	if ((first1 || first2) != 0)
		return 0;
	return 1;
}

int List::operator!= (const List& list)const{
	return !(*this == list);
}

KeyType getListElement(int address) const{
	int temporaryAddress = nextRefs_[0];
	while ((temporaryAddress != 0) && (temporaryAddress != address)){
		temporaryAddress = nextRefs_[temporaryAddress];
	}
	if (temporaryAddress != address)
		throw("Non-existent address");
	return data_[address];
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
	int previousAddress = getAddressOfPreviousKey(findKey);
	if (previousAddress == -1)
		throw("List contains only one node");
		
	int temporaryAddress = getAddressOfPreviousKey(data_[previousAddress]);

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

void List::push(const KeyType& addKey){
	int temporaryAddress = getAddressFreeMemorySlot();
	if (temporaryAddress == -1)
		throw("Failed to allocate memory.");

	nextRefs_[temporaryAddress] = nextRefs_[0];
	nextRefs_[0] = temporaryAddress;
	data_[temporaryAddress] = addKey;
}

void List::pushEnd(const KeyType& addKey){
	int temporaryAddress = getAddressFreeMemorySlot();
	if (temporaryAddress == -1)
		throw("Failed to allocate memory.");
	data_[temporaryAddress] = addKey;

	int addressOfPenultimateNode;
	try{
		addressOfPenultimateNode = getAddressOfPenultimateNode();
	} catch (...) {
		nextRefs_[0] = temporaryAddress;
		nextRefs_[temporaryAddress] = 0;
		return;
	}

	nextRefs_[nextRefs_[addressOfPenultimateNode]] = temporaryAddress;
	nextRefs_[temporaryAddress] = 0;
}

void List::pushBefore(const KeyType& findKey, const KeyType& addKey){
	int temporaryAddress = getAddressFreeMemorySlot();
	if (temporaryAddress == -1)
		throw("Failed to allocate memory.");

	int addressFound = getAddressOfPreviousKey(findKey);

	int tmp = nextRefs_[addressFound];
	nextRefs_[addressFound] = temporaryAddress;
	nextRefs_[temporaryAddress] = tmp;
	data_[temporaryAddress] = addKey;
}

void List::pushAfter(const KeyType& findKey, const KeyType& addKey){
	int temporaryAddress = getAddressFreeMemorySlot();
	if (temporaryAddress == -1)
		throw("Failed to allocate memory.");

	int addressFound = find(findKey);

	int tmp = nextRefs_[addressFound];
	nextRefs_[addressFound] = temporaryAddress;
	nextRefs_[temporaryAddress] = tmp;
	data_[temporaryAddress] = addKey;
}

int List::searchMax(void) const{
	if (nextRefs_[0] == 0)
		throw("List is empty");

	int tmp = nextRefs_[0];
	KeyType max = data_[tmp];
	int tempAddr = tmp;

	while (tmp != 0){
		if (data_[tmp] > max){
			max = data_[tmp];
			tempAddr = tmp;
		}
		tmp = nextRefs_[tmp];
	}

	return tempAddr;
}

int List::searchMin(void) const{
	if (nextRefs_[0] == 0)
		throw("List is empty");

	int tmp = nextRefs_[0];
	KeyType min = data_[tmp];
	int tempAddr = tmp;

	while (tmp != 0){
		if (data_[tmp] < min){
			min = data_[tmp];
			tempAddr = tmp;
		}
		tmp = nextRefs_[tmp];
	}

	return tempAddr;
}

void List::swapFirstAndLastElements(void){
	if (nextRefs_[0] == 0)
		throw("List is empty");

	if (nextRefs_[nextRefs_[0]] == 0)
		return;

	int temporaryAddress = getAddressOfPenultimateNode();
	int first = nextRefs_[0];

	int tmp = nextRefs_[first];

	nextRefs_[first] = 0;
	nextRefs_[0] = nextRefs_[temporaryAddress];
	nextRefs_[temporaryAddress] = first;
}

void List::insertInOrderedList(const KeyType& findKey){
	int temporaryAddress = getAddressFreeMemorySlot();
	if (temporaryAddress == -1)
		throw("Failed to allocate memory.");

	int tmp = 0;
	while ((nextRefs_[tmp] != 0) && (data_[nextRefs_[tmp]] < findKey))
		tmp = nextRefs_[tmp];

	int t = nextRefs_[tmp];
	nextRefs_[tmp] = temporaryAddress;
	nextRefs_[temporaryAddress] = t;
}
 
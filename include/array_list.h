#pragma once

#include <iostream>

#define _BUF_ 2

using namespace std;
typedef int KeyType;

class List {
public:
    List(int size = 10);
    List(const List&);
    ~List(void);

    int find(const KeyType& ) const;
    


private:
    int maxSize_;
    KeyType* data_;
    int* nextRefs_;

	int getFreeMemorySlot(void) const;
};
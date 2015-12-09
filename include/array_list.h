#pragma once

#include <iostream>

#define _BUF_ 2

using namespace std;
typedef int KeyType;

class List {
private:
    int maxSize_;
    KeyType* data_;
    int* nextRefs_;

    int getAddressFreeMemorySlot(void) const;
    int getAddressOfPenultimateNode(void) const;
    int getAddressOfPreviousKey(const KeyType&) const;

public:
    List(int size = 10);
    List(const List&);
    ~List(void);

    List& operator= (const List&);
    int operator== (const List&)const;
    int operator!= (const List&)const;

    int find(const KeyType&) const;
    void remove(const KeyType&);
    void removeBefore(const KeyType&);
    void removeAfter(const KeyType&);
    void removeEnd(void);
    void push(const KeyType&);
    void pushEnd(const KeyType&);
    void pushBefore(const KeyType&,  const KeyType&);
    void pushAfter(const KeyType&,  const KeyType&);
    int searchMax(void) const;
    void swap (void); // поменять местами первый и последний
    void insertInOrderedList(const KeyType&);
    
    friend ostream& operator<<(ostream& out, const List& list) {
        int temporaryAddress = list.nextRefs_[0];
        while (temporaryAddress != 0) {
            out << "| " << list.data_[temporaryAddress] << " | -> ";
            temporaryAddress = list.nextRefs_[temporaryAddress];
        }
        out << "\\|||";
        return out;
    }
};
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

    int find(const KeyType&) const;
    void remove(const KeyType&);
    void removeBefore(const KeyType&);
    void removeAfter(const KeyType&);
    void removeEnd(void);

/*
    void PushAfter(KeyType, KeyType);
    void PushEnd(KeyType);
    void Swap(void);
    int SearchMax(void);
    void Sort(void);
    void PushSort(void);
    */
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
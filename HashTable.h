//
//  HashTable.h
//  CS210
//
//  Created by Badr AlKhamissi on 11/27/15.
//  Copyright © 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <sstream>
using namespace std;

template <class keyT, class dataT>
class HashTable {
private:
    struct slot{
        keyT key;
        dataT data;
    };
    slot* arr;
    keyT empty;
    int maxSize, cSize, h;
    int hash(const keyT&)const;
public:
    HashTable(keyT, int sz = 50);
    ~HashTable();
    bool insert(const keyT&, const dataT&);
    bool search(const keyT&);
    void update(const keyT&, const dataT&);
    void retrieve(keyT&, dataT&);
    bool isEmpty()const{return cSize == 0;};
    bool isFull()const{return cSize == maxSize;};
    void emptyTable(keyT);
    int size()const{return cSize;};
    slot operator[](int i){return (arr[i]);}
};

template <class keyT, class dataT>
HashTable<keyT, dataT>::HashTable(keyT emptyKey, int sz){
    maxSize = sz;
    cSize = 0;
    h = -1;
    arr = new slot[maxSize];
    emptyTable(emptyKey);
}

template <class keyT, class dataT>
HashTable<keyT, dataT>::~HashTable(){
    delete []arr;
}

template <class keyT, class dataT>
void HashTable<keyT, dataT>::emptyTable(keyT emptyKey){
    empty = emptyKey;
    for (int i = 0; i<maxSize; i++)
        arr[i].key = empty;
    cSize = 0;
    h = -1;
}

template <class keyT, class dataT>
int HashTable<keyT, dataT>::hash(const keyT& key)const{
    return key % maxSize;
}

template <class keyT, class dataT>
bool HashTable<keyT, dataT>::insert(const keyT& key, const dataT& data){
    if(!isFull()){
        h = hash(key);
        while (arr[h].key != empty)
            h = (h+1) % maxSize; // Linear Probing
        if(arr[h].key == empty){
            arr[h].key = key;
            arr[h].data = data;
            cSize++;
            return true;
        }
        return false;
    }else{
        return false;
    }
}

template <class keyT, class dataT>
bool HashTable<keyT, dataT>::search(const keyT& key){
    if(!isEmpty()){
        h = hash(key);
        int start = h;
        for( ; ;){
            if(arr[h].key == empty) return false;
            if(arr[h].key == key) return h;
            h = (h+1) % maxSize;
            if(h == start) return false;
        }
    }else{
        return false;
    }
}

template <class keyT, class dataT>
void HashTable<keyT, dataT>::update(const keyT& key, const dataT& data){
    if(search(key)){
        arr[h].key = key;
        arr[h].data = data;
    }
}

template <class keyT, class dataT>
void HashTable<keyT, dataT>::retrieve(keyT& key, dataT& data){
    if(search(key)){
        key = arr[h].key;
        data = arr[h].data;
    }
}


#endif /* HashTable_h */

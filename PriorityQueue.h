//
//  PriorityQueue.h
//  CS210
//
//  Created by Badr AlKhamissi on 11/16/15.
//  Copyright © 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


template <class T>
class PQ {
    T *arr;
    int maxSize;
    int idx;
    T minVal;
    void downHeap(int)
    void upHeap(int);
public:
    PQ(T, int sz = 10000
       );
    ~PQ();
    void push(T);
    void pop();
    T getTop(){return arr[1];};
    bool isEmpty()const{return !idx;};
    bool isFull()const{return idx == maxSize;};
    int size(){return idx;};
    void clear(){idx = 0;};
    void displayLevel(int,int,int,int);
    void displayHeap();
};

template <class T>
PQ<T>::PQ(T min, int sz){
    maxSize  = sz;
    arr = new T[maxSize];
    idx = 0;
    minVal = min;
    arr[0] = minVal;
}

template <class T>
PQ<T>::~PQ(){
    delete[] arr;
}

template <class T>
void PQ<T>::push(T v){
    *(arr+(++idx)) = v;
    upHeap(idx);
}

template <class T>
void PQ<T>::pop(){
    arr[1] = arr[idx--];
    downHeap(1);
}

template <class T>
void PQ<T>::upHeap(int k){
    int x = 0;
    T v = arr[k];
    while (arr[k/2] >= v) {
        x++;
        arr[k]= arr[k/2];
        k/=2;
    }
    //cout<<"Cost: "<<x+1<<endl;
    arr[k] = v;
}

template <class T>
void PQ<T>::downHeap(int k){
    int j = 2*k;
    T v = arr[k];
    while (j<=idx) {
        if((j<idx)&&(arr[j]>arr[j+1]))
            j++;
        if(v <= arr[j])
            break;
        arr[j/2] = arr[j];
        j*=2;
    }
    arr[j/2] = v;
}

template <class T>
void PQ<T>::displayLevel(int rows, int lvl, int s, int e){
    int skip = int(pow(2.0, rows-lvl)-1);
    for (int i = s; i<=e; i++) {
        cout<<setw(skip)<< " ";
        cout<<setw(2)<< arr[i];
        cout<<setw(skip)<< " ";
    }
    cout<<"\n\n\n";
}


template <class T>
void PQ<T>::displayHeap(){
    int s = 1, e = 1, rLength, k;
    int nLevels = int(ceil(log(float(idx))/log(2.0)+ 0.01));
    for (int lvl = 0; lvl<nLevels; lvl++) {
        displayLevel(nLevels,lvl,s,e);
        rLength = e-s+1;
        s = e + 1;
        k = e + 2*rLength;
        e = (k<idx) ? k:idx;
    }
}

#endif /* PriorityQueue_h */

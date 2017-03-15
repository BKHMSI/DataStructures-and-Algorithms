//
//  QueueT.h
//  CS210
//
//  Created by Badr AlKhamissi on 9/28/15.
//  Copyright © 2015 Badr AlKhamissi. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;


#ifndef QueueT_h
#define QueueT_h

template <class T>
class QueueT {
private:
    int* arr;
    int head, tail, count, size;
    
public:
    int A[500] = {};
    QueueT(int qSize = 500);
    QueueT(const QueueT<T>&);
    ~QueueT();
    bool isEmpty()const;
    bool isFull()const;
    void enqueue(T);
    void dequeue();
    void dequeue(T&);
    T front();
    void front(T&);
    int length()const;
    void print()const;
};



template <class T>
QueueT<T>::QueueT(int qSize){
    size = qSize;
    arr = new T[size];
    head = 1;
    tail = count = 0;
}

template <class T>
QueueT<T>::QueueT(const QueueT& rhs){
    head = rhs.head;
    tail = rhs.tail;
    count = rhs.count;
    size = rhs.size;
    arr = new T[size];
    
    for (int i = 0; i<count; i++) {
        *(arr+i) = *(rhs.arr+i);
    }
}

template <class T>
QueueT<T>::~QueueT(){
    delete[] arr;
}

template <class T>
bool QueueT<T>::isFull()const{
    return count>=size;
}

template <class T>
bool QueueT<T>::isEmpty()const{
    return count<=0;
}

template <class T>
int QueueT<T>::length()const{
    return count;
}

template <class T>
void QueueT<T>::enqueue(T q){
    if (isFull()) {
        cout<<"Queue is Full!"<<endl;
    }else{
        tail = (tail+1)%size;
        arr[tail] = q;
        count++;
    }
}

template <class T>
void QueueT<T>::dequeue(T& v){
    if (isEmpty()) {
        cout<<"Queue is Empty!"<<endl;
    }else{
        v = arr[head];
        head = (head+1)%size;
        count--;
    }
}

template <class T>
void QueueT<T>::dequeue(){
    if (isEmpty()) {
        cout<<"Queue is Empty!"<<endl;
    }else{
        head = (head+1)%size;
        count--;
    }
}

template <class T>
void QueueT<T>::front(T& v){
    if (isEmpty()) {
        cout<<"Queue is Empty!"<<endl;
    }else{
        v = *(arr+count);
    }
}

template <class T>
T QueueT<T>::front(){
    if (isEmpty()) {
        cout<<"Queue is Empty!"<<endl;
        return NULL;
    }else{
        return *(arr+count);
    }
}

template<class T>
void QueueT<T>::print()const{
    for (int i = head; i<=tail; i++) {
        cout<<*(arr+i)<<" ";
    }
    cout<<endl;
}



#endif /* QueueT_h */

//
//  StackT.h
//  CS210
//
//  Created by Badr AlKhamissi on 9/10/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __CS210__StackT__
#define __CS210__StackT__

#include <stdio.h>
#include <iostream>

using namespace std;


template <class T>
class StackT {
private:
    int top, size;
    T *arr;
public:
    StackT(); // Constructor
    StackT(int); // Constructor
    StackT(const StackT<T>&); // Copy Constructor
    ~StackT(); // Destructor
    void push(T);
    void pop();
    void pop(T&); // Overload for pop
    bool isEmpty()const;
    bool isFull()const;
    void print()const;
    bool operator==(const StackT<T>&);
    T getTop()const; // Retrieve Top
};


template <class T>
StackT<T>::StackT() {
    size = 100; // Default Size
    top = -1;
    arr = new T[size];
}

template <class T>
StackT<T>::StackT(int _size) {
    size = _size;
    top = -1;
    arr = new T[size];
}

template <class T>
StackT<T>::StackT(const StackT& copy) {
    size = copy.size;
    top = copy.top;
    arr = new T[size];
    for (int i = 0; i<=top; i++) {
        *(arr+i) = *(copy.arr+i);
    }
}

template <class T>
StackT<T>::~StackT() {
    delete[] arr;
}

template <class T>
void StackT<T>::push(T x){
    if (!isFull())
        *(arr+(++top)) = x;
    else
        cout<<"Stack Overflow"<<endl;
    
}

template <class T>
void StackT<T>::pop(){
    if (!isEmpty())
        top--;
    else
        cout<<"Stack Underflow"<<endl;
    
}

template <class T>
void StackT<T>::pop(T& v){
    if (!isEmpty())
        v = *(arr+(top--));
    else
        cout<<"Stack Underflow"<<endl;
}

template <class T>
bool StackT<T>::isEmpty()const{
    return top == -1 ? true:false;
}

template <class T>
bool StackT<T>::isFull()const{
    return top == size ? true:false;
}

template <class T>
T StackT<T>::getTop()const{
    if (!isEmpty())
        return *(arr+top);
    else
        return NULL;
}

template<class T>
bool StackT<T>::operator==(const StackT<T>&s){
    if (top != s.top) {
        return false;
    }
    
    for (int i = 0; i<=top; i++) {
        if(*(arr+i)!=*(s.arr+i))
            return false;
    }
    
    return true;
}

template <class T>
void StackT<T>::print()const{
    for (int i = 0; i<=top; i++) {
        cout<<*(arr+i)<<" ";
    }
    cout<<endl;
}

#endif /* defined(__CS210__StackT__) */

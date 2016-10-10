//
//  LinkedList.h
//  CPlusPlus
//
//  Created by Badr AlKhamissi on 9/14/16.
//  Copyright © 2016 Badr AlKhamissi. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <iostream>
using namespace std;

/**** THE ULTIMATE LINKED LIST CLASS ***/
// PUSH
// POP - LIFO
// DELETE SPECEFIC VALUE
// SORT
// COMPARE - ADD COMMON ELEMENTS INTO A THIRD LIST
// DISPLAY
// DISPLAY REVERSED
// SEARCH FOR A SPECEFIC VALUE
// OVERLOAD OPERATOR =
// OVERLOAD OPERATOR [ ] - ASSIGN A VALUE OR RETRIEVE A VALUE

template <class T>
class linkedList {
private:
    struct node{
        T x;
        node* next = NULL;
    };
    node *head, *prev;
public:
    linkedList();
    linkedList(T);
    linkedList(const linkedList&);
    ~linkedList();
    linkedList& operator=(const linkedList&);
    T& operator[](int);
    void push(T);
    void pop();
    void deleteNode(T);
    void sortList();
    void display();
    void displayReversed(node*);
    node* getHead(){return head;}
    int getSize();
    bool searchList(T, node*);
    linkedList compareLists(const linkedList&);
};

template <class T>
linkedList<T>::linkedList(){
    head = NULL;
    prev = head;
}

template <class T>
linkedList<T>::linkedList(T val){
    head = new node;
    head->x = val;
    head->next = NULL;
    prev = head;
}

template <class T>
linkedList<T>::linkedList(const linkedList& rhs){
    node* tmp = new node;
    this->head = tmp;
    head->next = NULL;
    prev = head;
    node* crsr = rhs.head;
    while (crsr!=NULL) {
        push(crsr->x);
        crsr = crsr->next;
    }
}

template <class T>
linkedList<T>& linkedList<T>::operator=(const linkedList& rhs){
    node* tmp = new node;
    this->head = tmp;
    head->next = NULL;
    prev = head;
    node* crsr = rhs.head;
    while (crsr!=NULL) {
        push(crsr->x);
        crsr = crsr->next;
    }
    return *this;
}

template <class T>
void linkedList<T>::push(T val){
    if(head == NULL){
        head = new node;
        head->x = val;
        head->next = NULL;
        prev = head;
    }else{
        node* crsr;
        crsr = new node;
        crsr->x = val;
        prev->next = crsr;
        crsr->next = NULL;
        prev = crsr;
    }
}

template <class T>
void linkedList<T>::pop(){
    if (head->next!= NULL) {
        node* crsr, *prevCrsr = nullptr;
        crsr = head;
        while (crsr->next!=NULL) {
            prevCrsr = crsr;
            crsr = crsr->next;
        }
        delete crsr;
        prevCrsr->next = NULL;
    }
}

template <class T>
void linkedList<T>::display(){
    node *crsr;
    crsr = head;
    while (crsr!=NULL) {
        cout<<crsr->x<<" ";
        crsr = crsr->next;
    }
}

template <class T>
void linkedList<T>::displayReversed(node* crsr){
    if (crsr!=NULL) {
        displayReversed(crsr->next);
        cout<<crsr->x<<" ";
    
}

template <class T>
T& linkedList<T>::operator[](int index){
    node* crsr = head;
    if (head!=NULL) {
        for (int i = 0; i<index; i++) {
            crsr = crsr->next;
        }
        return crsr->x;
    }else{
        cerr<<"List is Empty!!"<<endl;
        return head->x;
    }
}

template <class T>
int linkedList<T>::getSize(){
    node*crsr = head;
    int size = 0;
    while (crsr!=NULL) {
        crsr = crsr->next;
        size++;
    }
    return size;
}

template <class T>
void linkedList<T>::sortList(){
    node *crsr, *after;
    int size = getSize();
    for(int i = 0; i<size; i++){
        crsr = head;
        after = crsr->next;
        
        for(int j = 0; j<size-1-i; j++){
            if(crsr->x>after->x){
                T temp = crsr->x;
                crsr->x = after->x;
                after->x = temp;
            }
            crsr = crsr->next;
            after = crsr->next;
        }
    }
}

template <class T>
void linkedList<T>::deleteNode(T val){
    node *prev, *crsr;
    crsr = head;
    if (head->x == val) {
        head = head->next;
        delete crsr;
    }
    crsr = prev = head;
    while (crsr != NULL) {
        if (crsr->x == val) {
            prev->next = crsr->next;
            delete crsr;
            crsr = prev->next;
        }else{
            prev = crsr;
            crsr = crsr->next;
        }
    }
}

template <class T>
linkedList<T>::~linkedList(){
    node* crsr = head;
    while( crsr != NULL ) {
        node* next = crsr->next;
        delete crsr;
        crsr = next;
    }
    head = NULL;
}

template <class T>
bool linkedList<T>::searchList(T val, node* crsr){
    if(crsr!=NULL){
        if (crsr->x != val) {
            return searchList(val, crsr->next);
        }else{
            return true;
        }
    }
    return false;
}

template <class T>
linkedList<T> linkedList<T>::compareLists(const linkedList& l2){
    linkedList lhs;
    node* crsr = head;
    while (crsr!=NULL) {
        if (searchList(crsr->x, l2.head)) {
            lhs.push(crsr->x);
        }
        crsr = crsr->next;
    }
    return lhs;
}


#endif /* LinkedList_h */

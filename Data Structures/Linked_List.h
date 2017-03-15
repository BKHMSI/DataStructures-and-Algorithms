//
//  Linked_List.h
//  CS110
//
//  Created by Badr AlKhamissi on 5/4/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __CS110__Linked_List__
#define __CS110__Linked_List__

#include <stdio.h>
#include <iostream>
using namespace std;

/**** LINKED LIST CLASS ***/
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
    
    node* getHead(){return head;} // Function to return head of list
    
    // Overload function to SearchList to keep head private
    bool searchList(T, node*);
    // Overload function to displayReversed to keep head private
    void displayReversed(node*);

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
    void displayReversed() { displayReversed(getHead());};
    int getSize();
    bool searchList(T val) { return searchList(val,getHead());};
    linkedList compareLists(const linkedList&);
};

// Constructor
template <class T>
linkedList<T>::linkedList(){
    head = NULL;
    prev = head;
}

/* 
 Overload Constructor
 Parameters:
    val -> value inserted in the head of the list
 */
template <class T>
linkedList<T>::linkedList(T val){
    head = new node;
    head->x = val;
    head->next = NULL;
    prev = head;
}


/*
 Copy Constructor
 Parameters:
 rhs -> linked list to be copied into self
 */
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

// Destructor
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

/*
 Overload = operator 
 Parameters:
 rhs -> linked list to be copied into self
*/
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

/*
 Insert value to Linked list
 Parameters:
 val -> value to be inserted to end of list
 */
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

// Remove last value in list
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

// Display List
template <class T>
void linkedList<T>::display(){
    node *crsr;
    crsr = head;
    while (crsr!=NULL) {
        cout<<crsr->x<<" ";
        crsr = crsr->next;
    }
}

/*
 Display List in reverse using a recursive manner
 Parameters:
    crsr -> current pointer in list
 */
template <class T>
void linkedList<T>::displayReversed(node* crsr){
    if (crsr!=NULL) {
        displayReversed(crsr->next);
        cout<<crsr->x<<" ";
    }
}

/*
 Overloading [] to access specific element in list
 Parameters:
 index -> index of node to be accessed, 0 base
 */
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

// Return size of list
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


// Sort list using values
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

/*
 Delete node by value
 Parameters:
    val -> value of the node to be deleted
 */
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

/*
 Searching list
 Parameters:
    val -> value of the node to be searched
    crsr -> current pointer in list
 */
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

/*
 Adds common elements to a thrid list then return it
 Parameters:
    l2 -> list to be compared against self
*/
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

#endif /* defined(__CS110__Linked_List__) */

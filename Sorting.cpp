//
//  main.cpp
//  Sorting
//
//  Created by Badr AlKhamissi on 2/9/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

void selectionSort(int[]);
void insertionSort(int A[]);
void bubbleSort(int A[]);
void quickSort(int[], int, int);
void QuickSort(int[], int, int);
void swapA(int&, int&);
void displayArray(int A[]);
void displayArray(int A[],int,int);
int partition(int[], int, int);
const int size = 6;

int main(int argc, const char * argv[]) {
 
    int A[size] = {};
    srand(unsigned(time(NULL)));
    
    // Init Array
    for (int i = 0; i<size; i++)
        A[i] = rand()%10;
    
    // Output Before
    displayArray(A);
    
    /* Functions */
    
    //selectionSort(A);
    //bubbleSort(A);
    //quickSort(A, 0, size);
    //insertionSort(A);
    QuickSort(A, 0, size);
    
    
    
    //Output After
    displayArray(A);
    

    return 0;
}

// Selection Sort or Sequential Sort
void selectionSort(int A[]){
    for (int i = 0; i<size-1; i++) {
        int ptr = i;
        for (int j = i+1; j<size; j++) {
            if (A[j]<A[ptr]) {
                ptr = j;
            }
        }
        displayArray(A);
        swapA(A[ptr], A[i]);
    }
}

//Bubble Sort
void bubbleSort(int A[]){
    for (int i = 0; i<size-1; i++) {
        bool swapped = false;
        for (int j = 0; j<size-i-1; j++) {
            if (A[j]>A[j+1]) {
                swapA(A[j], A[j+1]);
                swapped = true;
            }
        }
        if(!swapped) break;
        displayArray(A);
    }
}

//Insertion Sort
void insertionSort(int A[]){
    int j, v;
    for (int i = 1; i < size; i++){
        j = i, v = A[i];
        while (j > 0 && v < A[j-1]){
            A[j] = A[j-1];
            j--;
        }
        A[j] = v;
        displayArray(A);
    }
}

int partition(int arr[], int p, int r){
    int pivot = arr[p];       // pivot is the first element
    int i = p-1;    int j = r+1;
    while (true)
    {
        do {j--;} while (arr[j] > pivot);
        do {i++;} while (arr[i] < pivot);
        if(i < j)  swapA(arr[i] , arr[j]);
        else return j;
    }
    // j is the location of last element in left part
}

void QuickSort (int arr[], int p , int r){
    if (p < r){
        int q = partition(arr,p,r);
        displayArray(arr);
        QuickSort(arr,p,q);
        QuickSort(arr,q+1,r);
        displayArray(arr);
    }
}

// QuickSort
void quickSort(int arr[], int left, int right)
{
    int i = left, j = right;
    int pivot = (abs(left + right) / 2);
    
    /* partition */
    while (i <= j) {
        while (arr[i] < arr[pivot])
            i++;
        while (arr[j] > arr[pivot])
            j--;
        if (i <= j) {
            swapA(arr[i], arr[j]);
            i++;
            j--;
            
        }
    }
    
    cout<<"Pivot: "<<arr[pivot]<<endl;
    displayArray(arr);
    
    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    
    if (i< right)
        quickSort(arr, i, right);
}


void swapA(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void displayArray(int A[], int n, int m){
    for (int i = n; i<m; i++) {
        cout<< A[i]<<" ";
    }
    cout<<endl;
}

void displayArray(int A[]){
    for (int i = 0; i<size; i++) {
        cout<< A[i]<<" ";
    }
    cout<<endl;
}


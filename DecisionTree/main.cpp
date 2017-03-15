//
//  main.cpp
//  DecisionTree
//
//  Created by Badr AlKhamissi on 10/10/16.
//  Copyright © 2016 Badr AlKhamissi. All rights reserved.
//

#include <iostream>
#include "DecisionTree.h"
using namespace std;


int main(int argc, const char * argv[]) {
    string path = "DT_Dataset.txt";
    DT dt(path);
    dt.train();
    dt.printTree();
    
    const int n = 4;
    vector<string>test;
    string input[4] = {"Sunny","Cold","Normal","FALSE"};
    //string input[4] = {"<=30","Medium","No","Fair"};
    
    for(int i = 0; i<n; i++)
        test.push_back(input[i]);
    
    cout<<"Class: "<<dt.classify(test)<<endl;
    dt.printPredicateForm();

    return 0;
}

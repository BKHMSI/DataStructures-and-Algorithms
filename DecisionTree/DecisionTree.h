//
//  DecisionTree.h
//  DecisionTree
//
//  Created by Badr AlKhamissi on 10/10/16.
//  Copyright © 2016 Badr AlKhamissi. All rights reserved.
//

#ifndef DecisionTree_h
#define DecisionTree_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>

using namespace std;

#define vec vector
#define mp(x,y) make_pair(x,y)

class DT {
    vec<vec<string>>X; // Data
    vec<string>Y; // Class
    vec<string>A; // Attributes
    
    vec<string>Rules;
    int m,n,c;
    float accuracy;
    string vote;
    struct node{
        string label;
        int idx;
        vec<pair<node*,string>>branches;
    };
    node* root;
    vec<node*>roots;
    node* constructTree(vec<vec<string>>,vec<string>,vec<string>);
    int attrSelection(vec<vec<string>>,vec<string>,int)const;
    float info(vec<vec<string>>,vec<string>)const;
    float entropy(int,vec<vec<string>>,vec<string>)const;
    float calcInfo(map<string,int>,vec<string>)const;
    pair<float,int> info(int,string,vec<vec<string>>,vec<string>)const;
    float gain(int,vec<vec<string>>,vec<string>)const;
    void printTree(node*,int)const;
    void generateRules(node*)const;
    int getAttrIndex(string)const;
    string classify(vec<string>,node*)const;
    void printPredicateForm(node*,int);
public:
    DT(string);
    bool readData(string);
    void dispData()const;
    bool sameClass(vec<string>)const;
    void train();
    int attrSelection()const{return attrSelection(X, Y, (int)A.size());};
    string attrSelectionStr()const{return A[attrSelection()];}
    vec<string>getRowAt(int)const;
    void removeAttr(int);
    string majorityVoting()const;
    vec<vec<string>> getSubTree(vec<vec<string>>,string,int);
    vec<string> getClassSubTree(vec<vec<string>>,vec<string>,string,int);
    vec<string> getAttrSubTree(vec<string>,string,int);
    void printTree()const{printTree(root,0);};
    void constructTree();
    set<string>getUnique(vec<vec<string>>,int)const;
    void generateRules()const{generateRules(root);};
    //string classify(vec<string> z)const{return classify(z, roots[0]);};
    string classify(vec<string>)const;
    void printPredicateForm();
    float getPredecitiveAccuracy()const{return accuracy;}
};

DT::DT(string file){
    m = n = accuracy = 0;
    if(!readData(file))
        cerr<<"Can't Open File"<<endl;
    else
        vote = majorityVoting();
}

void DT::train(){
    vec<vec<string>>XX;
    vec<string>YY;
    int error = 0;
    string res;
    for(int j = 0; j<X.size(); j++){
        for(int i = 0; i<X.size(); i++){
            if(i!=j){
               XX.push_back(X[i]);
               YY.push_back(Y[i]);
            }
        }
        roots.push_back(constructTree(XX,YY,A));
        res = classify(X[j], roots[j]);
        if(res!=Y[j]) error++;
        YY.clear();
        XX.clear();
    }
    accuracy = 100-((X.size()-error) / float(X.size()))*100;
    root = roots[0];
}

string DT::classify(vec<string>z)const{
    map<string,int>res;
    map<string,int>::iterator it;
    for(int i = 0; i<roots.size(); i++){
        res[classify(z, roots[i])]++;
    }
    it = res.end();
    return (--it)->first;
}

string DT::classify(vec<string>z,node*curr)const{
    for(int i = 0; i<curr->branches.size(); i++){
        if(curr->branches[i].first == nullptr)
            break;
        if(z[curr->idx] == curr->branches[i].second)
            return classify(z, curr->branches[i].first);
    }
    return curr->label;
}

void DT::constructTree(){
    root = constructTree(X, Y, A);
    cout<<"\nTree Constructed\n\n";
}

DT::node* DT::constructTree(vec<vec<string>>x,vec<string>y,vec<string>a){
    node* curr = new node;
    
    if(!a.size() || !y.size()){
        curr->label = vote;
        curr->idx = -1;
        curr->branches.push_back(make_pair(nullptr,""));
        return curr;
    }
    
    if(y.size() && sameClass(y)){
        curr->label = y[0];
        curr->idx = -1;
        curr->branches.push_back(make_pair(nullptr,""));
        return curr;
    }
    
    // Split
    int attr = attrSelection(x,y,(int)a.size());
    curr->label = a[attr];
    curr->idx = getAttrIndex(a[attr]);
    set<string> s = getUnique(x,attr);
    set<string>::iterator it;
    for(it = s.begin(); it!=s.end(); it++){
        curr->branches.push_back(
            make_pair(
                constructTree(
                    getSubTree(x, *it, attr),
                    getClassSubTree(x,y,*it,attr),
                    getAttrSubTree(a, *it, attr)
            ),*it)
        );
    }
    
    return curr;
}


vec<vec<string>> DT::getSubTree(vec<vec<string>>x,string val,int idx){
    if(idx < 0 || idx >= m) throw 0;
    vec<vec<string>> sub;
    int i,j;
    for(i = 0; i<x.size(); i++){
        vec<string>tmp;
        if(x[i][idx] == val){
            for(j = 0; j<x[i].size(); j++){
                if(j!=idx) tmp.push_back(x[i][j]);
            }
            sub.push_back(tmp);
        }
    }
   
    return sub;
}

vec<string> DT::getClassSubTree(vec<vec<string>>x,vec<string>y, string val,int idx){
    if(idx < 0 || idx >= m) throw 0;
    vec<string> sub;
    for(int i = 0; i<x.size(); i++)
        if(x[i][idx] == val)
            sub.push_back(y[i]);
    return sub;
}

vec<string> DT::getAttrSubTree(vec<string>a,string val,int idx){
    if(idx < 0 || idx >= m) throw 0;
    vec<string> sub;
    for(int i = 0; i<a.size(); i++)
        if(i!=idx)
            sub.push_back(a[i]);
    return sub;
}

int DT::attrSelection(vec<vec<string>>x,vec<string>y,int sz)const{
    float max = gain(0,x,y);
    int idx = 0;
    float g = 0;
    for(int i = 1; i<sz-1; i++){
        g = gain(i,x,y);
        if(g>max){
            max = g;
            idx = i;
        }
    }
    return idx;
}

float DT::gain(int idx,vec<vec<string>>x,vec<string>y)const{
    return info(x,y) - entropy(idx,x,y);
}

float DT::info(vec<vec<string>>x,vec<string>y)const{
    map<string,int>vote;
    for(int i = 0;i<y.size(); i++)
        vote[y[i]]++;
    
    return calcInfo(vote,y);
}

pair<float,int> DT::info(int idx, string val, vec<vec<string>>x, vec<string>y)const{
    map<string,int>count;
    int cnt = 0;
    for(int i = 0; i<x.size(); i++)
        if(x[i][idx] == val)
            count[y[i]]++, cnt++;
    return make_pair(calcInfo(count,y),cnt);
}



float DT::entropy(int idx,vec<vec<string>>x, vec<string>y)const{
    set<string>vis;
    float acc = 0;
    for(int i = 0; i<x.size(); i++){
        if(!vis.count(x[i][idx])){
            pair<float,int> res = info(idx,x[i][idx],x,y);
            acc+= (((res.second)/float(y.size())) * (res.first));
            vis.insert(x[i][idx]);
        }
    }
    return acc;
}

bool DT::sameClass(vec<string>labels)const{
    string y = labels[0];
    for(int i = 1; i<labels.size(); i++)
        if(labels[i] != y)
            return false;
    return true;
}

set<string> DT::getUnique(vec<vec<string>>x,int idx)const{
    set<string>s;
    for(int i = 0; i<x.size(); i++)
        s.insert(x[i][idx]);
    return s;
}

vec<string> DT::getRowAt(int idx)const{
    vector<string> v;
    if(idx < 0 || idx >= m)
        throw 0;
    for(int i = 0; i<n; i++)
        v.push_back(X[i][idx]);
    return v;
}

void DT::removeAttr(int idx){
    if(idx < 0 || idx >= m)
        throw 0;
    Y.erase(Y.begin()+idx);
    A.erase(A.begin()+idx);
    for(int i = 0; i<n; i++)
        X[i].erase(X[i].begin()+idx);
    m--;
}

string DT::majorityVoting()const{
    map<string,int>vote;
    map<string,int>::iterator it;
    for(int i = 0;i<Y.size(); i++)
        vote[Y[i]]++;
    return (--vote.end())->first;
}


float DT::calcInfo(map<string,int> count,vec<string>y)const{
    map<string,int>::iterator it;
    float acc = 0;
    for(it = count.begin(); it!=count.end(); it++)
        acc += (- ((it->second) /float((y.size())))  * log2(((it->second) /float((y.size())))));
    return acc;
}

void DT::printTree(node* root,int depth)const{
    if(root!=nullptr){
        for(int j = 0; j<depth; j++) cout<<"\t";
        cout<<root->label;
        if(root->branches[0].first != nullptr) cout<<endl;
        for(int i = 0; i<root->branches.size(); i++){
            for(int j = 0; j<depth+1; j++) cout<<"\t";
            cout<<root->branches[i].second<<endl;
            printTree(root->branches[i].first,depth+1);
        }
    }else{
        for(int j = 0; j<depth-1; j++) cout<<"\t";
        for(int i = 0; i<5; i++) cout<<"--";
        cout<<endl;
    }
}

void DT::generateRules(node*)const{
    
}


int DT::getAttrIndex(string attr)const{
    for(int i = 0; i<A.size(); i++)
        if(A[i] == attr)
            return i;
    return -1;
}


/**
 File Format CSV
 Attribute names first row
 Class labels last column
**/

bool DT::readData(string file){
    ifstream read;
    stringstream ss;
    string val;
    vector<string>tmp;
    set<string>count;
    int i = 1;
    read.open(file.c_str());
    if(read.fail())
        return false;
    
    getline(read,val);
    ss.str(val);
    while(getline(ss,val,','))
        A.push_back(val), m++;
    
    ss.clear();
    while((!read.eof() && getline(read,val))){
        ss.str(val);
        while(getline(ss,val,','))
            (i == m ? Y.push_back(val):tmp.push_back(val)),i++;
        i = 1;
        count.insert(Y[n]);
        X.push_back(tmp), n++;
        ss.clear();
        tmp.clear();
    }
    
    c = (int)count.size(); // # of classes
    
    return true;
}

void DT::dispData()const{
    int i,j;
    
    for(i = 0; i<m; i++)
        cout<<A[i]<<setw(4)<<(i==m-1)[" \n"];
    
    for(i = 0; i<m*5; i++)
        cout<<(i==m*5-1 ? "\n":"--");
    
    for(i = 0; i<n; i++){
        for(j = 0; j<m; j++){
            if(j == m-1) cout<<Y[i]<<endl;
            else cout<<X[i][j]<<setw(10);
        }
    }
}

void DT::printPredicateForm(){
    cout<<"\nRules: \n";
    printPredicateForm(root,0);
    cout<<endl;
}

void DT::printPredicateForm(node* root, int depth){
    if(root->branches[0].first !=nullptr){
        for(int j = 0; j<root->branches.size(); j++){
            for(int k = 0; k<depth && j!=0  ; k++) cout<<"\t";
            stringstream ss;
            ss<<root->label <<" is "<<root->branches[j].second;
            if(root->branches[j].first->branches[0].first != nullptr)
                ss<<" and ";
            cout<<ss.str();
            printPredicateForm(root->branches[j].first, depth+1);
        }
    }else{
        cout<<" => "<<root->label<<endl;;
    }
}




#endif /* DecisionTree_h */

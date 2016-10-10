//
//  BST.h
//  CS210
//
//  Created by Badr AlKhamissi on 11/11/15.
//  Copyright © 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <queue>


using namespace std;


template<class keyT, class dataT>
class node{
public:
    node(){left = right = NULL;}
    node(keyT key, dataT data){this->data = data; this->key = key; left = right = NULL;}
    keyT key;
    dataT data;
    node* left;
    node* right;
};

template<class keyT, class dataT>
class BST {
private:
    
    int sz, idx;
    node<keyT,dataT>* root;
    node<keyT,dataT>** arr;
    bool insert(node<keyT,dataT>*&, keyT key, dataT data);
    bool isEmpty(node<keyT,dataT>*)const{return root;};
    bool retrieve(node<keyT,dataT>*&, keyT key, dataT data)const;
    bool isIdentical(node<keyT,dataT>*, node<keyT,dataT>*);
    node<keyT,dataT>* remove(node<keyT,dataT>*&, keyT key);
    node<keyT,dataT>* getParent(keyT);
    node<keyT,dataT>* copyTree(node<keyT,dataT>*);
    node<keyT,dataT>* search(node<keyT,dataT>*, keyT)const;
    node<keyT,dataT>* inOrderSx(node<keyT,dataT>*);
    void inOrder(node<keyT,dataT>*);
    void preOrder(node<keyT,dataT>*);
    void postOrder(node<keyT,dataT>*);
    void lvlOrder(node<keyT,dataT>*);
    void backTraverse(node<keyT,dataT>*);
    keyT getMinKey(node<keyT,dataT>*);
    keyT getMaxKey(node<keyT,dataT>*);
    void getMedKey(node<keyT,dataT>*, int&, keyT&);
    int internal(node<keyT,dataT>*);
    int leaves(node<keyT,dataT>*);
    int size(node<keyT,dataT>*);
    void copyNodes(node<keyT,dataT>*&,node<keyT,dataT>*&);
    void displayLevel(int,int,int,int);
    int getHeight(node<keyT,dataT>*);
    int countKeysLarger(node<keyT,dataT>*, keyT);
public:
    BST();
    BST(const BST<keyT,dataT>&);
    bool insert(keyT key, dataT data);
    bool isEmpty()const{return isEmpty(root);};
    bool search(keyT key){ return search(root,key) ? true:false;};
    bool retrieve(keyT key, dataT data)const;
    void remove(keyT key);
    void inOrder(){idx = 0; delete arr; arr = new node<keyT,dataT>*[sz]; inOrder(root);};
    void preOrder(){idx = 0; delete arr; arr = new node<keyT,dataT>*[sz]; preOrder(root);};
    void postOrder(){idx = 0; delete arr; arr = new node<keyT,dataT>*[sz]; postOrder(root);};
    void lvlOrder(){idx = 0; delete arr; arr = new node<keyT,dataT>*[10]; lvlOrder(root);};
    void backTraverse(){idx = 0; delete arr; arr = new node<keyT,dataT>*[sz]; backTraverse(root);};
    node<keyT,dataT>* getRoot()const{return root;};
    int getHeight(){return getHeight(root);};
    keyT getMinKey(){return getMinKey(root);};
    keyT getMaxKey(){return getMaxKey(root);};
    keyT getMedKey(){ int cnt = size(); keyT key; getMedKey(root,cnt, key); return key;};
    node<keyT,dataT>* operator [](int i){return *(arr+i);}
    bool operator == (const BST<keyT,dataT>&);
    void display();
    int internal(){ return internal(root);};
    int leaves(){return leaves(root);};
    int size(){return size(root);};
    int countKeyLarger(keyT k){return countKeysLarger(root, k);};
    
    bool destroy(keyT key);
};




template<class keyT, class dataT>
BST<keyT, dataT>::BST(){
    sz = 0;
    root = NULL;
}

template<class keyT, class dataT>
BST<keyT, dataT>::BST(const BST<keyT,dataT>& bst){
    root = copyTree(bst.getRoot());
}

template<class keyT, class dataT>
node<keyT, dataT>* BST<keyT, dataT>::copyTree(node<keyT,dataT>* root){
    if (root) {
        node<keyT, dataT>* newTree = new node<keyT,dataT>;
        newTree->key = root->key;
        newTree->data = root->data;
        newTree->left = copyTree(root->left);
        newTree->right = copyTree(root->right);
        return newTree;
    }else{
        return NULL;
    }
}

template<class keyT, class dataT>
bool BST<keyT, dataT>::operator==(const BST<keyT, dataT>& rhs){
    return isIdentical(root, rhs.getRoot());
}


template<class keyT, class dataT>
bool BST<keyT, dataT>::isIdentical(node<keyT,dataT>* lhs, node<keyT,dataT>* rhs){
    if (lhs && rhs) {
        return isIdentical(lhs->left, rhs->left);
        if(lhs->key != rhs->key) return false;
        return isIdentical(lhs->right, rhs->right);
    }else if((!lhs && rhs) || (!rhs && lhs))
        return false;
    else
        return true;
}

template<class keyT, class dataT>
bool BST<keyT, dataT>::insert(keyT key, dataT data){
    return (sz++,insert(root, key, data));
}

template<class keyT, class dataT>
bool BST<keyT, dataT>::insert(node<keyT,dataT>* &ptr, keyT key, dataT data){
    if(!ptr){
        ptr = new node<keyT,dataT>(key,data);
        return true;
    }else if (ptr->key == key)
        return false;
    else if(key<ptr->key)
        return insert(ptr->left,key, data);
    else
        return insert(ptr->right,key, data);
    
}

template<class keyT, class dataT>
node<keyT,dataT>* BST<keyT, dataT>::search(node<keyT,dataT>* ptr, keyT key)const{
    if(!ptr){
        return NULL;
    }else if (ptr->key == key)
        return ptr;
    else if(key<ptr->key)
        return search(ptr->left, key);
    else
        return search(ptr->right, key);
}

template<class keyT, class dataT>
void BST<keyT, dataT>::remove(keyT key){
    if(remove(root, key))
        sz--;
}

template<class keyT, class dataT>
node<keyT,dataT>* BST<keyT, dataT>::remove(node<keyT,dataT>*& root, keyT key){
    node<keyT,dataT>* save;
    if(root == NULL)
        return NULL;
    if(root->key == key){
        if(root->right == NULL && root->left == NULL){
            free(root);
            return NULL;
        }
    }else if(root->right == NULL || root->left == NULL){
        if(root->right == NULL){
            save = root->left;
            free(root);
            return save;
        }else{
            save = root->right;
            free(root);
            return save;
        }
    }else{
        save = getParent(key);
        root->key = save->key;
        root->left = remove(root->left, key);
        return root;
    }
    
    if(root->key < key){
        root->right = remove(root->right, key);
    }else if(root->key > key){
        root->left = remove(root->left, key);
    }
    return root;
}

template<class keyT, class dataT>
void BST<keyT, dataT>::inOrder(node<keyT,dataT>* t){
    if (t){
        if(t->left) inOrder(t->left);
        *(arr+idx) = t;
        idx++;
        cout<<t->key<<" ";
        if(t->right)inOrder(t->right);
    }
}

template<class keyT, class dataT>
void BST<keyT, dataT>::preOrder(node<keyT,dataT>* t){
    if (t){
        *(arr+idx) = t;
        idx++;
        if(t->left) preOrder(t->left);
        if(t->right)preOrder(t->right);
    }
}

template<class keyT, class dataT>
void BST<keyT, dataT>::postOrder(node<keyT,dataT>* t){
    if (t){
        if(t->left) postOrder(t->left);
        if(t->right)postOrder(t->right);
        *(arr+idx) = t;
        idx++;
    }
}

template<class keyT, class dataT>
void BST<keyT, dataT>::lvlOrder(node<keyT,dataT>* root){
    queue<pair<node<keyT,dataT>*, int>>q;
    q.push(make_pair(root,0));
    node<keyT,dataT>* tmp;
    int height = getHeight();
    while (q.size()) {
        tmp = q.front().first;
        int lvl = q.front().second;
        *(arr+idx) = tmp;
        idx++;
        q.pop();
        
    
        if(tmp){
            // Complete Later
            if(!tmp->left && !tmp->right){
                int x = idx, l = lvl;
                while (l<=height) {
                    *(arr+2*x) = nullptr;
                    *(arr+2*x+1) = nullptr;
                    x*=2;
                    l++;
                }
            }
            
            if (tmp->left)
                q.push(make_pair(tmp->left,lvl+1));
            else
                q.push(make_pair(nullptr, lvl+1));

            if (tmp->right)
                q.push(make_pair(tmp->right,lvl+1));
            else
                q.push(make_pair(nullptr,lvl+1));
        }
    }
}

template<class keyT, class dataT>
void BST<keyT, dataT>::backTraverse(node<keyT,dataT>* root){
    if (root){
        if(root->right) backTraverse(root->right);
        *(arr+idx) = root;
        idx++;
        if(root->left) backTraverse(root->left);
        
    }
}

template<class keyT, class dataT>
node<keyT,dataT>* BST<keyT, dataT>::getParent(keyT key){
    node<keyT,dataT>* p = NULL, *x = root;
    bool found = false;
    while (!found && x) {
        if(key<x->key){
            p = x;
            x = x->left;
        }else if(key>x->key){
            p = x;
            x = x->right;
        }else{
            found = true;
        }
    }
    return p;
}

template<class keyT, class dataT>
bool BST<keyT, dataT>::destroy(keyT key){
    if(root){
        if(root->key == key){
            // Delete Root
            node<keyT,dataT>* sx = inOrderSx(root);
            node<keyT,dataT>* parent = getParent(sx->key);
            copyNodes(root, sx);
            if(parent->right->key == key)
                parent->right = sx->left;
            else
                parent->left = sx->left;
            delete sx;
            return true;
        }else{
            node<keyT,dataT>* xx = search(root, key);
            if(xx){
                // Delete Leaf Node
                node<keyT,dataT>* parent = getParent(key);
                if(!xx->left && !xx->right){
                    parent->right->key == key ? parent->right = NULL : parent->left = NULL;
                    delete xx;
                    idx--;
                    return true;
                }else if(xx->right || xx->left){
                 // Delete Internal Node
                    node<keyT,dataT>* sx = inOrderSx(xx);
                    parent = getParent(sx->key);
                    if(parent->right){
                        if(parent->right->key == sx->key)
                            parent->right = NULL;
                        else
                            parent->left = NULL;
                    }else{
                        parent->left = NULL;
                    }
         
                    copyNodes(xx, sx);
                    delete sx;
                    idx--;
                    return true;
                }
            }else{
                return false;
            }
        }
    }
    return false;
}

template<class keyT, class dataT>
node<keyT,dataT>* BST<keyT, dataT>::inOrderSx(node<keyT,dataT>* ptr){
    if(ptr->left){
        ptr = ptr->left;
        while (ptr->right)
            ptr = ptr->right;
        return ptr;
    }else if(ptr->right){
        ptr = ptr->right;
        while(ptr->left)
            ptr = ptr->left;
        return ptr;
    }else{
        return NULL;
    }
}

template<class keyT, class dataT>
void BST<keyT, dataT>::copyNodes(node<keyT,dataT>*& node1,node<keyT,dataT>*& node2){
    node1->key = node2->key;
    node1->data = node2->data;
};


template<class keyT, class dataT>
keyT BST<keyT, dataT>::getMinKey(node<keyT,dataT>* root){
    if (!(root->left))
        return root->key;
    else
        return getMinKey(root->left);
}

template<class keyT, class dataT>
void BST<keyT, dataT>::getMedKey(node<keyT,dataT>* root, int& cnt, keyT& med){
    if(root){
        if(root->left)
             getMedKey(root->left, cnt, med);
        cnt--;
        if(size()/2 == cnt)
             med = root->key;
        if(root->right)
             getMedKey(root->right, cnt, med);
    }
}

template<class keyT, class dataT>
keyT BST<keyT, dataT>::getMaxKey(node<keyT,dataT>* root){
    if (!root->right)
        return root->key;
    else
        return getMaxKey(root->right);
}


template<class keyT, class dataT>
int BST<keyT, dataT>::internal(node<keyT,dataT>* root){
    if(!root){
        return 0;
    }else if(root->left || root->right){
        return 1+internal(root->left)+internal(root->right);
    }
    return 0;
}

template<class keyT, class dataT>
int BST<keyT, dataT>::leaves(node<keyT,dataT>* root){
    if(!root){
        return 0;
    }else if(!root->left && !root->right){
        return 1;
    }
    return leaves(root->left)+leaves(root->right);
}

template<class keyT, class dataT>
int BST<keyT, dataT>::getHeight(node<keyT,dataT>* root){
    if(!root)
        return 0;
    else
        return 1 + max(getHeight(root->left),getHeight(root->right));
}

template<class keyT, class dataT>
int BST<keyT, dataT>::size(node<keyT,dataT>* root){
    if(!root){
        return 0;
    }else{
        return 1+size(root->left)+size(root->right);
    }
}

template<class keyT, class dataT>
int BST<keyT, dataT>::countKeysLarger(node<keyT,dataT>* root, keyT k){
    if(!root){
        return 0;
    }else if(root->key>=k){
        return 1+countKeysLarger(root->left,k)+countKeysLarger(root->right,k);
    }else{
        return countKeysLarger(root->left,k)+countKeysLarger(root->right,k);
    }
}

template<class keyT, class dataT>
void BST<keyT, dataT>::display(){
    lvlOrder();
    for (int i = 0; i<10; i++) {
        if(arr[i])
            cout<<arr[i]->key<<" ";
        else
            cout<<"Empty ";
    }
    cout<<endl;
    int s = 1, e = 1, rLength, k;
    int total = size();
    int nLevels = getHeight();
    lvlOrder();
    for (int lvl = 0; lvl<nLevels; lvl++) {
        displayLevel(nLevels,lvl,s,e);
        rLength = e-s+1;
        s = e + 1;
        k = e + 2*rLength;
        e = (k<total) ? k:total;
    }

}

template<class keyT, class dataT>
void BST<keyT, dataT>::displayLevel(int rows, int lvl, int s, int e){
    int skip = int(pow(2.0, rows-lvl)-1);
    for (int i = s; i<=e; i++) {
        cout<<setw(skip)<< " ";
        if(arr[i-1])
            cout<<setw(2)<< arr[i-1]->key;
        else
            cout<<setw(2)<< " ";
        cout<<setw(skip)<< " ";
    }
    cout<<"\n\n\n";

}




#endif /* BST_h */

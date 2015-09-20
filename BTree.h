#include <iostream>
#ifndef BTREE_H
#define BTREE_H

using namespace std;

class BTKey{
public:
    long key;
    int rrn;
    BTKey(long k, int r){key = k; rrn = r;};
    BTKey(){};
};

class BTreeNode{
  public:
    BTKey *keys; 
    int t; 
    BTreeNode **C; 
    int n;    
    bool leaf; 
    BTreeNode(int t, bool leaf); 
    void insertNonFull(BTKey k);
    void splitChild(int i, BTreeNode *y);
    void traverse();
    BTreeNode *search(long k); 
    int findKey(BTKey k);

    void remove(BTKey k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    BTKey getPred(int idx);
    BTKey getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    friend class BTree;
    BTKey searchBTK(long k);
};


class BTree{
    BTreeNode *root;
    int t;
public:
    BTree(int _t){  root = NULL;  t = _t; }
    void traverse(){  if (root != NULL) root->traverse(); }
    BTreeNode* search(int k){  return (root == NULL)? NULL : root->search(k); }
    void insert(BTKey);
    void remove(BTKey);
    BTKey searchBTK(int k);
};



#endif
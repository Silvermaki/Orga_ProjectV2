#include <iostream>
#include "BTree.h"
using namespace std;

void BTree::insert(BTKey k){
    if(root == NULL){
        root = new BTreeNode(t, true);
        root->keys[0] = k;  
        root->n = 1; 
    }
    else{
        if (root->n == 2*t-1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            BTKey temp = s->keys[0];
            if (temp.key < k.key)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else 
            root->insertNonFull(k);
    }
}

BTreeNode::BTreeNode(int t, bool leaf){
    this -> t = t;
    this -> leaf = leaf;
    keys = new BTKey[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}

void BTreeNode::traverse(){
    int i;
    for(i = 0; i < n; i++){
        if(leaf == false)
            C[i]->traverse();
        cout << keys[i].key << "\n";
    }
    if(leaf == false)
        C[i]->traverse();
}

BTreeNode *BTreeNode::search(long k){
    int i = 0;
    while (i < n && k > keys[i].key)
        i++;
    if (keys[i].key == k)
        return this;
    if (leaf == true)
        return NULL;
    return C[i]->search(k);
}

void BTreeNode::insertNonFull(BTKey k){
    int i = n-1;
    if (leaf == true){
        while (i >= 0 && keys[i].key > k.key){
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else{
        while (i >= 0 && keys[i].key > k.key)
            i--;
        if (C[i+1]->n == 2*t-1){
            splitChild(i+1, C[i+1]);
            if (keys[i+1].key < k.key)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y){
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    y->n = t - 1;
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
    C[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n = n + 1;
}

int BTreeNode::findKey(BTKey k){
    int idx=0;
    while (idx<n && keys[idx].key < k.key)
        ++idx;
    return idx;
}

void BTreeNode::remove(BTKey k){
    int idx = findKey(k);
    if (idx < n && keys[idx].key == k.key){
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else{
        if (leaf){
            cout << "Does not exist...\n";
            return;
        }
        bool flag = ( (idx==n)? true : false );
        if (C[idx]->n < t)
            fill(idx);
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

void BTreeNode::removeFromLeaf (int idx){
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
    n--;
    return;
}

void BTreeNode::removeFromNonLeaf(int idx){
    BTKey k = keys[idx];
    if (C[idx]->n >= t){
        BTKey pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }
    else if  (C[idx+1]->n >= t){
        BTKey succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }
    else{
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

BTKey BTreeNode::getPred(int idx){
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n-1];
}
 
BTKey BTreeNode::getSucc(int idx){
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

BTKey BTreeNode::searchBTK(long k){
    int i = 0;
    while (i < n && k > keys[i].key)
        i++;
    if (keys[i].key == k)
        return keys[i];
    if (leaf == true){
        BTKey temp(0,0);
        return temp;
    }
    return C[i]->searchBTK(k);
}

void BTreeNode::fill(int idx){
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);
    else{
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

void BTreeNode::borrowFromPrev(int idx){
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
    if (!child->leaf){
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }
    child->keys[0] = keys[idx-1];
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];
    keys[idx-1] = sibling->keys[sibling->n-1];
    child->n += 1;
    sibling->n -= 1;
    return;
}

void BTreeNode::borrowFromNext(int idx){
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];
    child->keys[(child->n)] = keys[idx];
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];
    keys[idx] = sibling->keys[0];
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];
    if (!sibling->leaf){
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
    child->n += 1;
    sibling->n -= 1;
    return;
}

void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];
    child->keys[t-1] = keys[idx];
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];
    child->n += sibling->n+1;
    n--;
    delete(sibling);
    return;
}

void BTree::remove(BTKey k){
    if (!root){
        cout << "Empty index...\n";
        return;
    }
    root->remove(k);
    if (root->n==0){
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
        delete tmp;
    }
    return;
}

BTKey BTree::searchBTK(int k){
    if (!root){
        cout << "Empty index...\n";
        BTKey temp(0,0);
        return temp;
    }
    return root->searchBTK(k);
}
#ifndef PHONE_H
#define PHONE_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "BTree.h"

using namespace std;

class phone{
  	int number;
  	string id_client;
  public:
  	phone();
  	phone(int,string);
  	int getNumber();
  	void setNumber(int);
  	string getId_client();
  	void setId_client(string);
  	vector<int> createNumbers(int);
  	vector<phone> phoneVector(vector<int>, vector<string>);
    void availAdd(phone);
    void availDelete(int);
    void saveFile(vector<phone>);
    void availList();
    void availModify(phone, int);
    void reIndex();
  	string toString();
    void checkIndex();
    BTree loadIndex();
};

#endif
#ifndef CITY_H
#define CITY_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "BTree.h"

using namespace std;

class city{
	int id_city;
	string name;
  public:
	city();
	city(int,string);
	void setId_city(int);
	int getId_city();
	void setName(string);
	string getName();
	vector<city> cityVector();
	void availDelete(int);
	string toString();
	void saveFile(vector<city>);
	void availList();
	void availModify(city, int);
	void reIndex();
	void checkIndex();
	BTree loadIndex();
	BTree addCity(city,BTree);
    void checkIndexStatus();
    void search(int);
    string search2(long);
};

#endif
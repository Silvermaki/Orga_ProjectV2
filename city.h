#ifndef CITY_H
#define CITY_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
	void availAdd(city);
	string toString();
	void saveFile(vector<city>);
	void availList();
	void availModify(city, int);
	void reIndex();
};

#endif
#ifndef CLIENT_H
#define CLIENT_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "city.h"
#include <iomanip>
#include "BTree.h"

using namespace std;

class client{
	string id_client;
	string name;
	char gender;
	int id_city;
  public:
	client();
	client(string,string,char,int);
	void setId_client(string);
	string getId_client();
	void setName(string);
	string getName();
	void setGender(char);
	char getGender();
	void setId_city(int);
	int getId_city();
	vector<int> createIds(int);
	vector<string> createNames();
	vector<string> idtoString(vector<int>);
	vector<client> clientVector(vector<string>, vector<string>, vector<city>);
	void availDelete(int);
	void saveFile(vector<client>);
	void availList();
	void availModify(client, int);
	void reIndex();
	string toString();
	void checkIndex();
	BTree loadIndex();
	BTree addClient(client,BTree);
    void checkIndexStatus();
    void search(int);
    string search2(long);
};

#endif
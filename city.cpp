#include "city.h"

using namespace std;

city::city(){
	id_city = 0;
	name = "";
}

city::city(int id_city, string name){
	this -> id_city = id_city;
	this -> name = name;
}

void city::setId_city(int id_city){
	this -> id_city = id_city;
}

int city::getId_city(){
	return id_city;
}

void city::setName(string name){
	this -> name = name;
}

string city::getName(){
	return name;
}

vector<city> city::cityVector(){
	ifstream myFile;
	string line;
	vector<city> mycities;
	myFile.open("CityNamesAndIDs.txt");
	int count = 0;
	string name;
	int ID;
	if(myFile.is_open()){
		while(getline(myFile,line)){
			if(count==0){
				name = line;
				count = 1;
			}else{
				ID = atoi(line.c_str());
				city city(ID,name);
				mycities.push_back(city);
				count = 0;
			}
		}
	}
	myFile.close();
	return mycities;
}

string city::toString(){
	stringstream ss;
	ss << id_city << "\t" << name;
	return ss.str();
}
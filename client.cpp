#include "client.h"

using namespace std;

client::client(){
	id_client = "";
	name = "";
	id_city = 0;
}

client::client(string id_client, string name, char gender, int id_city){
	this -> id_client = id_client;
	this -> name = name;
	this -> gender = gender;
	this -> id_city = id_city;
}

void client::setId_client(string id_client){
	this -> id_client = id_client;
}

string client::getId_client(){
	return id_client;
}

void client::setName(string name){
	this -> name = name;
}

string client::getName(){
	return name;
}

void client::setGender(char gender){
	this -> gender = gender;
}

char client::getGender(){
	return gender;
}

void client::setId_city(int id_city){
	this -> id_city = id_city;
}

int client::getId_city(){
	return id_city;
}

vector<int> client::createIds(int amount){//xxyywwwwooooo
	int counter = 0;
	vector<int> list;
	srand(time(NULL));
	do{
		int number = (rand()%18 + 1)*1000000 + (rand()%50 + 1)*10000 + 1900 +rand()%98;
		list.push_back(number);
		counter++;
	}while(counter < amount);
	return list;
}

vector<string> client::createNames(){
	vector<string> list;
	ifstream myFile;
	myFile.open("names.txt");
	string line;
	while(getline(myFile, line)){
		list.push_back(line);
	}
	myFile.close();
	return list;
}

vector<client> client::clientVector(vector<string> ids, vector<string> names, vector<city> cities){
	srand(time(NULL));
	vector<client> list;
	int i;
	for(i=0 ; i < ids.size() ; i++){
		int cit = rand()%30;
		char gender;
		int gen = rand()%2;
		if(gen == 1){
			gender = 'M';
		}else{
			gender = 'F';
		}
		city temp = cities.at(cit);
		list.push_back(client(ids.at(i), names.at(i), gender, temp.getId_city()));
	}
	return list;
}

vector<string> client::idtoString(vector<int> ids){
	vector<string> str_id;
	int i;
	srand(time(NULL));
	for(i = 0; i < ids.size() ; i++){
		int num = rand()%99999;
		stringstream ss;
		ss << setfill('0') << setw(8) << ids.at(i) << setfill('0') << setw(5) << num;
		str_id.push_back(ss.str());
	}
	return str_id;
}

string client::toString(){
	stringstream ss;
	ss << id_client << "\t" << name << "\t" << gender << "\t" << id_city;
	return ss.str();
}
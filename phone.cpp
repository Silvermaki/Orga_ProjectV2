#include "phone.h"

using namespace std;

phone::phone(){
	number = 0;
	id_client = "";
}

phone::phone(int number, string id_client){
	this -> number = number;
	this -> id_client = id_client;
}

int phone::getNumber(){
	return number;
}

void phone::setNumber(int number){
	this -> number = number;
}

string phone::getId_client(){
	return id_client;
}

void phone::setId_client(string id_client){
	this -> id_client = id_client;
}

vector<int> phone::createNumbers(int amount){
	int counter = 0;
	vector<int> list;
	srand(time(NULL));
	do{
		int number = 20000000 + (rand()%10)*1000000 + (rand()%10)*100000 + (rand()%10)*10000 + (rand()%10)*1000 + (rand()%10)*100 + (rand()%10)*10 + (rand()%10);
		int i, flag = 0;
		for(i = 0 ; i < counter ; i++){
			if(list.at(i) == number){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			list.push_back(number);
			counter++;
		}
	}while(counter < amount);
	return list;
}

vector<phone> phone::phoneVector(vector<int> numbers, vector<string> ids){
	vector<phone> temp;
	int i;
	for(i = 0 ; i< ids.size() ; i++){
		temp.push_back(phone(numbers.at(i), ids.at(i)));
	}
	return temp;
}

string phone::toString(){
	stringstream ss;
	ss << number << "\t" << id_client;
	return ss.str();
}
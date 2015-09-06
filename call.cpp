#include "call.h"

using namespace std;

call::call(){
	number = 0;
	start = 0;
	end = 0;
	destination = 0;
}

call::call(int number,long start,long end,int destination){
	this -> number = number;
	this -> start = start;
	this -> end = end;
	this -> destination = destination;
}

int call::getNumber(){
	return number;
}

void call::setNumber(int number){
	this -> number = number;
}

long call::getEnd(){
	return end;
}

void call::setEnd(long end){
	this -> end = end;
}

long call::getStart(){
	return start;
}

void call::setStart(long start){
	this -> start = start;
}

int call::getDestination(){
	return destination;
}

void call::setDestination(int destination){
	this -> destination = destination;
}

vector<int> call::createCallStart(int amount){  //YYYYMMDDHHMMSS
	int counter = 0;
	vector<int> list;
	srand(time(NULL));
	do{
		int number = (rand()%12 + 1)*100000000 + (rand()%31 + 1)*1000000 + (rand()%24)*10000 + rand()%60*100 + rand()%60;
		list.push_back(number);
		counter++;
	}while(counter < amount);
	return list;
}

vector<int> call::createCallEnd(int amount, vector<int> start){  //YYYYMMDDHHMMSS
	int counter = 0;
	vector<int> list;
	srand(time(NULL));
	do{
		int number = start.at(counter)/1000000;
		number = number * 1000000;
		number = number + (rand()%24)*10000 + rand()%60*100 + rand()%60;
		if(number > start.at(counter)){
			list.push_back(number);
			counter++;
		}
	}while(counter < amount);
	return list;
}

vector<call> call::callVector(vector<int> numbers, vector<long> starting, vector<long> ending ){
	vector<call> lists;
	int i;
	srand(time(NULL));
	int num;
	int des;
	for(i = 0; i < starting.size() ; i++){
		do{
			num = rand()%500;
			des = rand()%500;
		}while(num-des == 0);
		lists.push_back(call(numbers.at(num), starting.at(i), ending.at(i), numbers.at(des)));
	}
	return lists;
}

vector<long> call::startLong(vector<int> starting){
	int i;
	vector<long> temp;
	for(i = 0; i<starting.size(); i++){
		long temp2 = 20150000000000 + starting.at(i);
		temp.push_back(temp2);
	}
	return temp;
}

vector<long> call::endLong(vector<int> ending){
	int i;
	vector<long> temp;
	for(i = 0; i<ending.size(); i++){
		long temp2 = 20150000000000 + ending.at(i);
		temp.push_back(temp2);
	}
	return temp;
}

string call::toString(){
	stringstream ss;
	ss << number << "\t" << start<< "\t" << end << "\t" << destination;
	return ss.str();
}

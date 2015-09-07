//calls_vector header.size() = 128
//call.size = 58
#include "call.h"
#include <iomanip>

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

void call::availDelete(int rrn){
	fstream is("calls_vector.txt");
	if(is.is_open()){
		char * buffer = new char;
		int offset=128+rrn*58;//calculate offset.
		is.seekg(offset);//Move get cursor to offset.
		is.read(buffer,1);//Read 1 byte
		if(*buffer == '_'){//Check if already deleted.
			delete[] buffer;
			is.seekp(offset);//Move the put cursor towards the deleted registry.
			is.write("*",1);//Mark the registry as deleted.
			is.seekg(11);//Move the get cursor to the old value from the avail list header.
			char * buffer2 = new char(7);
			is.read(buffer2,7);//Save the value to a buffer.
			stringstream ss;
			ss << setfill(' ') << setw(7) << rrn;
			string temp = ss.str();//Save the new value for the avail list header.
			is.seekp(11);//Move the put cursor to the avail list header.
			is.write(temp.c_str(),7);//Overwrite avail list header.
			is.seekp(offset+2);//Move the put cursor to the next deleted reference of the registry.
			is.write(buffer2,7);//Overwrite it with the old value of the avail list header.
			delete[] buffer2;
			
		}else{
			cout << "Invalid value, registry does not exist or is already deleted -calls_vector.txt- \n";
		}
		is.close();	
	}else{
		cout << "Could not open file -calls_vector.txt- \n";
	}
}

void call::availAdd(call x){
	fstream is("cities_vector.txt");
	if(is.is_open()){
		char * buffer = new char(7);
		is.seekg(11);//Move get cursor to avail list header
		is.read(buffer,7);//Save avail list value
		stringstream ss;
		ss << buffer;
		string temp = ss.str();
		if(temp=="      0"){//Check if avail list header is empty
			is.seekp(0,ios_base::end);//Move to the end of the file
			stringstream ss2;
			ss2 << "_ " << "        "<< x.getNumber() << ' '<< x.getStart() << ' '<< x.getEnd() << ' '<< x.getDestination() << "\n";//Save added call to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),58);//Append added city
		}else{
			int rrn = atoi(temp.c_str());
			int offset=128+rrn*58;//calculate offset.
			is.seekp(offset+2);//Move the put cursor to the next deleted reference of the registry.
			char * buffer2 = new char(7);
			is.read(buffer2,7);//Save the value to a buffer.
			is.seekp(11);//Move the put cursor to the avail list header.
			is.write(buffer2,7);//Overwrite avail list header.
			is.seekp(offset);//Move back to offset.
			stringstream ss2;
			ss2 << "_ " << "        "<< x.getNumber() << ' '<< x.getStart() << ' '<< x.getEnd() << ' '<< x.getDestination() << "\n";//Save added call to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),58);//Rewrite value.
		}
		is.close();
	}else{
		cout << "Could not open file -calls_vector.txt- \n";
	}
}

void call::reIndex(){
	fstream is("calls_vector.txt");//Open the file to index.
	ofstream index;
	index.open("calls_index.txt");
	int rrn=1;//rrn counter
	is.seekg (0, is.end);//Move get cursor to the end of file.
    int length = is.tellg();//Save the value to a variable.
    do{
    	int offset=128+rrn*58;//calculate offset for the current value.
    	is.seekg(offset);//Move the get cursor to the current offset.
    	char* mark = new char;//Save the mark
    	is.read(mark,1);
    	if(*mark == '_'){//Check if mark states registry is not deleted
    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
    		char * buffer = new char(8);//Buffer to store the seeked value ID.
    		is.read(buffer,8);//Save into buffer.
    		index.write(buffer,8);
    		stringstream ss;//Create stream to manage fixed size
    		ss << setfill(' ') << setw(9) << rrn << "\n";//create fixe sized 9 rrn for file managing
    		string temp = ss.str();//Cast stream
    		index.write(temp.c_str(),10);//Write to index file.
    	}
    	rrn++;
    }while(rrn!=(length-128)/58);//While the rrn is not equal to length - header size divided by the registry length.
    is.close();
	index.close();
}

void call::saveFile(vector<call> calls){
	int i;
	ofstream file("calls_vector.txt");
	if(file.is_open()){
		file << "Avail_head:" << setfill(' ') << setw(8) <<"0\n";
		file << "Re-index:" << setfill(' ') << setw(10) <<"0\n";
		file << "Structure:\n";
		file << " M:Marked\n";
		file << " B:Blank_Space\n";
		file << " R:Reference\n";
		file << " N:Number\n";
		file << " S:Start\n";
		file << " E:End\n";
		file << " D:Destination\n";
		file << "MBRRRRRRRBNNNNNNNNBSSSSSSSSSSSSSSBEEEEEEEEEEEEEEBDDDDDDDD\n";
		for(i = 0; i<calls.size() ; i++){
			file << "_ " << "        "<< calls.at(i).getNumber() << ' '<< calls.at(i).getStart() << ' '<< calls.at(i).getEnd() << ' '<< calls.at(i).getDestination() << "\n";
		}
		file.close();
	}else{
		cout << "Error opening file -calls_vector.txt- \n";
	}
}

string call::toString(){
	stringstream ss;
	ss << number << "\t" << start<< "\t" << end << "\t" << destination;
	return ss.str();
}

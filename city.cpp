#include "city.h"
#include <iomanip>

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

void city::availDelete(int rrn){
	fstream is("cities_vector.txt");
	if(is.is_open()){
		char * buffer = new char;
		int offset=111+rrn*55;//calculate offset.
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
			cout << "Invalid value, registry does not exist or is already deleted.";
		}
		is.close();	
	}else{
		cout << "Could not open file -cities_vector.txt";
	}
}

void city::availAdd(city x){
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
			ss2 << "_ " << "        " <<setfill('0') << setw(4) << x.getId_city() << setfill(' ') << setw(40) << x.getName()<<"\n";//Save added city to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),55);//Append added city
		}else{
			int rrn = atoi(temp.c_str());
			int offset=111+rrn*55;//calculate offset.
			is.seekp(offset+2);//Move the put cursor to the next deleted reference of the registry.
			char * buffer2 = new char(7);
			is.read(buffer2,7);//Save the value to a buffer.
			is.seekp(11);//Move the put cursor to the avail list header.
			is.write(buffer2,7);//Overwrite avail list header.
			is.seekp(offset);//Move back to offset.
			stringstream ss2;
			ss2 << "_ " << "        " <<setfill('0') << setw(4) << x.getId_city() << setfill(' ') << setw(40) << x.getName()<<"\n";//Save added city to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),55);//Rewrite value.
		}
		is.close();
	}else{
		cout << "Could not open file -cities_vector.txt";
	}
}

void city::reIndex(){
	fstream is("cities_vector.txt");//Open the file to index.
	ofstream index;
	index.open("cities_index.txt");
	int rrn=1;//rrn counter
	is.seekg (0, is.end);//Move get cursor to the end of file.
    int length = is.tellg();//Save the value to a variable.
    do{
    	int offset=111+rrn*55;//calculate offset for the current value.
    	is.seekg(offset);//Move the get cursor to the current offset.
    	char* mark = new char;//Save the mark
    	is.read(mark,1);
    	if(*mark == '_'){//Check if mark states registry is not deleted
    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
    		char * buffer = new char(4);//Buffer to store the seeked value ID.
    		is.read(buffer,4);//Save into buffer.
    		index.write(buffer,4);
    		stringstream ss;//Create stream to manage fixed size
    		ss << setfill(' ') << setw(9) << rrn << "\n";//create fixe sized 10 rrn for file managing
    		string temp = ss.str();//Cast stream
    		index.write(temp.c_str(),10);//Write to index file.
    	}
    	rrn++;
    }while(rrn!=(length-111)/55);//While the rrn is not equal to length - header size divided by the registry length.
    is.close();
	index.close();
}

string city::toString(){
	stringstream ss;
	ss << id_city << "\t" << name;
	return ss.str();
}
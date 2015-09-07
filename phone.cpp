//phones_vector header.size() = 110
//phone.size = 33
#include "phone.h"
#include <iomanip>

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

void phone::availDelete(int rrn){
	fstream is("phones_vector.txt");
	if(is.is_open()){
		char * buffer = new char;
		int offset=110+rrn*33;//calculate offset.
		is.seekg(offset);//Move get cursor to offset.
		is.read(buffer,1);//Read 1 byte
		cout << buffer;
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
			cout << "Invalid value, registry does not exist or is already deleted -phones_vector.txt- \n";
		}
		is.close();	
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

void phone::availAdd(phone x){
	fstream is("phones_vector.txt");
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
			ss2 << "_ " << "        " << x.getNumber() << ' ' << x.getId_client()<< "\n";//Save added city to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),33);//Append added city
		}else{
			int rrn = atoi(temp.c_str());
			int offset=110+rrn*33;//calculate offset.
			is.seekp(offset+2);//Move the put cursor to the next deleted reference of the registry.
			char * buffer2 = new char(7);
			is.read(buffer2,7);//Save the value to a buffer.
			is.seekp(11);//Move the put cursor to the avail list header.
			is.write(buffer2,7);//Overwrite avail list header.
			is.seekp(offset);//Move back to offset.
			stringstream ss2;
			ss2 << "_ " << "        " << x.getNumber() << ' ' << x.getId_client()<< "\n";//Save added phone to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),33);//Rewrite value.
		}
		is.close();
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

void phone::saveFile(vector<phone> phones){
	int i;
	ofstream file("phones_vector.txt");
	if(file.is_open()){
		file << "Avail_head:" << setfill(' ') << setw(8) <<"0\n";
		file << "Re-index:" << setfill(' ') << setw(10) <<"0\n";
		file << "Structure:\n";
		file << " M:Marked\n";
		file << " B:Blank_Space\n";
		file << " R:Reference\n";
		file << " N:Number\n";
		file << " I:Client_ID\n";
		file << "MBRRRRRRRBNNNNNNNNBIIIIIIIIIIIII\n";
		for(i = 0; i<phones.size() ; i++){
			file << "_ " << "        " << phones.at(i).getNumber() << ' ' << phones.at(i).getId_client()<< "\n";
		}
		file.close();
	}else{
		cout << "Error opening file -phones_vector.txt- \n";
	}
}

void phone::availList(){
	fstream is("phones_vector.txt");//Open the file to list.
	if(is.is_open()){
		int rrn=1;//rrn counter
		is.seekg (0, is.end);//Move get cursor to the end of file.
	    int length = is.tellg();//Save the value to a variable.
	    do{
	    	int offset=110+rrn*33;//calculate offset for the current value.
	    	is.seekg(offset);//Move the get cursor to the current offset.
	    	char* mark = new char;//Save the mark
	    	is.read(mark,1);
	    	if(*mark == '_'){//Check if mark states registry is not deleted
	    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
	    		char * buffer = new char(23);//Buffer to store the registry.
	    		is.read(buffer,23);//Save into buffer.
	    		cout << buffer;//List.
	    	}
	    	rrn++;
		}while(rrn!=(length-111)/55);//While the rrn is not equal to length - header size divided by the registry length.
		is.close();
	}else{
		cout << "Error opening file -phones_vector.txt- \n";
	}
}

void phone::availModify(phone x, int rrn){
	fstream is("phones_vector.txt");//Open the file to list.
	if(is.is_open()){
		char * buffer = new char;
		int offset=110+rrn*33;//calculate offset.
		is.seekg(offset);//Move get cursor to offset.
		is.read(buffer,1);//Read 1 byte
		if(*buffer == '_'){//Check if already deleted.
			is.seekp(offset);
			stringstream ss2;
			ss2 << "_ " << "        " << x.getNumber() << ' ' << x.getId_client()<< "\n";//Save added phone to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),33);//Rewrite value.
		}else{
			cout << "Invalid value, registry does not exist or is already deleted -phones_vector.txt- \n";
		}
		is.close();
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

string phone::toString(){
	stringstream ss;
	ss << number << "\t" << id_client;
	return ss.str();
}
//phones_vector header.size() = 110
//phone.size = 33
#include "phone.h"
#include <iomanip>
#include <algorithm>
#include "BTree.h"

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
	unsigned int i;
	for(i = 0 ; i< ids.size() ; i++){
		temp.push_back(phone(numbers.at(i), ids.at(i)));
	}
	return temp;
}

void phone::availDelete(int rrn){
	fstream is("phones_vector.txt");
	cout << "Attempting action...\n";
	if(is.is_open()){
		char * buffer = new char;
		int offset=110+rrn*33;//calculate offset.
		is.seekg(offset);//Move get cursor to offset.
		is.read(buffer,1);//Read 1 byte
		if(*buffer == '_'){//Check if already deleted.
			is.seekp(offset);//Move the put cursor towards the deleted registry.
			is.write("*",1);//Mark the registry as deleted.
			is.seekg(11);//Move the get cursor to the old value from the avail list header.
			char buffer2[7];
			is.read(buffer2,7);//Save the value to a buffer.
			stringstream ss;
			ss << setfill(' ') << setw(7) << rrn;
			string temp = ss.str();//Save the new value for the avail list header.
			is.seekp(11);//Move the put cursor to the avail list header.
			is.write(temp.c_str(),7);//Overwrite avail list header.
			is.seekp(offset+2);//Move the put cursor to the next deleted reference of the registry.
			is.write(buffer2,7);//Overwrite it with the old value of the avail list header.
			cout << "Completed succesfully.\n";
		}else{
			cout << "Invalid value, registry does not exist or is already deleted -phones_vector.txt- \n";
		}
		is.close();	
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

BTree phone::addPhone(phone x, BTree index){
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
			int final = ((int)is.tellp()-110)/33;
			stringstream ss2;
			ss2 << "_ " << "        " << x.getNumber() << ' ' << x.getId_client()<< "\n";//Save added city to stream
			string temp2 = ss2.str();
			BTKey key(x.getNumber(),final);
			index.insert(key);
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
			BTKey key(x.getNumber(),rrn);
			index.insert(key);
			is.write(temp2.c_str(),33);//Rewrite value.
		}
		is.close();
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
	return index;
}

void phone::reIndex(){
	fstream is("phones_vector.txt");//Open the file to index.
	cout << "Attemting to re-index -phones_vector.txt-\n";
	if(is.is_open()){
		ofstream index;
		index.open("phones_index.txt");
		if(index.is_open()){
			is.seekp(36);
			is.write("1",1);//Anti-Disaster Flag, marks if indexing finished correctly.
			int rrn=1;//rrn counter
			is.seekg (0, is.end);//Move get cursor to the end of file.
		    int length = is.tellg();//Save the value to a variable.
		    vector<pair<string,string> > index_list;//Index vector of pairs.
		    do{
		    	int offset=110+rrn*33;//calculate offset for the current value.
		    	is.seekg(offset);//Move the get cursor to the current offset.
		    	char* mark = new char;//Save the mark
		    	is.read(mark,1);
		    	if(*mark == '_'){//Check if mark states registry is not deleted
		    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
		    		char * buffer = new char(8);//Buffer to store the seeked value ID.
		    		is.read(buffer,8);//Save into buffer.
		    		stringstream ss;//Create stream to manage fixed size
		    		ss << setfill(' ') << setw(9) << rrn << "\n";//create fixe sized 9 rrn for file managing
		    		string temp = ss.str();//Cast stream
		    		string str(buffer,8);
		    		index_list.push_back(make_pair(str,temp));
		    	}
		    	rrn++;
		    }while(rrn!=(length-110)/33);//While the rrn is not equal to length - header size divided by the registry length.
		    sort(index_list.begin(),index_list.end());//Sort index alphabetically.
		    unsigned int i;
		    for(i=0;i<index_list.size();i++){
		    	index << index_list[i].first << index_list[i].second;//Copy to File.
		    }
		    index.close();
		    is.seekp(36);
			is.write("0",1);//Indexing finished succesfully, setting flag back to 0.
			cout << "Succesfully re-indexed -phones_vector.txt- \n";
		}else{
			cout << "Could not open file -phones_index.txt- \n";
		}
	    is.close();
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

void phone::saveFile(vector<phone> phones){
	unsigned int i;
	ofstream file("phones_vector.txt");
	cout << "Attempting to create PHONE file  -phones_vector.txt-...\n";
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
		cout << "Succesfully created PHONE file  -phones_vector.txt- \n";
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
	    		char buffer[23];//Buffer to store the registry.
	    		is.read(buffer,23);//Save into buffer.
	    		string str(buffer,23);
	    		cout << str;//List.
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

void phone::checkIndex(){
	fstream is("phones_vector.txt");//Open the file to index.
	cout << "Checking -phones_index.txt- index status...\n";
	if(is.is_open()){
		is.seekg(36);
		char* flag = new char;//flag variable
		is.read(flag,1);//Anti-Disaster Flag, marks if indexing finished correctly.
		if(*flag=='1'){
			phone temp;
			temp.reIndex();
			cout << "-phones_index.txt- has been re-indexed.\n";
		}else{
			cout << "-phones_index.txt- does not need re-indexing.\n";
		}
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

void phone::checkIndexStatus(){
	fstream is("phones_vector.txt");//Open the file to index.
	cout << "Checking -phones_index.txt- index status...\n";
	if(is.is_open()){
		is.seekg(36);
		char* flag = new char;//flag variable
		is.read(flag,1);//Anti-Disaster Flag, marks if indexing finished correctly.
		if(*flag=='1'){
			cout << "-phones_index.txt- needs re-indexing.\n";
		}else{
			cout << "-phones_index.txt- does not need re-indexing.\n";
		}
	}else{
		cout << "Could not open file -phones_vector.txt- \n";
	}
}

BTree phone::loadIndex(){
	BTree temp(10);//Create BTree
	ifstream index;
	cout << "Attempting to load index to memory... \n";
	index.open("phones_index.txt");
	if(index.is_open()){
		index.seekg (0, index.end);//Move get cursor to the end of file.
	    int length = index.tellg();//Save the value to a variable.
	    for(int i = 0;i*18<length;i++){
	    	index.seekg(i*18);//Move read pointer to registry
		    char * buffer = new char(4);//Store in buffer
		    index.read(buffer,8);//Store value in buffer
		    string str(buffer,8);
		    long value = atol(str.c_str());
		    index.seekg(i*18 + 8);//Move read pointer to RRN
		    char * buffer2 = new char(9);
		    index.read(buffer2,9);//Store value in buffer
		    string str2(buffer2,9);
		    int rrn = atoi(str2.c_str());
		    BTKey key(value,rrn);
		    temp.insert(key);//Save index element to tree;
	    }
	    cout << "Index succesfully loaded to memory. \n";
	}else{
		cout << "Unable to open file -phones_index.txt- \n";
	}	
    return temp;
}

void phone::search(int rrn){
	ifstream index;
	index.open("phones_vector.txt");
	if(index.is_open()){
		int offset=110+rrn*33 + 10;
		index.seekg(offset);
		char buffer[23];//Buffer to store the registry.
		index.read(buffer,23);//Save into buffer.
		string str(buffer,23);
		cout << "Found at RRN " << rrn << ": ";
		cout << str;
	}else{
		cout << "Found in index but unable to open file -phones_index.txt- \n";
	}
}

string phone::search2(long xid){
	ifstream index;
	index.open("phones_vector.txt");
	int rrn = 1;
	index.seekg (0, index.end);//Move get cursor to the end of file.
    long length = ((long)index.tellg()-110)/33;
	if(index.is_open()){
		do{
			int offset=110+rrn*33 + 10;
			index.seekg(offset);
			char buffer[8];
			index.read(buffer,8);
			string str(buffer,8);
			if(atoi(str.c_str())==xid){
				index.seekg(offset);
				char buffer[23];//Buffer to store the registry.
				index.read(buffer,23);//Save into buffer.
				string str(buffer,23);
				stringstream ss;
				ss << "                    PHONE     CLIENT ID\n";                        
				ss << "Found at RRN " << rrn << ": " <<str;
				return ss.str();
			}else{
				rrn ++;
			}
		}while(rrn<length);
	}else{
		cout << "Found in index but unable to open file -phones_index.txt- \n";
	}
	return "Not found...\n";
}

string phone::toString(){
	stringstream ss;
	ss << number << "\t" << id_client;
	return ss.str();
}
//clients_vector header.size() = 136
//client.size = 72
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

void client::availDelete(int rrn){
	fstream is("clients_vector.txt");
	if(is.is_open()){
		char * buffer = new char;
		int offset=136+rrn*72;//calculate offset.
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
			cout << "Invalid value, registry does not exist or is already deleted -clients_vector.txt- \n";
		}
		is.close();	
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
}

void client::availAdd(client x){
	fstream is("clients_vector.txt");
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
			ss2 << "_ " << "        " << x.getId_client() << ' ' << setfill(' ') << setw(40) << x.getName() << ' ' << x.getGender() << ' ' << setfill('0') << setw(4) << x.getId_city()<<"\n";//Save added client to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),72);//Append added city
		}else{
			int rrn = atoi(temp.c_str());
			int offset=136+rrn*72;//calculate offset.
			is.seekp(offset+2);//Move the put cursor to the next deleted reference of the registry.
			char * buffer2 = new char(7);
			is.read(buffer2,7);//Save the value to a buffer.
			is.seekp(11);//Move the put cursor to the avail list header.
			is.write(buffer2,7);//Overwrite avail list header.
			is.seekp(offset);//Move back to offset.
			stringstream ss2;
			ss2 << "_ " << "        " << x.getId_client() << ' ' << setfill(' ') << setw(40) << x.getName() << ' ' << x.getGender() << ' ' << setfill('0') << setw(4) << x.getId_city()<<"\n";//Save added client to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),72);//Rewrite value.
		}
		is.close();
	}else{
		cout << "Could not open file -clients_vector.txt.txt- \n";
	}
}

//clients_vector header.size() = 136
//client.size = 72

void client::reIndex(){
	fstream is("clients_vector.txt");//Open the file to index.
	ofstream index;
	index.open("clients_index.txt");
	int rrn=1;//rrn counter
	is.seekg (0, is.end);//Move get cursor to the end of file.
    int length = is.tellg();//Save the value to a variable.
    do{
    	int offset=136+rrn*72;//calculate offset for the current value.
    	is.seekg(offset);//Move the get cursor to the current offset.
    	char* mark = new char;//Save the mark
    	is.read(mark,1);
    	if(*mark == '_'){//Check if mark states registry is not deleted
    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
    		char * buffer = new char(13);//Buffer to store the seeked value ID.
    		is.read(buffer,13);//Save into buffer.
    		index.write(buffer,13);
    		stringstream ss;//Create stream to manage fixed size
    		ss << setfill(' ') << setw(9) << rrn << "\n";//create fixe sized 14 rrn for file managing
    		string temp = ss.str();//Cast stream
    		index.write(temp.c_str(),10);//Write to index file.
    	}
    	rrn++;
    }while(rrn!=(length-136)/72);//While the rrn is not equal to length - header size divided by the registry length.
    is.close();
	index.close();
}

void client::saveFile(vector<client> clients){
	int i;
	ofstream file("clients_vector.txt");
	if(file.is_open()){
		file << "Avail_head:" << setfill(' ') << setw(8) <<"0\n";
		file << "Re-index:" << setfill(' ') << setw(10) <<"0\n";
		file << "Structure:\n";
		file << " M:Marked\n";
		file << " B:Blank_Space\n";
		file << " R:Reference\n";
		file << " I:Client_ID\n";
		file << " N:Client_Name\n";
		file << " G:Gender\n";
		file << " C:City_ID\n";
		file << "MBRRRRRRRBIIIIIIIIIIIIIBNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNBGBCCCC\n";
		for(i = 0; i<clients.size() ; i++){
			file << "_ " << "        " << clients.at(i).getId_client() << ' ' << setfill(' ') << setw(40) << clients.at(i).getName() << ' ' << clients.at(i).getGender() << ' ' << setfill('0') << setw(4) << clients.at(i).getId_city()<<"\n";
		}
		file.close();
	}else{
		cout << "Error opening file -clients_vector.txt- \n";
	}
}

string client::toString(){
	stringstream ss;
	ss << id_client << "\t" << name << "\t" << gender << "\t" << id_city;
	return ss.str();
}
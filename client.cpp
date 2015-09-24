//clients_vector header.size() = 136
//client.size = 72
#include "client.h"
#include <algorithm>
#include "BTree.h"

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
	unsigned int i;
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
	unsigned int i;
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
	cout << "Attempting action...\n";
	if(is.is_open()){
		char * buffer = new char;
		int offset=136+rrn*72;//calculate offset.
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
			cout << "Invalid value, registry does not exist or is already deleted -clients_vector.txt- \n";
		}
		is.close();	
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
}

BTree client::addClient(client x, BTree index){
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
			int final = ((int)is.tellp()-136)/72;
			stringstream ss2;
			ss2 << "_ " << "        " << x.getId_client() << ' ' << setfill(' ') << setw(40) << x.getName() << ' ' << x.getGender() << ' ' << setfill('0') << setw(4) << x.getId_city()<<"\n";//Save added client to stream
			string temp2 = ss2.str();
			string idclient = x.getId_client();
			BTKey key(atol(idclient.c_str()),final);
			index.insert(key);
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
			string idclient = x.getId_client();
			BTKey key(atol(idclient.c_str()),rrn);
			index.insert(key);
			is.write(temp2.c_str(),72);//Rewrite value.
		}
		is.close();
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
	return index;
}

void client::reIndex(){
	fstream is("clients_vector.txt");//Open the file to index.
	cout << "Attemting to re-index -clients_vector.txt-\n";
	if(is.is_open()){
		ofstream index;
		index.open("clients_index.txt");
		if(index.is_open()){
			is.seekp(36);
			is.write("1",1);//Anti-Disaster Flag, marks if indexing finished correctly.
			int rrn=1;//rrn counter
			is.seekg (0, is.end);//Move get cursor to the end of file.
		    int length = is.tellg();//Save the value to a variable.
		    vector<pair<string,string> > index_list;//Index vector of pairs.
		    do{
		    	int offset=136+rrn*72;//calculate offset for the current value.
		    	is.seekg(offset);//Move the get cursor to the current offset.
		    	char* mark = new char;//Save the mark
		    	is.read(mark,1);
		    	if(*mark == '_'){//Check if mark states registry is not deleted
		    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
		    		char * buffer = new char(13);//Buffer to store the seeked value ID.
		    		is.read(buffer,13);//Save into buffer.
		    		stringstream ss;//Create stream to manage fixed size
		    		ss << setfill(' ') << setw(9) << rrn << "\n";//create fixe sized 14 rrn for file managing
		    		string temp = ss.str();//Cast stream
		    		string str(buffer,13);
		    		index_list.push_back(make_pair(str,temp));
		    	}
		    	rrn++;
		    }while(rrn!=(length-136)/72);//While the rrn is not equal to length - header size divided by the registry length.
		    sort(index_list.begin(),index_list.end());//Sort index alphabetically.
		    unsigned int i;
		    for(i=0;i<index_list.size();i++){
		    	index << index_list[i].first << index_list[i].second;//Copy to File.
		    }
		    index.close();
		    is.seekp(36);
			is.write("0",1);//Indexing finished succesfully, setting flag back to 0.
			cout << "Succesfully re-indexed -clients_vector.txt- \n";
		}else{
			cout << "Could not open file -clients_index.txt- \n";
		}
	    is.close();
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
}

void client::saveFile(vector<client> clients){
	unsigned int i;
	ofstream file("clients_vector.txt");
	cout << "Attempting to create CLIENT file  -clients_vector.txt-... \n";
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
		cout << "Succesfully created CLIENT file  -clients_vector.txt- \n";
	}else{
		cout << "Error opening file -clients_vector.txt- \n";
	}
}

void client::availList(){
	fstream is("clients_vector.txt");//Open the file to list.
	int counter = 0;
	int num = 1;
	int iter;
	cout << "How many records per page? (NUMBER)\n";
	cin >> iter;
	cin.ignore();
	if(is.is_open()){
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
	    		char buffer[62];//Buffer to store the registry.
	    		is.read(buffer,62);//Save into buffer.
	    		string str(buffer,62);
	    		cout <<"Record Number " <<num << ": ";
	    		cout << str;//List.
	    		counter++;
		        num++;
		        if(counter == iter){
		            cout << "Show More? (y/n) \n";
		            char ans;
		            cin >> ans;
		            cin.ignore();
		            if(ans == 'y'){
		                counter = 0;
		            }else{
		                break;
		            }
		        }
	    	}
	    	rrn++;
		}while(rrn!=(length-111)/55);//While the rrn is not equal to length - header size divided by the registry length.
		is.close();
	}else{
		cout << "Error opening file -clients_vector.txt- \n";
	}
}

void client::availModify(client x, int rrn){
	fstream is("clients_vector.txt");//Open the file to list.
	if(is.is_open()){
		char * buffer = new char;
		int offset=136+rrn*72;//calculate offset.
		is.seekg(offset);//Move get cursor to offset.
		is.read(buffer,1);//Read 1 byte
		if(*buffer == '_'){//Check if already deleted.
			is.seekp(offset);
			stringstream ss2;
			ss2 << "_ " << "        " << x.getId_client() << ' ' << setfill(' ') << setw(40) << x.getName() << ' ' << x.getGender() << ' ' << setfill('0') << setw(4) << x.getId_city()<<"\n";//Save added client to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),72);//Rewrite value.
		}else{
			cout << "Invalid value, registry does not exist or is already deleted -clients_vector.txt- \n";
		}
		is.close();
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
}

void client::checkIndex(){
	fstream is("clients_vector.txt");//Open the file to index.
	cout << "Checking -clients_index.txt- index status...\n";
	if(is.is_open()){
		is.seekg(36);
		char* flag = new char;//flag variable
		is.read(flag,1);//Anti-Disaster Flag, marks if indexing finished correctly.
		if(*flag=='1'){
			client temp;
			temp.reIndex();
			cout << "-clients_index.txt- has been re-indexed.\n";
		}else{
			cout << "-clients_index.txt- does not need re-indexing.\n";
		}
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
}

void client::checkIndexStatus(){
	fstream is("clients_vector.txt");//Open the file to index.
	cout << "Checking -clients_index.txt- index status...\n";
	if(is.is_open()){
		is.seekg(36);
		char* flag = new char;//flag variable
		is.read(flag,1);//Anti-Disaster Flag, marks if indexing finished correctly.
		if(*flag=='1'){
			cout << "-clients_index.txt- needs re-indexing.\n";
		}else{
			cout << "-clients_index.txt- does not need re-indexing.\n";
		}
	}else{
		cout << "Could not open file -clients_vector.txt- \n";
	}
}

BTree client::loadIndex(){
	BTree temp(8);//Create BTree
	ifstream index;
	cout << "Attempting to load index to memory... \n";
	index.open("clients_index.txt");
	if(index.is_open()){
		index.seekg (0, index.end);//Move get cursor to the end of file.
	    int length = index.tellg();//Save the value to a variable.
	    for(int i = 0;i*23<length;i++){
	    	index.seekg(i*23);//Move read pointer to registry
		    char * buffer = new char(4);//Store in buffer
		    index.read(buffer,13);//Store value in buffer
		    string str(buffer,13);
		    long value = atol(str.c_str());
		    index.seekg(i*23 + 13);//Move read pointer to RRN
		    char * buffer2 = new char(9);
		    index.read(buffer2,9);//Store value in buffer
		    string str2(buffer2,9);
		    int rrn = atoi(str2.c_str());
		    BTKey key(value,rrn);
		    temp.insert(key);//Save index element to tree;
	    }
	    cout << "Index succesfully loaded to memory. \n";
	}else{
		cout << "Unable to open file -clients_index.txt- \n";
	}	
    return temp;
}

void client::search(int rrn){
	ifstream index;
	index.open("clients_vector.txt");
	if(index.is_open()){
		int offset=offset=136+rrn*72 + 10;
		index.seekg(offset);
		char buffer[62];//Buffer to store the registry.
		index.read(buffer,62);//Save into buffer.
		string str(buffer,62);
		cout << "Found at RRN " << rrn << ": ";
		cout << str;
	}else{
		cout << "Found in index but unable to open file -clients_index.txt- \n";
	}
}

string client::search2(long xid){
	ifstream index;
	index.open("clients_vector.txt");
	int rrn = 1;
	index.seekg (0, index.end);//Move get cursor to the end of file.
    long length = ((long)index.tellg()-136)/72;
	if(index.is_open()){
		do{
			int offset=136+rrn*72 + 10;
			index.seekg(offset);
			char buffer[13];
			index.read(buffer,13);
			string str(buffer,13);
			if(atol(str.c_str())==xid){
				index.seekg(offset);
				char buffer[62];//Buffer to store the registry.
				index.read(buffer,62);//Save into buffer.
				string str(buffer,62);
				stringstream ss;
				ss << "                           ID                                     NAME   INFO\n";
				ss << "Found at RRN " << rrn << ": " <<str;
				return ss.str();
			}else{
				rrn ++;
			}
		}while(rrn<length);
	}else{
		cout << "Found in index but unable to open file -clients_index.txt- \n";
	}
	return "Not found...\n";
}

string client::toString(){
	stringstream ss;
	ss << id_client << "\t" << name << "\t" << gender << "\t" << id_city;
	return ss.str();
}
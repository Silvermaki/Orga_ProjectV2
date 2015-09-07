//cities_vector header.size() = 111
//city.size = 55
#include "city.h"
#include <iomanip>
#include <string.h>
#include <algorithm>

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
			cout << "Invalid value, registry does not exist or is already deleted -cities_vector.txt- \n";
		}
		is.close();	
	}else{
		cout << "Could not open file -cities_vector.txt- \n";
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
		cout << "Could not open file -cities_vector.txt- \n";
	}
}

void city::availList(){
	fstream is("cities_vector.txt");//Open the file to list.
	if(is.is_open()){
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
	    		char * buffer = new char(45);//Buffer to store the registry.
	    		is.read(buffer,45);//Save into buffer.
	    		cout << buffer;//List.
	    	}
	    	rrn++;
		}while(rrn!=(length-111)/55);//While the rrn is not equal to length - header size divided by the registry length.
		is.close();
	}else{
		cout << "Could not open file -cities_vector.txt- \n";
	}
}

void city::availModify(city x, int rrn){
	fstream is("cities_vector.txt");//Open the file to list.
	if(is.is_open()){
		char * buffer = new char;
		int offset=111+rrn*55;//calculate offset.
		is.seekg(offset);//Move get cursor to offset.
		is.read(buffer,1);//Read 1 byte
		if(*buffer == '_'){//Check if already deleted.
			is.seekp(offset);
			stringstream ss2;
			ss2 << "_ " << "        " <<setfill('0') << setw(4) << x.getId_city() << setfill(' ') << setw(40) << x.getName()<<"\n";//Save added city to stream
			string temp2 = ss2.str();
			is.write(temp2.c_str(),55);//Rewrite value.
		}else{
			cout << "Invalid value, registry does not exist or is already deleted -cities_vector.txt- \n";
		}
		is.close();
	}else{
		cout << "Could not open file -cities_vector.txt- \n";
	}
}

void city::reIndex(){
	fstream is("cities_vector.txt");//Open the file to index.
	if(is.is_open()){
		ofstream index;
		index.open("cities_index.txt");
		if(index.is_open()){
			is.seekp(36);
			is.write("1",1);//Anti-Disaster Flag, marks if indexing finished correctly.
			int rrn=1;//rrn counter
			is.seekg (0, is.end);//Move get cursor to the end of file.
		    int length = is.tellg();//Save the value to a variable.
		    vector<pair<string,string> > index_list;//Index vector of pairs.
		    do{
		    	int offset=111+rrn*55;//calculate offset for the current value.
		    	is.seekg(offset);//Move the get cursor to the current offset.
		    	char* mark = new char;//Save the mark
		    	is.read(mark,1);
		    	if(*mark == '_'){//Check if mark states registry is not deleted
		    		is.seekg(offset+10);//Move the get cursor to the current offset, bypasing the mark byte and the reference bytes.
		    		char * buffer = new char(4);//Buffer to store the seeked value ID.
		    		is.read(buffer,4);//Save into buffer.
		    		stringstream ss;//Create stream to manage fixed size
		    		ss << setfill(' ') << setw(9) << rrn << "\n";//create fixe sized 10 rrn for file managing
		    		string temp = ss.str();//Cast stream
		    		string str(buffer,4);
		    		index_list.push_back(make_pair(str,temp));
		    	}
		    	rrn++;
		    }while(rrn!=(length-111)/55);//While the rrn is not equal to length - header size divided by the registry length.
		    sort(index_list.begin(),index_list.end());//Sort index alphabetically.
		    int i;
		    for(int i=0;i<index_list.size();i++){
		    	index << index_list[i].first << index_list[i].second;//Copy to File.
		    }
		    index.close();
		    is.seekp(36);
			is.write("0",1);//Indexing finished succesfully, setting flag back to 0.
		}else{
			cout << "Could not open file -cities_index.txt- \n";
		}
	    is.close();
	}else{
		cout << "Could not open file -cities_vector.txt- \n";
	}
}

void city::checkIndex(){
	fstream is("cities_vector.txt");//Open the file to index.
	if(is.is_open()){
		is.seekg(36);
		char* flag = new char;//flag variable
		is.read(flag,1);//Anti-Disaster Flag, marks if indexing finished correctly.
		if(*flag=='1'){
			city temp;
			temp.reIndex();
			cout << "-cities_index.txt- has been re-indexed.\n";
		}else{
			cout << "-clities_index.txt- does not need re-indexing.\n";
		}
	}else{
		cout << "Could not open file -cities_vector.txt- \n";
	}
}

void city::saveFile(vector<city> cities){
	ofstream file("cities_vector.txt");
	int i;
	if(file.is_open()){
		file << "Avail_head:" << setfill(' ') << setw(8) <<"0\n";
		file << "Re-index:" << setfill(' ') << setw(10) <<"0\n";
		file << "Structure:\n";
		file << " M:Marked\n";
		file << " B:Blank_Space\n";
		file << " R:Reference\n";
		file << " I:City_ID\n";
		file << " N:City_Name\n";
		file << "MBRRRRRRRBIIIIBNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n";
		for(i = 0; i<cities.size() ; i++){
			file << "_ " << "        " <<setfill('0') << setw(4) << cities.at(i).getId_city() << setfill(' ') << setw(40) << cities.at(i).getName()<<"\n";
		}
		file.close();
	}else{
		cout << "Error opening file -cities_vector.txt- \n";
	}
}

string city::toString(){
	stringstream ss;
	ss << id_city << "\t" << name;
	return ss.str();
}
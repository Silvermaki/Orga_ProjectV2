#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "phone.h"
#include "call.h"
#include "city.h"
#include "client.h"
#include <iomanip>

using namespace std;

void saveFiles(vector<city>, vector<client>, vector<call>, vector<phone>);

int main(int argc, char* argv[]){
	//////////////////////////////////////CODE FOR CREATING THE ORIGINAL FILES -START-////////////////////////////////////////////
	/*
	srand(time(NULL));
	phone temp;
	call temp2;
	city temp5;
	client temp6;
	vector<int> numbers_list = temp.createNumbers(500);
	vector<int> starts_list = temp2.createCallStart(50000);
	vector<int> ends_list = temp2.createCallEnd(50000, starts_list);
	vector<int> id_list = temp6.createIds(500);
	vector<string> sid_list = temp6.idtoString(id_list);
	vector<string> name_list = temp6.createNames();
	vector<long> ends_long = temp2.endLong(ends_list);
	vector<long> starts_long = temp2.startLong(starts_list);
	vector<city> city_list = temp5.cityVector();
	vector<client> client_list = temp6.clientVector(sid_list, name_list, city_list);
	vector<call> call_list = temp2.callVector(numbers_list, starts_long, ends_long);
	vector<phone> phone_list = temp.phoneVector(numbers_list, sid_list);
	saveFiles(city_list, client_list, call_list, phone_list);
	*/
	//////////////////////////////////////CODE FOR CREATING THE ORIGINAL FILES -END-////////////////////////////////////////////
	city lol;
	lol.reIndex();
	return 0;
}

void saveFiles(vector<city> cities, vector<client> clients, vector<call> calls, vector<phone> phones){
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
		cout << "Error opening file -cities_vector.txt-";
	}
	
	file.open("clients_vector.txt");
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
		cout << "Error opening file -clients_vector.txt-";
	}


	file.open("calls_vector.txt");
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
		cout << "Error opening file -calls_vector.txt-";
	}

	
	file.open("phones_vector.txt");
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
		cout << "Error opening file -phones_vector.txt-";
	}
}

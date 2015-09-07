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

using namespace std;

void saveFiles(vector<city>, vector<client>, vector<phone>, vector<call>);
void init_Files();
void saveIndexes();
void init_Check();

int main(int argc, char* argv[]){
	/*****Create Files, Un-comment if you need to re-make the original files.*****/
	//init_Files();
	init_Check();
	phone phone1;
	call call1;
	city city1;
	client client1;

	return 0;
}
void init_Check(){//Checks if we need to re-index a file.
	city city_ref;
	city_ref.checkIndex();
	client client_ref;
	client_ref.checkIndex();
	call call_ref;
	call_ref.checkIndex();
	phone phone_ref;
	phone_ref.checkIndex();
}

//////////////////////////////////////CODE FOR CREATING THE ORIGINAL FILES -START-////////////////////////////////////////////
void init_Files(){
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
	saveFiles(city_list, client_list, phone_list, call_list);
	saveIndexes();

}

void saveIndexes(){
	city city_ref;
	city_ref.reIndex();
	client client_ref;
	client_ref.reIndex();
	call call_ref;
	call_ref.reIndex();
	phone phone_ref;
	phone_ref.reIndex();
}

void saveFiles(vector<city> cities, vector<client> clients, vector<phone> phones,vector<call> calls){
	city city_ref;
	city_ref.saveFile(cities);
	client client_ref;
	client_ref.saveFile(clients);
	call call_ref;
	call_ref.saveFile(calls);
	phone phone_ref;
	phone_ref.saveFile(phones);
}
//////////////////////////////////////CODE FOR CREATING THE ORIGINAL FILES -END-////////////////////////////////////////////
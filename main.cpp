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
#include "BTree.h"

using namespace std;

void saveFiles(vector<city>, vector<client>, vector<phone>, vector<call>);
void init_Files();
void saveIndexes();
void init_Check();
void Menu();
BTree addCityMenu(BTree);
BTree addClientMenu(BTree);
BTree addPhoneMenu(BTree);
BTree deleteCityMenu(BTree);
BTree deleteClientMenu(BTree);
BTree deletePhoneMenu(BTree);

/////////////////////////////////////////////////MAIN START///////////////////////////////////////////////////
int main(int argc, char* argv[]){
	//init_Files();//<-------------- UN-COMMENT IF YOU NEED TO CREATE/RESET INITIAL FILES ON RUN
	init_Check();// Re-indexing flag check.
	Menu();
	return 0;
}
/////////////////////////////////////////////////MAIN END/////////////////////////////////////////////////////

//////////////////////////////////////////MENU FUNCTIONS START////////////////////////////////////////////////
//General Menu
void Menu(){
	city city_ref;//Reference for city functions.
	client client_ref;//Reference for client functions.
	phone phone_ref;//Reference for phone functions.
	call call_ref;
	BTree city_index  = city_ref.loadIndex();//Load city_index.txt into a B tree.
	BTree client_index  = client_ref.loadIndex();//Load client_index.txt into a B tree.
	BTree phone_index  = phone_ref.loadIndex();//Load phone_index.txt into a B tree.

	do{
		char ans;
		int inputs_int;
		string inputs;
		city temp;
		
		phone temp3;

		cout << "\nWhat do you want to do? (Type in your answer and press ENTER or CTR+Z to exit)\n";
		cout << "a. Add\nb. Delete\nc. List\nd. Modify\ne. Search\nf. Re-Index\ng. Re-Build Files\nh. Flush Indexes\ni. Re-load Indexes\n";
		cout << "j. Check Index Status\n";
		cin >> ans;
		cin.ignore();
		switch(ans){
			case 'a':
				cout << "\nWhat do you want to Add? (Type in your answer and press ENTER or CTR+Z to exit)\n";
				cout << "1. City\n2. Client\n3. Phone\n";
				cin >> ans;
				cin.ignore();

				switch(ans){
					case '1':
						city_index = addCityMenu(city_index);
						break;
					case '2':
						client_index = addClientMenu(client_index);
						break;
					case '3':
						phone_index = addPhoneMenu(phone_index);
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}

				break;
			case 'b':
				cout << "\nWhat do you want to Add? (Type in your answer and press ENTER or CTR+Z to exit)\n";
				cout << "1. City\n2. Client\n3. Phone\n";
				cin >> ans;
				cin.ignore();

				switch(ans){
					case '1':
						city_index = deleteCityMenu(city_index);
						break;
					case '2':
						client_index = deleteClientMenu(client_index);
						break;
					case '3':
						phone_index = deletePhoneMenu(phone_index);
						break;
					default:
						break;
				}
				break;
			case 'c':
				break;
			case 'd':

				break;
			case 'e':

				break;
			case 'f':
				cout << "\nRe-index which files? (Type in your answer and press ENTER or CTR+Z to exit)\n";
				cout << "1. City\n2. Client\n3. Phone\n4. Call\n5. All\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						city_ref.reIndex();
						break;
					case '2':
						client_ref.reIndex();
						break;
					case '3':
						phone_ref.reIndex();
						break;
					case '4':
						call_ref.reIndex();
						break;
					case '5':
						city_ref.reIndex();
						client_ref.reIndex();
						phone_ref.reIndex();
						call_ref.reIndex();
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}
				break;
			case 'g':
				init_Files();
				break;
			case 'h':

				break;
			case 'i':
				cout << "\nRe-Load which index? (Type in your answer and press ENTER or CTR+Z to exit)\n";
				cout << "1. City\n2. Client\n3. Phone\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						city_index  = city_ref.loadIndex();//Load city_index.txt into a B tree.
						break;
					case '2':
						client_index  = client_ref.loadIndex();//Load client_index.txt into a B tree.
						break;
					case '3':
						phone_index  = phone_ref.loadIndex();//Load phone_index.txt into a B tree.
						break;
					case '4':
						
						break;
					case '5':
						city_index  = city_ref.loadIndex();//Load city_index.txt into a B tree.
						client_index  = client_ref.loadIndex();//Load client_index.txt into a B tree.
						phone_index  = phone_ref.loadIndex();//Load phone_index.txt into a B tree.
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}
				break;
			case 'j':
				cout << "\nCheck which index status? (Type in your answer and press ENTER or CTR+Z to exit)\n";
				cout << "1. City\n2. Client\n3. Phone\n4. Call\n5. All\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						city_ref.checkIndexStatus();
						break;
					case '2':
						client_ref.checkIndexStatus();
						break;
					case '3':
						phone_ref.checkIndexStatus();
						break;
					case '4':
						call_ref.checkIndexStatus();
						break;
					case '5':
						city_ref.checkIndexStatus();
						client_ref.checkIndexStatus();
						phone_ref.checkIndexStatus();
						call_ref.checkIndexStatus();
						break;
					default:
						cout <<"Wrong Input.\n";
						break;
				}
				break;
			default:
				cout << "Wrong Input.\n";
				break;
		}
	}while(true);
}

//Add client from user input.
BTree addClientMenu(BTree client_index){
	int inputs_int;
	string inputs;
	client temp2;
	cout << "Client ID? (13 DIGITS)\n";
	std::getline (cin,inputs);
	temp2.setId_client(inputs);
	cout << "Client Name? (MAX 40 CHARACTERS)\n";
	std::getline (cin,inputs);
	temp2.setName(inputs);
	cout << "Client Gender? (M or F)\n";
	std::getline (cin,inputs);
	temp2.setGender(inputs.at(0));
	cout << "Client ID City? ()\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	temp2.setId_city(inputs_int);
	return temp2.addClient(temp2, client_index);
}

//Add city from user input.
BTree addCityMenu(BTree city_index){
	int inputs_int;
	string inputs;
	city temp;
	cout << "City ID? (MAX 4 DIGITS)\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	temp.setId_city(inputs_int);
	cout << "City Name? (MAX 40 CHARACTERS)\n";
	std::getline (cin,inputs);
	temp.setName(inputs);
	return temp.addCity(temp, city_index);
}

//Add phone from user input.
BTree addPhoneMenu(BTree phone_index){
	int inputs_int;
	string inputs;
	phone temp;
	cout << "Phone Number? (8 DIGITS)\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	temp.setNumber(inputs_int);
	cout << "Client ID? (13 DIGITS)\n";
	std::getline (cin,inputs);
	temp.setId_client(inputs);
	return temp.addPhone(temp, phone_index);
}

//Delete city by ID
BTree deleteCityMenu(BTree city_index){
	int id;
	city city_ref;
	cout << "City ID to delete? (MAX 4 DIGITS)\n";
	cin >> id;
	cin.ignore();

	BTKey temp = city_index.searchBTK(id);
	city_index.remove(temp);
	city_ref.availDelete(temp.rrn);
	return city_index;
}

//Delete client by ID
BTree deleteClientMenu(BTree client_index){
	long id;
	client client_ref;
	cout << "Client ID to delete? (13 DIGITS)\n";
	cin >> id;
	cin.ignore();
	BTKey temp = client_index.searchBTK(id);
	client_index.remove(temp);
	client_ref.availDelete(temp.rrn);
	return client_index;
}

//Delete phone by Number
BTree deletePhoneMenu(BTree phone_index){
	long id;
	phone phone_ref;
	cout << "Phone Number to delete? (8 DIGITS)\n";
	cin >> id;
	cin.ignore();

	BTKey temp = phone_index.searchBTK(id);
	phone_index.remove(temp);
	phone_ref.availDelete(temp.rrn);
	return phone_index;
}
//////////////////////////////////////////MENU FUNCTIONS END//////////////////////////////////////////////////

//////////////////////////////////////////INITIAL COMPONENTS START////////////////////////////////////////////
//Checks if we need to re-index a file
void init_Check(){
	city city_ref;
	city_ref.checkIndex();
	client client_ref;
	client_ref.checkIndex();
	call call_ref;
	call_ref.checkIndex();
	phone phone_ref;
	phone_ref.checkIndex();
}
//////////////////////////////////////////INITIAL COMPONENTS END/////////////////////////////////////////////

//////////////////////////////CODE FOR CREATING THE ORIGINAL FILES -START-///////////////////////////////////
//Creates files and indexes and their respective data vectors
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

//Creates indexes
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

//Creates files
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
//////////////////////////////CODE FOR CREATING THE ORIGINAL FILES -END-////////////////////////////////////
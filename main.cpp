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
void listCityMenu(BTree);
void listClientMenu(BTree);
void listPhoneMenu(BTree);
BTree modifyClientMenu(BTree);
BTree modifyCityMenu(BTree);
BTree modifyPhoneMenu(BTree);
void searchCityMenu(BTree);
void searchClientMenu(BTree);
void searchPhoneMenu(BTree);
void searchCityMenuFile();
void searchClientMenuFile();
void searchPhoneMenuFile();

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

		cout << "\nWhat do you want to do? (Type in your answer and press ENTER)\n";
		cout << "a. Add Record\nb. Delete Record\nc. List Record\nd. Modify Record\ne. Search Record\nf. Re-Index\ng. Re-Build Files\nh. Flush Indexes\ni. Re-load Indexes\n";
		cout << "j. Check Index Status\nz. Exit\n";
		cin >> ans;
		cin.ignore();
		switch(ans){
			case 'a':
				cout << "\nWhat do you want to Add? (Type in your answer and press ENTER)\n";
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
				cout << "\nWhat do you want to Delete? (Type in your answer and press ENTER)\n";
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
				cout << "\nList which record? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n4. Call\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						cout << "\nWhich order? (Type in your answer and press ENTER)\n";
						cout << "1. Record File\n2. Index File\n";
						cin >> ans;
						cin.ignore();
						switch(ans){
							case '1':
								city_ref.availList();
								break;
							case '2':
								listCityMenu(city_index);
								break;
							default:
								cout << "Wrong Input.\n";
								break;
						}
						break;
					case '2':
						cout << "\nWhich order? (Type in your answer and press ENTER)\n";
						cout << "1. Record File\n2. Index File\n";
						cin >> ans;
						cin.ignore();
						switch(ans){
							case '1':
								client_ref.availList();
								break;
							case '2':
								listClientMenu(client_index);
								break;
							default:
								cout << "Wrong Input.\n";
								break;
						}
						break;
					case '3':
						cout << "\nWhich order? (Type in your answer and press ENTER)\n";
						cout << "1. Record File\n2. Index File\n";
						cin >> ans;
						cin.ignore();
						switch(ans){
							case '1':
								phone_ref.availList();
								break;
							case '2':
								listPhoneMenu(phone_index);
								break;
							default:
								cout << "Wrong Input.\n";
								break;
						}
						break;
					case '4':
						call_ref.availList();	
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}
				break;
			case 'd':
				cout << "\nModify what? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						city_index = modifyCityMenu(city_index);
						break;
					case '2':
						client_index = modifyClientMenu(client_index);
						break;
					case '3':
						phone_index = modifyPhoneMenu(phone_index);
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}
				break;
			case 'e':
				cout << "\nSearch for what? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						cout << "\nSearch using what? (Type in your answer and press ENTER)\n";
						cout << "1. Data file\n2. Memory Index\n";
						cin >> ans;
						cin.ignore();
						switch(ans){
							case '1':
								searchCityMenuFile();
								break;
							case '2':
								searchCityMenu(city_index);
								break;
							default:
								cout << "Wrong Input.\n";
								break;
						}
						break;
					case '2':
						cout << "\nSearch using what? (Type in your answer and press ENTER)\n";
						cout << "1. Data file\n2. Memory Index\n";
						cin >> ans;
						cin.ignore();
						switch(ans){
							case '1':
								searchClientMenuFile();
								break;
							case '2':
								searchClientMenu(client_index);
								break;
							default:
								cout << "Wrong Input.\n";
								break;
						}
						break;
					case '3':
						cout << "\nSearch using what? (Type in your answer and press ENTER)\n";
						cout << "1. Data file\n2. Memory Index\n";
						cin >> ans;
						cin.ignore();
						switch(ans){
							case '1':
								searchPhoneMenuFile();
								break;
							case '2':
								searchPhoneMenu(phone_index);
								break;
							default:
								cout << "Wrong Input.\n";
								break;
						}
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}
				break;
			case 'f':
				cout << "\nRe-index which files? (Type in your answer and press ENTER)\n";
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
				cout << "\nRe-Load which index? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n5. All\n";
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
				cout << "\nCheck which index status? (Type in your answer and press ENTER)\n";
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
			case 'z':
				exit(0);
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

//Modify client from user input.
BTree modifyClientMenu(BTree client_index){
	long inputs_int;
	string inputs;
	client temp2;
	cout << "Existing client ID? (13 DIGITS)\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	BTKey temp = client_index.searchBTK(inputs_int);
	if(client_index.searchBTKB(inputs_int)){
		cout << "New client ID? (13 DIGITS)\n";
		std::getline (cin,inputs);
		temp2.setId_client(inputs);
		stringstream(inputs) >> inputs_int;
		if(!client_index.searchBTKB(inputs_int)){
			cout << "New client Name? (MAX 40 CHARACTERS)\n";
			std::getline (cin,inputs);
			temp2.setName(inputs);
			cout << "New client Gender? (M or F)\n";
			std::getline (cin,inputs);
			temp2.setGender(inputs.at(0));
			cout << "New client ID City? ()\n";
			std::getline (cin,inputs);
			stringstream(inputs) >> inputs_int;
			temp2.setId_city(inputs_int);
			client_index.remove(temp);
			temp2.availDelete(temp.rrn);
			return temp2.addClient(temp2, client_index);
		}else{
			cout << "This record already exists, can't have duplicates. \n";
		}
	}else{
		cout << "Record does not exist...\n";
	}
	return client_index;
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


//Modify city from user input.
BTree modifyCityMenu(BTree city_index){
	int inputs_int;
	string inputs;
	city temp;
	cout << "Existing City ID? (MAX 4 DIGITS)\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	BTKey temp2 = city_index.searchBTK(inputs_int);
	if(city_index.searchBTKB(inputs_int)){
		cout << "New City ID? (MAX 4 DIGITS)\n";
		std::getline (cin,inputs);
		stringstream(inputs) >> inputs_int;
		temp.setId_city(inputs_int);
		if(!city_index.searchBTKB(inputs_int)){
			cout << "New City Name? (MAX 40 CHARACTERS)\n";
			std::getline (cin,inputs);
			temp.setName(inputs);
			city_index.remove(temp2);
			temp.availDelete(temp2.rrn);
			return temp.addCity(temp, city_index);
		}else{
			cout << "This record already exists, can't have duplicates. \n";
		}
	}else{
		cout << "Record does not exist...\n";
	}
	return city_index;
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

//Modify phone from user input.
BTree modifyPhoneMenu(BTree phone_index){
	long inputs_int;
	string inputs;
	phone temp;
	cout << "Existing Phone Number? (8 DIGITS)\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	BTKey temp2 = phone_index.searchBTK(inputs_int);
	if(phone_index.searchBTKB(inputs_int)){
		cout << "New Phone Number? (8 DIGITS)\n";
		std::getline (cin,inputs);
		stringstream(inputs) >> inputs_int;
		temp.setNumber(inputs_int);
		if(!phone_index.searchBTKB(inputs_int)){
			cout << "New Client ID? (13 DIGITS)\n";
			std::getline (cin,inputs);
			temp.setId_client(inputs);
			phone_index.remove(temp2);
			temp.availDelete(temp2.rrn);
			return temp.addPhone(temp, phone_index);
		}else{
			cout << "This record already exists, can't have duplicates. \n";
		}
	}else{
		cout << "Record does not exist...\n";
	}
}

//Delete city by ID
BTree deleteCityMenu(BTree city_index){
	int id;
	city city_ref;
	cout << "City ID to delete? (MAX 4 DIGITS)\n";
	cin >> id;
	cin.ignore();
	if(city_index.searchBTKB(id)){
		BTKey temp = city_index.searchBTK(id);
		city_index.remove(temp);
		city_ref.availDelete(temp.rrn);
	}else{
		cout << "Record does not exist...\n";
	}
	return city_index;
}

//Delete client by ID
BTree deleteClientMenu(BTree client_index){
	long id;
	client client_ref;
	cout << "Client ID to delete? (13 DIGITS)\n";
	cin >> id;
	cin.ignore();
	if(client_index.searchBTKB(id)){
		BTKey temp = client_index.searchBTK(id);
		client_index.remove(temp);
		client_ref.availDelete(temp.rrn);
	}else{
		cout << "Record does not exist...\n";
	}
	return client_index;
}

//Delete phone by Number
BTree deletePhoneMenu(BTree phone_index){
	long id;
	phone phone_ref;
	cout << "Phone Number to delete? (8 DIGITS)\n";
	cin >> id;
	cin.ignore();
	if(phone_index.searchBTKB(id)){
		BTKey temp = phone_index.searchBTK(id);
		phone_index.remove(temp);
		phone_ref.availDelete(temp.rrn);
	}else{
		cout << "Record does not exist...\n";
	}
	return phone_index;
}

//Search Cities index
void searchCityMenu(BTree city_index){
	int id;
	city city_ref;
	cout << "City ID to search? (MAX 4 DIGITS)\n";
	cin >> id;
	cin.ignore();
	if(city_index.searchBTKB(id)){
		BTKey temp = city_index.searchBTK(id);
		city_ref.search(temp.rrn);
	}else{
		cout << "Record not found...\n";
	}
}

void searchCityMenuFile(){
	city city_ref;
	long id;
	cout << "City ID to search? (MAX 4 DIGITS)\n";
	cin >> id;
	cin.ignore();
	cout << city_ref.search2(id);
}

//Search Clients index
void searchClientMenu(BTree client_index){
	long id;
	client client_ref;
	cout << "client ID to search? (13 DIGITS)\n";
	cin >> id;
	cin.ignore();
	if(client_index.searchBTKB(id)){
		BTKey temp = client_index.searchBTK(id);
		client_ref.search(temp.rrn);
	}else{
		cout << "Record not found...\n";
	}
}

void searchClientMenuFile(){
	client client_ref;
	long id;
	cout << "Client ID to search? (MAX 4 DIGITS)\n";
	cin >> id;
	cin.ignore();
	cout << client_ref.search2(id);
}

//Search Phones index
void searchPhoneMenu(BTree phone_index){
	long id;
	phone phone_ref;
	cout << "phone Number to search? (13 DIGITS)\n";
	cin >> id;
	cin.ignore();
	if(phone_index.searchBTKB(id)){
		BTKey temp = phone_index.searchBTK(id);
		phone_ref.search(temp.rrn);
	}else{
		cout << "Record not found...\n";
	}
}

void searchPhoneMenuFile(){
	phone phone_ref;
	long id;
	cout << "Phone Number to search? (8 DIGITS)\n";
	cin >> id;
	cin.ignore();
	cout << phone_ref.search2(id);
}

//List Cities using index
void listCityMenu(BTree city_index){
	fstream is("cities_vector.txt");
	city_index.traverseList(1, is);
	is.close();
}

//List Clients using index
void listClientMenu(BTree clients_index){
	fstream is("clients_vector.txt");
	clients_index.traverseList(2, is);
	is.close();
}

//List Phones using index
void listPhoneMenu(BTree phones_index){
	fstream is("phones_vector.txt");
	phones_index.traverseList(3, is);
	is.close();
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
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
void payment(BTree);
void JsonExportCity();
void JsonExportClient();
void JsonExportPhone();

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
		cout << "j. Check Index Status\nk. Payments\nl. JSON\nz. Exit\n";
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
				cout << "\nFlush which index? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n4. All\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						cout << "Attempting flush...\n";
						city_ref.reIndex();
						city_index  = city_ref.loadIndex();//Load city_index.txt into a B tree.
						cout << "Succesfully flushed city index to disc.\n";
						break;
					case '2':
						cout << "Attempting flush...\n";
						client_ref.reIndex();
						client_index  = client_ref.loadIndex();//Load client_index.txt into a B tree.
						cout << "Succesfully flushed client index to disc.\n";
						break;
					case '3':
						cout << "Attempting flush...\n";
						phone_ref.reIndex();
						phone_index  = phone_ref.loadIndex();//Load phone_index.txt into a B tree.
						cout << "Succesfully flushed phone index to disc.\n";
						break;
					default:
						cout << "Attempting flush...\n";
						city_ref.reIndex();
						client_ref.reIndex();
						phone_ref.reIndex();
						city_index  = city_ref.loadIndex();//Load city_index.txt into a B tree.
						client_index  = client_ref.loadIndex();//Load client_index.txt into a B tree.
						phone_index  = phone_ref.loadIndex();//Load phone_index.txt into a B tree.
						cout << "Succesfully flushed every index to disc.\n";
						break;
				}
				break;
			case 'i':
				cout << "\nRe-Load which index? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n4. All\n";
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
			case 'k':
				payment(client_index);

				break;
			case 'l':
				cout << "\nExport what JSON? (Type in your answer and press ENTER)\n";
				cout << "1. City\n2. Client\n3. Phone\n";
				cin >> ans;
				cin.ignore();
				switch(ans){
					case '1':
						JsonExportCity();
						break;
					case '2':
						JsonExportClient();
						break;
					case '3':
						JsonExportPhone();
						break;
					default:
						cout << "Wrong Input.\n";
						break;
				}
				break;
			case 'z':
				cout << "Attempting flush...\n";
				city_ref.reIndex();
				client_ref.reIndex();
				phone_ref.reIndex();
				cout << "Succesfully flushed every index to disc.\n";
				cout << "Exiting application... Bye  :-)\n";
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
	if(!client_index.searchBTKB(atol(inputs.c_str()))){
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
	}else{
		cout << "This record already exists...\n";
		return client_index;
	}
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
	if(!city_index.searchBTKB(inputs_int)){
		temp.setId_city(inputs_int);
		cout << "City Name? (MAX 40 CHARACTERS)\n";
		std::getline (cin,inputs);
		temp.setName(inputs);
		return temp.addCity(temp, city_index);
	}else{
		cout << "This record already exists...\n";
		return city_index;
	}
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
	if(!phone_index.searchBTKB(inputs_int)){
		temp.setNumber(inputs_int);
		cout << "Client ID? (13 DIGITS)\n";
		std::getline (cin,inputs);
		temp.setId_client(inputs);
		return temp.addPhone(temp, phone_index);
	}else{
		cout << "This record already exists...\n";
		return phone_index;
	}
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
	int iter;
    int counter = 0;
    int num=1;
    cout << "How many records per page? (NUMBER)\n";
    cin >> iter;
    cin.ignore();
	city_index.traverseList(1, is);
	is.close();
}

//List Clients using index
void listClientMenu(BTree clients_index){
	fstream is("clients_vector.txt");
	int iter;
    int counter = 0;
    int num=1;
    cout << "How many records per page? (NUMBER)\n";
    cin >> iter;
    cin.ignore();
	clients_index.traverseList(2, is);
	is.close();
}

//List Phones using index
void listPhoneMenu(BTree phones_index){
	fstream is("phones_vector.txt");
	int iter;
    int counter = 0;
    int num=1;
    cout << "How many records per page? (NUMBER)\n";
    cin >> iter;
    cin.ignore();
	phones_index.traverseList(3, is);
	is.close();
}

//Payment Method Calc
void payment(BTree client_index){
	long inputs_int;
	string inputs;
	client temp;
	int iter = 0;
	int counter = 0;
	int fee_counter = 1;
	cout << "Existing client ID? (13 DIGITS)\n";
	std::getline (cin,inputs);
	stringstream(inputs) >> inputs_int;
	cout << "How many Fee's per page? (NUMBER)\n";
	cin >> iter;
	cin.ignore();
	if(client_index.searchBTKB(inputs_int)){
		fstream phonie("phones_vector.txt");
		fstream callies("calls_vector.txt");
		if(phonie.is_open() && callies.is_open()){
			int rrn = 1;
			long offset = 110+rrn*33;
			phonie.seekg (0, phonie.end);//Move get cursor to the end of file.
		    long length = phonie.tellg();//Save the value to a variable.
			do{
				offset = 110+rrn*33;
				char * mark = new char;
				char buffer[8];
				phonie.seekg(offset);
				phonie.read(mark,1);
				char buffer3[13];
				phonie.seekg(offset+19);
				phonie.read(buffer3,13);
				string str(buffer3,13);

				if(*mark == '_' && atol(str.c_str()) == inputs_int){
					phonie.seekg(offset + 10);
					phonie.read(buffer, 8);
					string number(buffer,8);
					cout << number << "\n";
					int rrn2 = 1;
					long offset2 = 128+rrn*58;
					callies.seekg (0, phonie.end);//Move get cursor to the end of file.
		    		long length2 = callies.tellg();//Save the value to a variable.
					do{
						offset2 = 128+rrn2*58;
						char * mark2 = new char;
						char buffer4[8];
						callies.seekg(offset2);
						callies.read(mark2,1);
						callies.seekg(offset2+10);
						callies.read(buffer4,8);
						string str2(buffer4,8);
						if(*mark2 == '_' && number == str2){
							char buffer7[8];
							callies.seekg(offset2 + 49);
							callies.read(buffer7,8);
							string str3(buffer7,8);

							char yearstart[4];
							callies.seekg(offset2 + 19);
							callies.read(yearstart,4);
							string ys(yearstart,4);
							char monthstart[2];
							callies.seekg(offset2 + 23);
							callies.read(monthstart,2);
							string ms(monthstart,2);
							char daystart[2];
							callies.seekg(offset2 + 25);
							callies.read(daystart,2);
							string ds(daystart,2);
							char hourstart[2];
							callies.seekg(offset2 + 27);
							callies.read(hourstart,2);
							string hs(hourstart,2);
							char minutestart[2];
							callies.seekg(offset2 + 29);
							callies.read(minutestart,2);
							string mins(minutestart,2);
							char secondstart[2];
							callies.seekg(offset2 + 31);
							callies.read(secondstart,2);
							string secs(secondstart,2);

							char yearend[4];
							callies.seekg(offset2 + 34);
							callies.read(yearend,4);
							string ye(yearend,4);
							char monthend[2];
							callies.seekg(offset2 + 38);
							callies.read(monthend,2);
							string me(monthend,2);
							char dayend[2];
							callies.seekg(offset2 + 40);
							callies.read(dayend,2);
							string de(dayend,2);
							char hourend[2];
							callies.seekg(offset2 + 42);
							callies.read(hourend,2);
							string he(hourend,2);
							char minuteend[2];
							callies.seekg(offset2 + 44);
							callies.read(minuteend,2);
							string mine(minuteend,2);
							char secondend[2];
							callies.seekg(offset2 + 46);
							callies.read(secondend,2);
							string sece(secondend,2);

							cout << "Transaction Number: " << fee_counter << "   "<< str2 << " to " << str3 <<"\n";
							cout << "Begin: " << ys << "/" << ms << "/" << ds << " at " << hs << ":" << mins << ":" << secs << "\n";
							cout << "Ended: " << ye << "/" << me << "/" << de << " at " << he << ":" << mine << ":" << sece << "\n";
							
							int shour = atoi(hourstart);
							int ehour = atoi(hourend);
							int sminutes = atoi(minutestart);
							int eminutes = atoi(minuteend);
							int sseconds = atoi(secondstart);
							int eseconds = atoi(secondend);
							double morningprice = 0;
							double midprice = 0;
							double lateprice = 0;
							double totalprice = 0;
							if(shour < 8){
								if(ehour < 8){
									morningprice = (ehour - shour - 1)*0.01*60 + (60 - sminutes + eminutes)*0.01;
								}else if(ehour < 16){
									morningprice = (8 - shour - 1)*0.01*60 + (60 - sminutes)*0.01;
									midprice = (ehour - 8)*0.05*60 + eminutes*0.05;
								}else{
									morningprice = (8 - shour - 1)*0.01*60 + (60 - sminutes)*0.01;
									midprice = (ehour - 8)*0.05*60;
									lateprice = (ehour - 16)*0.04*60 + eminutes*0.04;
								}
							}else if(shour < 16){
								if(ehour < 16){
									midprice = (ehour - shour -1)*0.05*60 + (60 - sminutes + eminutes)*0.05;
								}else{
									midprice = (16 - shour -1)*0.05*60 + (60 - sminutes)*0.05;
									lateprice = (ehour - 16)*0.04*60 + eminutes*0.04; 
								}
							}else{
								lateprice = (ehour - shour -1)*0.04*60 + (60 - sminutes + eminutes)*0.04;
							}
							totalprice = morningprice + midprice + lateprice;
							cout << "Early Fee: " << morningprice << "$ Mid Fee: " << midprice << "$ Late Fee: " << lateprice << "$ *** Total: " << totalprice <<"$ ***\n\n";
							counter ++;
							fee_counter++;
							if(counter == iter){
								char ans;
								cout << "Show More? (y/n)\n";
								cin >> ans;
								cin.ignore();
								if(ans == 'y')
									counter = 0;
								else
									break;
							}
						}
						rrn2++;
					}while(rrn2<(length2-128)/58);
				}
				rrn++;
			}while(rrn<(length-110)/33);
		}else{
			cout << "Can't open files...\n";
		}
	}else{
		cout << "Client doesn't exist...\n";
	}

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

void JsonExportCity(){
	fstream is("cities_vector.txt");
	ofstream json("cities_jason.txt");
	cout << "Attempting action...\n";
	int rrn = 1;
	if(is.is_open() && json.is_open()){
		is.seekg (0, is.end);//Move get cursor to the end of file.
    	long length = ((long)is.tellg()-111)/55;
    	json << "{\"cities\":[\n";
		do{
			int offset=111+rrn*55 + 10;
			char buffer1[4];
			is.seekg(offset);
			is.read(buffer1,4);
			string str(buffer1,4);
			char buffer2[40];
			is.seekg(offset+4);
			is.read(buffer2,40);
			string str2(buffer2,40);
			if(rrn == length-1)
				json << "{\"id\":\""<<str<<"\", \"name\":\""<<str2<<"\"}\n]}";
			else
				json << "{\"id\":\""<<str<<"\", \"name\":\""<<str2<<"\"},\n";
			rrn++;
		}while(rrn<length);
		cout << "JSON-ED Succesfuilly.\n";
	}else{
		cout << "Could not open file -cities_vector.txt- or -cities_json.txt- \n";
	}
}

void JsonExportClient(){
	fstream is("clients_vector.txt");
	ofstream json("clients_jason.txt");
	cout << "Attempting action...\n";
	int rrn = 1;
	if(is.is_open() && json.is_open()){
		is.seekg (0, is.end);//Move get cursor to the end of file.
    	long length = ((long)is.tellg()-136)/72;
    	json << "{\"clients\":[\n";
		do{
			int offset=136+rrn*72 + 10;
			char buffer1[13];
			is.seekg(offset);
			is.read(buffer1,13);
			string str(buffer1,13);
			char buffer2[40];
			is.seekg(offset+14);
			is.read(buffer2,40);
			string str2(buffer2,40);
			char buffer3[1];
			is.seekg(offset+55);
			is.read(buffer3,1);
			string str3(buffer3,1);
			char buffer4[4];
			is.seekg(offset+57);
			is.read(buffer4,4);
			string str4(buffer4,4);
			if(rrn == length-1)
				json << "{\"id\":\""<<str<<"\", \"name\":\""<<str2<<"\", \"gender\":\""<<str3<<"\", \"city\":\""<<str4<<"\"}\n]}";
			else
				json << "{\"id\":\""<<str<<"\", \"name\":\""<<str2<<"\", \"gender\":\""<<str3<<"\", \"city\":\""<<str4<<"\"},\n";
			rrn++;
		}while(rrn<length);
		cout << "JSON-ED Succesfuilly.\n";
	}else{
		cout << "Could not open file -clients_vector.txt- or -clients_json.txt- \n";
	}
}

void JsonExportPhone(){
	fstream is("phones_vector.txt");
	ofstream json("phones_jason.txt");
	cout << "Attempting action...\n";
	int rrn = 1;
	if(is.is_open() && json.is_open()){
		is.seekg (0, is.end);//Move get cursor to the end of file.
    	long length = ((long)is.tellg()-111)/55;
    	json << "{\"phones\":[\n";
		do{
			int offset=110+rrn*33 + 10;
			char buffer1[8];
			is.seekg(offset);
			is.read(buffer1,8);
			string str(buffer1,8);
			char buffer2[13];
			is.seekg(offset+9);
			is.read(buffer2,13);
			string str2(buffer2,13);
			if(rrn == length-1)
				json << "{\"number\":\""<<str<<"\", \"client_id\":\""<<str2<<"\"}\n]}";
			else
				json << "{\"number\":\""<<str<<"\", \"client_id\":\""<<str2<<"\"},\n";
			rrn++;
		}while(rrn<length);
		cout << "JSON-ED Succesfuilly.\n";
	}else{
		cout << "Could not open file -cities_vector.txt- or -cities_json.txt- \n";
	}
}
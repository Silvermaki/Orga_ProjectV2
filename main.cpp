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

int main(int argc, char* argv[]){
	/*****Create Files, Un-comment if you need to re-make the original files.*****/
	//init_Files();
	init_Check();
	BTree t(3);
	BTKey temp(1,3);
	t.insert(temp);
	BTKey temp1(3,6);
	t.insert(temp1);
    BTKey temp2(10,13);
	t.insert(temp2);
    BTKey temp3(11,14);
	t.insert(temp3);
    BTKey temp4(13,16);
	t.insert(temp4);
    BTKey temp5(14,17);
	t.insert(temp5);
    BTKey temp6(15,18);
	t.insert(temp6);
    BTKey temp7(18,21);
	t.insert(temp7);
	BTKey temp8(16,19);
	t.insert(temp8);
	BTKey temp9(19,22);
	t.insert(temp9);
    BTKey temp10(24,27);
	t.insert(temp10);
    BTKey temp11(25,28);
	t.insert(temp11);
    BTKey temp12(21,24);
	t.insert(temp12);
    BTKey temp13(4,7);
	t.insert(temp13);
    BTKey temp14(5,8);
	t.insert(temp14);
    BTKey temp15(20,23);
	t.insert(temp15);
    BTKey temp16(22,25);
	t.insert(temp16);
    BTKey temp17(2,5);
	t.insert(temp17);
    BTKey temp18(17,20);
	t.insert(temp18);
    BTKey temp19(12,15);
	t.insert(temp19);
	BTKey temp20(6,9);
	t.insert(temp20);

    cout << "Traversal of tree constructed is\n";
    t.traverse();
    cout << endl;
 
    t.remove(temp20);
    cout << "Traversal of tree after removing 6\n";
    t.traverse();
    cout << endl;
 
    t.remove(temp4);
    cout << "Traversal of tree after removing 13\n";
    t.traverse();
    cout << endl;
 
    t.remove(temp16);
    cout << "Traversal of tree after removing 22\n";
    t.traverse();
    cout << endl;
 
    t.remove(temp10);
    cout << "Traversal of tree after removing 24\n";
    t.traverse();
    cout << endl;
 
    t.remove(temp1);
    cout << "Traversal of tree after removing 3\n";
    t.traverse();
    cout << endl;
 
    t.remove(temp2);
    cout << "Traversal of tree after removing 10\n";
    t.traverse();
    cout << endl;

    BTKey temp40 = t.searchBTK(25);
    cout << "Search 25: " << temp40.key << "::" << temp40.rrn;
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
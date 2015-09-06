#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>

using namespace std;

//################### START CLASSES 

class numero_tel{
  public:
  	int num;
  	numero_tel(int);
  	numero_tel();
};

class llamadas{
   public:
   	int num;
	int inicio, final;
   	llamadas(int,int,int);
   	llamadas();
};

//################### END CLASSES 

//################### START CLASS numero_tel FUNCTIONS

numero_tel::numero_tel(){
	num = 0;
}

numero_tel::numero_tel(int arg_num){
	num = arg_num;
}

ostream& operator<<(ostream& output, const numero_tel& numero) {
  return output << numero.num << endl;
}

istream& operator>>(istream& input, numero_tel& numero){
	input >> numero.num;
	return input;
}

//################### END CLASS numero_tel FUNCTIONS

//################### START CLASS llamadas FUNCTIONS

llamadas::llamadas(){
	num = 0;
	inicio = 0;
	final = 0;
}

llamadas::llamadas(int arg_num, int arg_inicio, int arg_final){
	num = arg_num;
	inicio = arg_inicio;
	final = arg_final;
}

ostream& operator<<(ostream& output, const llamadas& llamada) {
  return output << llamada.num << "\t" << llamada.inicio << "\t" << llamada.final << endl;
}

istream& operator>>(istream& input, llamadas& llamada){
	input >> llamada.num >> llamada.inicio >> llamada.final;
	return input;
}

//################### END CLASS llamadas FUNCTIONS

//################### START FUNCTIONS

//################### END FUNCTIONS

int main(int argc, char* argv[]){
	int i;
	srand(time(NULL));
	int list[750];
	string temp_num="";
	ofstream myfile;
    myfile.open ("numeros.txt");
	for(i=0;i<750;i++){
		int number = 20000000 + (rand()%10)*1000000 + (rand()%10)*100000 + (rand()%10)*10000 + (rand()%10)*1000 + (rand()%10)*100 + (rand()%10)*10 + (rand()%10);
		list[i]=number;
		myfile << number << endl;
	}
	myfile.close();
	return 0;
}
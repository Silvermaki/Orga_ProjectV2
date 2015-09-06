#ifndef CALL_H
#define CALL_H
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class call{
  	int number;
  	long start;
  	long end;
  	int destination;
  public:
  	call();
  	call(int,long,long,int);
  	int getNumber();
  	void setNumber(int);
  	long getStart();
  	void setStart(long);
  	long getEnd();
  	void setEnd(long);
  	int getDestination();
  	void setDestination(int);
  	vector<int> createCallStart(int);
  	vector<int> createCallEnd(int,vector<int>);
  	vector<call> callVector(vector<int> numbers, vector<long> starting, vector<long> ending);
  	vector<long> startLong(vector<int>);
	vector<long> endLong(vector<int>);
  	string toString();
};

#endif
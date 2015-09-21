all: prog 

prog: main.o  call.o phone.o city.o client.o BTree.o 
	g++ main.o call.o phone.o city.o client.o BTree.o -o prog

main.o: main.cpp
	g++ -c main.cpp

call.o: call.cpp
	g++ -c call.cpp

phone.o: phone.cpp
	g++ -c phone.cpp

city.o: city.cpp
	g++ -c city.cpp

client.o: client.cpp
	g++ -c client.cpp

BTree.o: BTree.cpp
	g++ -c BTree.cpp

clean:
	rm *o prog
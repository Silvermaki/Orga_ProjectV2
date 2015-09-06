all: prog 

prog: main.o  call.o phone.o city.o client.o
	g++ main.o call.o phone.o city.o client.o -o prog

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
clean:
	rm *o prog
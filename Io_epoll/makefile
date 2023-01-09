main:main.o IoEpoll.o
	g++ -o main main.o IoEpoll.o
main.o:main.cpp
	g++ -c main.cpp
IoEpoll.o:
	g++ -c IoEpoll.cpp
clean:
	rm -rf main.o IoEpoll.o
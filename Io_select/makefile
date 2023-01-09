main: main.o IoSelect.o
	g++ -o main main.o IoSelect.o
main.o:main.cpp
	g++ -c main.cpp
IoSelect:IoSelect.cpp
	g++ -c IoSelect.cpp

clean:
	rm -rf main.o IoSelect.o
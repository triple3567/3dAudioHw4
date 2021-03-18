all: main.cpp
	g++ -o main.o main.cpp HRTFContainer.cpp

clean: main.o
	rm main.o
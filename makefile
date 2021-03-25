all: main.cpp
	g++ -o main.exe main.cpp HRTFContainer.cpp

clean: main.exe
	rm main.exe
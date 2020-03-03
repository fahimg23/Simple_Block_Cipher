CXX = gcc
CXXFLAGS = -Wall -g -pthread

main: main.o encrypt.o file_buffer.o
	$(CXX) $(CXXFLAGS) -o main main.o encrypt.o file_buffer.o

main.o: main.c encrypt.h file_buffer.h
	$(CXX) $(CXXFLAGS) -c main.c

encrypt.o: encrypt.c encrypt.h
	$(CXX) $(CXXFLAGS) -c encrypt.c

file_buffer.o: file_buffer.c file_buffer.h
	$(CXX) $(CXXFLAGS) -c file_buffer.c

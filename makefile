CXX = g++
CXXFLAGS = -Wall

all: Int4MMH.o MMHeap.o driver.cpp
        $(CXX) $(CXXFLAGS) Int4MMH.o MMHeap.o driver.cpp -o all

MMHeap.o: Int4MMH.o MMHeap.cpp
        $(CXX) $(CXXFLAGS) -c MMHeap.cpp

Int4MMH.o: Int4MMH.h Int4MMH.cpp
        $(CXX) $(CXXFLAGS) -c Int4MMH.cpp

clean:
        rm *.o*

run:
        ./all

val:
        valgrind ./all

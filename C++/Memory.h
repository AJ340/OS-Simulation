#ifndef MEMORY_H
#define MEMORY_H


//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.
#include <list>
#include "PCB.h"
#include <iterator>
#include <iostream>
using namespace std;


struct MemoryObj;

struct HoleInfo;

class Memory
{
public:

	Memory();

	Memory(unsigned int max_size);

	void operator=(Memory other);

	void allocate( PCB a, unsigned int size);

	//Remove a from memory
	void freeMem(PCB a);

	void print();
	
	//Change size of memory
	void resizeMem(unsigned int max_size);

private:
	list<MemoryObj> mem;

	//Gets worst fit for a process. (Largest possible hole for process size)
	HoleInfo getWorstFit(unsigned int neededSpace);

	//Combines any consecutive holes
	void mergeFreeSpaces();


};

#include "Memory.cpp"


#endif





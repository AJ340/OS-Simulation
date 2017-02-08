#ifndef SYSTEM_H
#define SYSTEM_H




#include "CPU.h"
#include "Memory.h"
#include "Device.h"
#include <vector>
#include <sstream>

using namespace std;
//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.

class System
{
public:

	System();

	System(unsigned int memAmmt);

	//Create a process in CPU
	void createProcess(unsigned int p_memAmnt, int priority);

	//Terminate current process in CPU
	void terminateCurrent();

	//Create devices and Printers
	void create_D_and_P(int d, int p);

	//Current process in cpu request a device or printer 
	// (string device only works when device = "dX"
	// where X is smaller than size) 
	//Returns true if process actually moved to an existing device. 
	//False if process couldnt be moved due to device not existing
	bool requestDevice(string device, string file_name, string file_size);

	//device described by string device finishes its current job. Returns true if a 
	//Job was actually finished. False if device was idle;
	bool finishDeviceJob(string device);

	//Makes the memory size max_size
	void sizeMem(unsigned int max_size);

	//Debug print. Sloppily prints info about system.
	void print();

	//Print interface for all parts of System
	bool print(string what);

private:
	int pidRange;
	CPU cpu_1;
	Memory ram;	
	vector<Device> disks;
	vector<Device> printers;


	bool checkNumValidityDeviceString(string s, char c, char d);

	int generatePID();
	
	void handleProcess(PCB proc, unsigned int p_memAmnt);
	
};

#include "System.cpp"

#endif

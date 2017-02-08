#ifndef DEVICE_H
#define DEVICE_H

//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.
#include "PCB.h"
#include <string>
#include <deque>
#include <iostream>
using namespace std;

//Class to group necessary info for a Device JOB.
class DeviceObj
{
	public:
	PCB process;
	string file_name;
	string file_size;

	void print()
	{
		cout << "{PID" << ":" << process.getPID() << ", filename:" <<
			file_name << ", filesize: " <<  file_size << "}";	
		}
};



//Both disks and printers utilize the same information, so theyll both be of type Device
class Device
{
public:
	Device();

	Device(string device_name);
	
	Device(string device_name, PCB process, string file_name, string file_size);
	
	//Process arriving to a device (disk/printer)
	void arrive(PCB process, string file_name, string file_size);
	
	//Current process leaves device
	PCB leave();

	void print();

	//If current process
	bool isIdle();

	//name of device
	string getName();
	
private:
	deque<DeviceObj> device_queue;
	DeviceObj* current_job;
	string name;


	void startNewJob();
};

#include "Device.cpp"

#endif

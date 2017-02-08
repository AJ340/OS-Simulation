#ifndef CPU_H
#define CPU_H
//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.

#include "PCB.h"
#include <string>
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

class CPU
{
public:
	CPU();
	
	CPU(PCB a);
	
	//Process arrives at readyqueue and either becomes current_process or 
	// performs context switch if neccesary
	void arrive(PCB process);
	
	//Current_process leaves CPU. performs context switch if necessary
	PCB leave();

	//Prints out current_process a
	void print();

	//If cpu has dummy empty PCB (with pid=0), return 1
	bool isEmpty();


private:
	priority_queue<PCB, vector<PCB>, greater<PCB> > readyQueue;
	PCB current_process;

	//Makes sure process with smallest priority is running
	void contextSwitch();

};

#include "CPU.cpp"

#endif
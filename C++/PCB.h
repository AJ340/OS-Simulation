#ifndef PCB_H
#define PCB_H

//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.
#include <iostream> 
using namespace std;

class PCB
{
public:

	PCB();
	
	PCB(PCB &p);

	PCB(const PCB &p);
	
	PCB(int x);
	//Overloaded Operators
	void operator=(PCB p);

	bool operator>( PCB other);
	
	bool operator>( const PCB & other) const ;
	
	//Getters
	int getPID() const;

	int getPriority() const;

 	//Setters
	void setPID(int n_PID);

	void setPriority(int n_Priority);

 	void print() const;
 	
private:
	int PID;
	int priority;

};
#include "PCB.cpp"

#endif 

//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.

	PCB::PCB()
	{
		this->PID = 0;
		this->priority = 9999999;
	}

	PCB::PCB(PCB &p)
	{
		 this->PID = p.PID;
		 this->priority = p.priority;
	}

	PCB::PCB(const PCB &p)
	{
		 this->PID = p.PID;
		 this->priority = p.priority;
	}


	//Overloaded Operators
	void PCB::operator=(PCB p)
	{
		this->PID = p.PID;
		this->priority = p.priority;
	}

	bool PCB::operator>( PCB other)
	{
		if (this->priority > other.priority)
			return true;
		return false;
	} 

	bool PCB::operator>( const PCB & other) const 
	{
		if (this->priority > other.priority)
			return true;
		return false;
	} 

	//Getters
	int PCB::getPID() const
	{ return PID; }

	int PCB::getPriority() const 
	{ return priority; }


 	//Setters
	void PCB::setPID(int n_PID)
 	{ PID = n_PID;}

	void PCB::setPriority(int n_Priority)
 	{ priority = n_Priority;}

 	void PCB::print() const
 	{
 		cout << "{PID:" << PID << " Priority:" << priority << "}";
 	}





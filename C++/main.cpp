#include <iostream>
#include "System.h"

//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.
System * system_Gen(unsigned int memSize, int numDisk, int numPrint)
{
	System* s_ptr = new System (memSize);
	s_ptr->create_D_and_P(numDisk,numPrint);
	return s_ptr;
}

//
void handleInput(System * s, string input)
{
	unsigned int proc_mem;
	int priority;
	string fname,fsize;


	switch(input[0])
	{
		
		case 'A':{
			bool pri=true;
			while(pri){
			cout << "Enter how much memory process will need followed by priority. (Press enter in between) " << endl;
			cin >> proc_mem >> priority;
			if(priority < 0) 
				{cout << "Priority cant be negative" << endl; continue;}
			pri=false;
			}
			s->createProcess(proc_mem, priority);
			break;
		}

		case 't':{
			s->terminateCurrent();
			cout << "Current process terminated." << endl;
			break;
		}

		case 'd':{
			cout << "Enter file name and file size (Press enter in between) " << endl;
			cin >> fname >> fsize;
			if(!s->requestDevice(input,fname,fsize))
			{
				cout <<  "*Error requesting device" << endl;
			}
			break;
		}

		case 'p':{
			cout << "Enter file name and file size (Press enter in between) " << endl;
			cin >> fname >> fsize;
			if(!s->requestDevice(input,fname,fsize))
			{
				cout <<  "*Error requesting device" << endl;
			}
			break;
		}

		case 'D':{
			if(s->finishDeviceJob(input))
				cout << "Process done using " << input << endl; 
			else
				cout << "*Error while finishing job on " << input << endl;
			break;
		}

		case 'P':{
			if(s->finishDeviceJob(input))
				cout << "Process done using " << input << endl; 
			else
				cout << "*Error while finishing job on " << input << endl;
			break;
		}

		case 'S':{
			string print;
			cout << "Enter Snapshot print command (r, m, i) " << endl;
			cin >> print;
			if(!s->print(print))
				cout << "*Error invalid snapshot command "<< endl;
			break;
		}

		default:{
			cout << "*Error: Invalid system command." << endl;
		}
	}

}

void run_Simulation()
{
	unsigned int mem_max;
	int n_disks,n_printers;
	string fname,fsize;
	bool command=true;
	System * sys_ptr;

	while(command)
	{
		cout << "Enter max memory (bytes), number of disks and number of printers. (Press enter in between) " << endl;
		cin >> mem_max >> n_disks >> n_printers;
		if(n_disks>9 || n_printers >9)
		{
			cout << "*Error: Max number of disks or devices is 9"<<endl;
			continue;
		}
		command=false;
	}
	command=true;;

	sys_ptr = system_Gen(mem_max, n_disks, n_printers);

	while(command)
	{
		string sys_cmd;
		cout << "Enter commands for system (A,t,d,p,D,P,S). Type B or b to exit simulation"<< endl;
		cin >> sys_cmd;
		if(sys_cmd == "B" || sys_cmd == "b")
		{
			command=false;
			break;
		}
		handleInput(sys_ptr,sys_cmd);
	}
	delete sys_ptr;
}

int main (int argc, char *argv[]) 
{
	
	run_Simulation();













	/*
	System s((unsigned int) 800000000);
	//cout << "created system" << endl;
	s.sizeMem((unsigned int) 7000000);
	//cout << "s.sizeMem((unsigned int) 8000000000) complete" << endl;
	
	s.createProcess((unsigned int) 1000000, 3);
	//cout << "s.createProcess((unsigned int) 1000000, 21) complete"<< endl;
		//s.print(); cout<< endl;

	 s.createProcess((unsigned int) 50000, 21);
	//cout << "s.createProcess((unsigned int) 50000, 61) complete" << endl;
		//s.print(); cout<< endl;

	 s.createProcess((unsigned int) 2000000, 61);
	//cout << "s.createProcess((unsigned int) 2000000, 3) complete"<< endl;
		//s.print(); cout<< endl;

	s.create_D_and_P(3,0);
	bool yn = s.requestDevice("d1","HAM.doc","500kb");
	if(yn==false)
		cout <<"*Error with ss;";
	yn = s.requestDevice("d1","WHOA.doc","400kb");
	if(yn==false)
		cout <<"*Error with ss;";
	yn = s.requestDevice("d1","WOW.doc","1500kb");
	if(yn==false)
		cout <<"*Error with ss;";





	//s.terminateCurrent();
	s.print(); cout<< endl;
	cout <<"FINISHING DEVICE JOBS";

	yn =s.finishDeviceJob("D1");
	if(yn==false)
		cout <<"FINISH DEVICE JOB D1 FAILED";

	yn =s.finishDeviceJob("D1");
	if(yn==false)
		cout <<"FINISH DEVICE JOB D1 FAILED";

	yn =s.finishDeviceJob("D1");
	if(yn==false)
		cout <<"FINISH DEVICE JOB D1 FAILED";

	yn=s.finishDeviceJob("D1");
	if(yn==false)
		cout <<"FINISH DEVICE JOB D1 FAILED";


	//	s.terminateCurrent();
	s.print(); cout<< endl;*/
	return 0;

}

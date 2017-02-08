//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.

	CPU::CPU()
	{ 
		current_process.setPID(0);
	}

	CPU::CPU(PCB a)
	{
		current_process = a;
	}

	void CPU::arrive(PCB process)
	{
		readyQueue.push(process);
		contextSwitch();
		return;
	}

	PCB CPU::leave()
	{
		PCB empty;
		PCB old = current_process;
		current_process = empty;
		contextSwitch();
		return old;
	}

	void CPU::print()
	{
		priority_queue<PCB, vector<PCB>, greater<PCB> > printQueue = readyQueue;

		cout << "~Process in CPU: ";
		current_process.print();cout << endl;


		cout << "~ReadyQueue: ";
		int size = printQueue.size();
		for (int i=0; i< size;i++)
		{
			(printQueue.top()).print(); 
			if(i != size-1)
				cout <<" , ";
			printQueue.pop();
		}
		cout << endl<< endl;
	}

	void CPU::contextSwitch()
	{
		//if readyqueue empty do nothing
		if(readyQueue.empty())
			return;


		PCB at_top(readyQueue.top());
		//If cpu isnt doing anything. Make at_top the currently running proess
		if(isEmpty())
		{
			current_process = at_top;
			readyQueue.pop();
			return;
		}
		//if current process priority is bigger. 
		if (current_process > at_top)
		{
			readyQueue.push(current_process);
			current_process = at_top;
			readyQueue.pop();
		}
	}

	bool CPU::isEmpty()
	{
		if(current_process.getPID() == 0)
			return true;
		return false;
	}






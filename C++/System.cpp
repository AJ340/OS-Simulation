//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.
	System::System()
	{
		pidRange =1 ;
		//cpu_1;
		//ram;

	}
	

	System::System(unsigned int memAmmt)
	{
		Memory m;
		m.resizeMem(memAmmt);
		ram = m;
		pidRange = 1;
	}

	void System::createProcess(unsigned int p_memAmnt, int priority)
	{
		int proc_pid = generatePID();
		PCB proc;
		proc.setPID(proc_pid);
		proc.setPriority(priority);
		//Debug code ... cout << "PROC: " ; proc.print(); cout << endl;
		handleProcess(proc, p_memAmnt);
	}

	void System::terminateCurrent()
	{
		PCB to_reclaim = cpu_1.leave();
		ram.freeMem(to_reclaim);
	}


	void System::create_D_and_P(int d, int p)
	{
		for(int i=1;i<=d; i++)
		{
			stringstream convert;
			convert << i;
			string s= "d"+ convert.str();
			Device add(s);
			disks.push_back(add);
		}
		for(int i=1;i<=p; i++)
		{
			stringstream convert;
			convert << i;
			string s= "p"+convert.str();
			Device add(s);
			printers.push_back(add);
		}
	}

	bool System::checkNumValidityDeviceString(string s, char c, char d)
	{
		if(s.size() > 3)
			return false;

		stringstream convert2;
		convert2 << disks.size() << printers.size();
		//Debug code .... cout << convert2.str()<< endl;
		if (convert2.str()[0] < s[1] ||  convert2.str()[0] == '0' || s[1] == '0')
			return false;

		if(c=='a')
			return true;
		else if(c=='r')
		{
			int where = s[1] - '0';
			if(d=='d' && disks[where-1].isIdle())
				return false;
			else if(d=='p' && printers[where-1].isIdle())
				return false;
			return true; 
		}
		else
			return false;


	}


	bool System::requestDevice(string device, string file_name, string file_size)
	{
		if(cpu_1.isEmpty())
		{
			cout << "  *Error: CPU is empty" << endl;
			return false;
		}
		if(device[0] == 'd')
		{
			if (!checkNumValidityDeviceString(device,'a','d'))
				return false;
			int where = device[1] - '0';
				disks[where-1].arrive(cpu_1.leave(), file_name, file_size);
			return true;
		}

		else if(device[0] == 'p')
		{
			if (!checkNumValidityDeviceString(device,'a','p'))
				return false;
			int where = device[1] - '0';
			printers[where-1].arrive(cpu_1.leave(), file_name, file_size);
			return true;
		}

		else
			cout << "*Error: d or p not detected" << endl;

		return false;

	}

	bool System::finishDeviceJob(string device)
	{
		//Debug code ... cout << convert2.str()<< endl;

		if(device[0] == 'D')
		{
			if (!checkNumValidityDeviceString(device,'r','d'))
				return false;
			int where = device[1] - '0';
			cpu_1.arrive( disks[where-1].leave());
			return true;
		}

		else if(device[0] == 'P')
		{
			if (!checkNumValidityDeviceString(device,'r','p'))
				return false;
			int where = device[1] - '0';
			cpu_1.arrive( printers[where-1].leave());
			return true;
		}

		else
			cout << "*Error: D or P not detected" << endl;
		return false;


	}

	void System::sizeMem(unsigned int max_size)
	{	
		ram.resizeMem(max_size);
	}

	void System::print()
	{
		cout << "CPU1 : " <<  endl;
		cpu_1.print();

		cout << "RAM : " <<  endl;
		ram.print();

		for (int i=0;i<disks.size();i++)
			disks[i].print();

		for (int i=0;i<printers.size();i++)
			printers[i].print();
	}


	bool System::print(string what)
	{

		switch (what[0]){
			case 'r':{
				cpu_1.print();
				break;
			}
			case 'i':{
				for(int i=0;i<disks.size();i++)
					disks[i].print();

				for(int i=0;i<printers.size();i++)
					printers[i].print();

				break;
			}
			case 'm':{
				ram.print();
				break;
			}
			default:
				return false;
			return true;
		}
		//case
		return 1;
	}


	int System::generatePID()
	{
		int old = pidRange;
		pidRange++;
		return old;
	}

	void System::handleProcess(PCB proc, unsigned int p_memAmnt)
	{
		ram.allocate(proc,p_memAmnt);
		cpu_1.arrive(proc);
	}
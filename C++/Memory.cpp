//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.

struct MemoryObj
{
	unsigned int byte;
	PCB owner;
};


struct HoleInfo
{
	list<MemoryObj>::iterator start_Position;
	unsigned int size_Available;
};


	Memory::Memory()
	{
		MemoryObj x;
		x.byte=0;
		PCB freed;
		x.owner = freed;
		mem.push_back(x);
		mem.push_back(x);
	}

	Memory::Memory(unsigned int max_size)
	{
		MemoryObj x;
		x.byte=0;
		PCB freed;
		x.owner = freed;
		mem.push_back(x);
		x.byte = max_size;
		mem.push_back(x);
	}

	void Memory::operator=(Memory other)
	{
		mem = other.mem;
	}

	void Memory::allocate( PCB a, unsigned int size)
	{
		HoleInfo wf = getWorstFit(size);
		if (wf.start_Position == mem.end())
		{
			cout << "Error: No holes found" << endl;
			return ;
		}

		MemoryObj x;
		x.byte = wf.start_Position->byte + size;
		x.owner = a;
		advance(wf.start_Position,1);
		mem.insert(wf.start_Position, x);
	} 

	void Memory::freeMem(PCB a)
	{
	//cout <<" Youre good " << endl;	
		list<MemoryObj>::iterator iterator;
		PCB empty;
		for (list<MemoryObj>::iterator iter = mem.begin(); iter != mem.end(); ++iter) 
		{
			if(iter == mem.end())
				break;
			if((iter -> owner).getPID() == a.getPID() )
			{
				//(iterator -> owner).print();
				MemoryObj j;
				j.byte= iter->byte;
				j.owner= empty;
				iterator = iter;
				mem.insert(iterator, j);
				mem.erase(iterator);

				//advance(iterator,1);
				break;
			}

		}
	//cout <<" Youre good " << endl;	
		mergeFreeSpaces();
	}

	void Memory::print()
	{
	
		list<MemoryObj>::iterator iterator, iterator2;
		cout << "_____________________________________________________________"<< endl;
		for (iterator = mem.begin(); iterator != prev(mem.end()); ++iterator) 	
		{		
			iterator2 = iterator;
			advance(iterator2,1);
			PCB one = iterator->owner, two=iterator2->owner;
			unsigned int o =iterator->byte, t =iterator2->byte;

			int pid2 =iterator2->owner.getPID();

			if(two.getPID() > 0)
				cout << "| Range " << o << " - " << t-1 << " occupied by process with pid " << pid2 << endl;
			if(two.getPID() == 0)
				cout << "| Range " << o << " - " << t-1 << " is free." << endl;
		}
		cout << "_____________________________________________________________"<< endl;

	}

	void Memory::resizeMem(unsigned int max_size){
		
		prev(mem.end())->byte = max_size;
	}


	HoleInfo Memory::getWorstFit(unsigned int neededSpace)
	{
		HoleInfo worst_fit;
		worst_fit.start_Position = mem.end();
		worst_fit.size_Available = 0;

		list<MemoryObj>::iterator iterator1, iterator2;

		for (iterator1 = mem.begin(); iterator1 != prev(mem.end()); ++iterator1) 
		{
		//for(int i=0; i< mem.size()-1; i++)
			iterator2 = iterator1;
			advance(iterator2,1);
			if (iterator2->owner.getPID() == 0)
			{
				unsigned int sz_Avail = iterator2->byte - iterator1->byte;
				if( (sz_Avail > neededSpace) && (sz_Avail > worst_fit.size_Available) )
				{
					worst_fit.start_Position = iterator1;
					worst_fit.size_Available = sz_Avail;
				}
			}
		}
		return worst_fit;
	}

		void Memory::mergeFreeSpaces()
		{
			list<MemoryObj>::iterator iterator1, iterator2;
			for (iterator1 = mem.begin(); iterator1 != prev(mem.end()); ++iterator1) 
			{
				iterator2 = iterator1;
				advance(iterator2,1);
				if((iterator1->owner.getPID()==0) && (iterator2->owner.getPID()==0))
				{
					if(iterator1 != mem.begin())
						mem.erase(iterator1);
				}
			}		

		}




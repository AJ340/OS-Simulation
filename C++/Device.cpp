//Created by Andres Quinones on 5/12/2016
//Copyright 2016, Andres Quinones, All rights reserved.






	Device::Device()
	{
		current_job = nullptr;
	}
	
	Device::Device(string device_name, PCB process, string file_name, string file_size)
	{
		DeviceObj p;
		p.process= process;
		p.file_size = file_size;
		p.file_name=file_name;

		device_queue.push_back(p);
		current_job = &device_queue.front();
		name = device_name;
	}
	
	Device::Device(string device_name)
	{
		name = device_name;
		current_job = nullptr;
	}

	void Device::arrive(PCB process, string file_name, string file_size)
	{
		DeviceObj p;
		p.process= process;
		p.file_size = file_size;
		p.file_name=file_name;
		device_queue.push_back(p);

		if(isIdle())
			startNewJob();
	}
	
	PCB Device::leave()
	{
		PCB old = current_job->process;
		current_job=nullptr;
		device_queue.pop_front();
		//device_queue.resize(device_queue.size()-1);
		startNewJob();
		return old;
	}

	void Device::print()
	{
		if(isIdle())
		{
			cout <<"|| "<< name << " is idle."<< endl;
			return;
		}
		cout << "|| "<< name << ": Current Job"; current_job->print();

		cout << endl << "|| +  " << name <<" I/O Queue : ";
		for(int i=1; i < device_queue.size();i++)
		{
			device_queue[i].print();
		}
		cout << endl;
	}
	

	void Device::startNewJob()
	{
		if(device_queue.empty())
			current_job=nullptr;
		else 
			current_job = &device_queue.front();
	}

	bool Device::isIdle()
	{
		if (current_job == nullptr)
			return true;
		return false;
	}

	string Device::getName()
	{
		return name;
	}

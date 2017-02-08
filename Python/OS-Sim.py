import sys
import os
# import random


# OS Simulation


# PCB Holder
class PCB_Holder:
    _current_PCB = ()
    def __init__(self, new_pcb=()):
        self._current_PCB = new_pcb
    
    def get_current_PCB(self):
        return self._current_PCB
    
    def switch(self, new_pcb = ()):
        temp = self._current_pcb
        self._current_pcb = new_pcb
        return temp

# CPU_QUEUE
class FIFO_QUEUE:
    _processes = []
    def insert(self, a_pcb):
        self._processes.append(a_pcb)
    
    def remove(self, a_pcb):
        del self._processes[a_pcb]
        
    def popNext(self):
        temp = self._processes[0]
        del self._processes[0]
        return temp

    def print(self):
        print(self._processes)

# PREMPTIVE_PRIORITY
class Priority_QUEUE (FIFO_QUEUE):
    def insert(self, a_pcb):
        count = 0
        if self._processes:
            for x in self._processes:
                if (x[1] < a_pcb[1]):
                    count += 1
        self._processes.insert(count,a_pcb)    
        
# CPU
class CPU (PCB_Holder):
    def __init__(self, new_pcb):
        super(CPU,self).__init__(new_pcb)
       
# MEMORY
class Memory:
    __ram = [] # List of tuples (list) (pid, start, size)
    def __init__(self, max_size = 8000000):
        start_tuple = [-1, 0, max_size]
        self.__ram.append(start_tuple)

    def __deleteNegTwos(self):
        count = -1
        for x in self.__ram[:]:
            count += 1
            if(x[0]==-2):
                del self.__ram[count]
            
    
    def __mergeFreeSpaces(self):
        idx = -1
        to_delete = []
        for x in range(0, len(self.__ram)):
            idx += 1
            if (self.__ram[idx][0] == -1):
                idy = idx+1
                size_accum = self.__ram[idx][2]
                for y in range(idy, len(self.__ram)):
                    if (self.__ram[idy][0] == -1):
                        size_accum += self.__ram[idy][2]
                        self.__ram[idy][0] = -2
                        to_delete.append(self.__ram[idy])
                    else:
                        break
                    idy += 1
                if (idy != idx+1):
                    self.__ram[idx][2] = size_accum
        for x in to_delete:
            #print(x)
            self.__ram.remove(x)

    def getWorstFitIndex(self, pcb_size):
        dest_index = -1
        i = -1
        max_avail = 0       
        for x in self.__ram:
            i += 1
            if (x[0] == -1):
                hole_size = x[2] - x[1]
                if (hole_size > pcb_size and hole_size > max_avail):
                    max_avail = hole_size
                    dest_index = i
        return dest_index

    def allocate(self, a_pid, pcb_size):
       dest_index = self.getWorstFitIndex(pcb_size)
       if (self.__ram[dest_index][0] != -1):
           print("Error. Dest not empty")
       new_start = self.__ram[dest_index][1]
       self.__ram[dest_index][1] += pcb_size
       self.__ram[dest_index][2] -= pcb_size
       self.__ram.insert(dest_index, [a_pid, new_start, pcb_size])

    def free(self, a_pid):
        pid_size = -1
        for x in self.__ram[:]:
            if (x[0] == a_pid):
                x[0] = -1
                break
        self.__mergeFreeSpaces()

    def print(self):
        print(self.__ram)

        
       
# DEVICE
class Device(PCB_Holder):
    def __init__(self, new_pcb):
        super(Device,self).__init__(new_pcb)

# PCB (just use pid priority tuple)
class PCB:
    __pid = -1
    __priority =-1
    
    def __init__(self, pid, priority):
        self.__pid = pid
        self.__priority = priority

    def getPID(self):
        return self.__pid
    
    def getPriority(self):
        return self.__priority
    
    
# SYSTEM
class OperatingSys:
    _cpu_ = CPU()
    _cpu_priority_queue = Priority_QUEUE()
    _mem
    _number_of_printers = 0
    _number_of_disks = 0
    _printers = []
    _printer_queues = []
    _disks = []
    _disk_queues = []

    def __init__(self, mem_size = 8000000, numb_printers, numb_disks):
        self._mem = Memory(mem_size)
        for x in range(0,numb_printers):
            self._number_of_printers = numb_printers
            self._printers.append(Device())
            self._printer_queues.append(FIO_QUEUE())
        for x in range(0,numb_disks):
            self._number_of_disks = numb_disks
            self._disks.append(Device())
            self._disk_queues.append(FIO_QUEUE())

# OS_FrontEnd
#class OS_FrontEnd:
#    def cmd_A:
#    def cmd_t:
#    def cmd_pX:
#    def cmd_PX:
#    def cmd_dX:
#    def cmd_DX:
#    def cmd_S:
    
#Testing
CPU_Priority = Priority_QUEUE()
CPU_Priority.insert((1,1))
CPU_Priority.insert((3,3))
CPU_Priority.insert((0,0))
CPU_Priority.insert((2,2))
CPU_Priority.print()

mem = Memory()
print("Start Allocation Tests")
mem.allocate(0, 100)
mem.allocate(1, 5000)
mem.allocate(2, 10000)
mem.allocate(3, 1)
mem.print()

print("Start Free Tests")
mem.free(2)
mem.print()
mem.free(1)
mem.print()
mem.free(3)

mem.print()




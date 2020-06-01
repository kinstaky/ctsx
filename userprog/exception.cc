// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#ifdef LAB4
int Hash(int vpn, int c) {
	return (vpn % 31 + c) % NumPhysPages;
}



#endif

#ifdef LAB6

struct ExecArg {
	int id;
	char name[32];
};

struct ForkArg{
	int address;
	AddrSpace *space;
};

void GetString(int addr, char *buffer) {
	char ch = 'a';
	int i = 0;
	while (ch != '\0') {
		while (!machine->ReadMem(addr+i, 1, (int*)&ch)) {
			machine->RaiseException(PageFaultException, addr+i);
		}
		//printf("%d %c\n", i, ch);
		buffer[i] = ch;
		i++;
	}
}


void ReadMem(char *buffer, int addr, int size) {
	char ch;
	for (int i = 0; i != size; ++i) {
		while (!machine->ReadMem(addr+i, 1, (int*)&ch)) {
			machine->RaiseException(PageFaultException, addr+i);
		}
		buffer[i] = ch;
	}
}

void WriteMem(char *buffer, int addr, int size) {
	for (int i = 0; i != size; ++i) {
		while (!machine->WriteMem(addr+i, 1, buffer[i])) {
			machine->RaiseException(PageFaultException, addr+i);
		}
	}
}

void StartNewProcess(ExecArg *args) {
//printf("start new process\n");
    AddrSpace *space;
    space = new AddrSpace(args->name);
    currentThread->space = space;
    currentThread->SpaceId = args->id;
    delete args;

    space->InitRegisters();		// set the initial register values
    space->RestoreState();		// load page table register

    machine->Run();			// jump to the user progam
    ASSERT(FALSE);			// machine->Run never returns;
}


void ForkProcess(ForkArg *args) {
	AddrSpace *space;
	space = new AddrSpace(*(args->space));
	currentThread->space = space;
	space->InitRegisters();
	space->RestoreState();

	// to run at in the specific function
	machine->WriteRegister(PCReg, args->address);
    machine->WriteRegister(NextPCReg, args->address+4);
    machine->WriteRegister(RetAddrReg, 4);

	//delete args;
	machine->Run();
	ASSERT(FALSE);
	return;
}


#endif


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
//printf("ExceptionHandler\n");

    if ((which == SyscallException) && (type == SC_Halt)) {
		DEBUG('a', "Shutdown, initiated by user program.\n");
   		interrupt->Halt();
   	}
#ifdef LAB4
   	else if (which == SyscallException) {
   		if (type == SC_Exit) {
printf("Exit code: %d\n", machine->registers[4]);
   			DEBUG('a', "Exit %d\n", machine->registers[4]);
#ifdef LAB6
//fileSystem->PrintID(machine->registers[4]);
   			for (int i = 0; i != MAXOPEN; ++i) {
   				if (currentThread->OpenTable[i].inUse == 1) {
   					fileSystem->Close(currentThread->OpenTable[i].file);
   				}
   			}
			fileSystem->Remove(currentThread->space->fileName);
			int id = currentThread->SpaceId;
			ASSERT(machine->SpaceTable[id].inUse == 1);
			if (machine->SpaceTable[id].wait) {
				machine->SpaceTable[id].wait->V();
			}

#endif
   			currentThread->Finish();
   			//interrupt->Halt();
#ifdef LAB6
   		} else if (type == SC_Create) {
   			char buffer[32];
   			GetString(machine->registers[4], (char*)buffer);
   			DEBUG('a', "Create file %s\n", buffer);
   			fileSystem->Create(buffer, 0);
//printf("Create file %s\n", buffer);

   		} else if (type == SC_Open) {
   			char buffer[32];
   			GetString(machine->registers[4], (char*)buffer);
   			DEBUG('a', "Open file %s\n", buffer);
   			int id = fileSystem->OpenID(buffer);
   			machine->registers[2] = id;

   		} else if (type == SC_Write) {
   			char *buffer = new char[machine->registers[5]];
   			ReadMem(buffer, machine->registers[4], machine->registers[5]);
//printf("Write file %d with %d bytes string:%s\n", machine->registers[6], machine->registers[5], buffer);
   			//DEBUG('a', "Write file from %p of %d bytes in file %d\n", machine->registers[4], machine->registers[5], machine->registers[6]);
   			fileSystem->WriteID(buffer, machine->registers[5], machine->registers[6]);
//fileSystem->PrintID(machine->registers[6]);
   			delete[] buffer;

   		} else if (type == SC_Read) {
   			char *buffer = new char[machine->registers[5]];
   			machine->registers[2] = fileSystem->ReadID(buffer, machine->registers[5], machine->registers[6]);
   			WriteMem(buffer, machine->registers[4], machine->registers[5]);
//printf("read file %d with %d bytes and get string:%s\n", machine->registers[6], machine->registers[5], buffer);
   			//DEBUG('a', "Read file from %p of %d bytes in file %d\n", machine->registers[4], machine->registers[5], machine->registers[6]);

   		} else if (type == SC_Close) {

   			DEBUG('a', "Close file %d\n", machine->registers[4]);
   			fileSystem->CloseID(machine->registers[4]);

   		} else if (type == SC_Exec) {

   			ExecArg *args = new ExecArg;
   			GetString(machine->registers[4], (char*)args->name);
   			for (int i = 0; i != MAXSPACE; ++i) {
   				if (machine->SpaceTable[i].inUse == 0) {
   					machine->SpaceTable[i].inUse = 1;
   					machine->SpaceTable[i].wait = NULL;
   					args->id = i;
   					break;
   				}
   			}
   			machine->registers[2] = args->id;
   			Thread *thread = new Thread("exec thread");
   			thread->Fork(StartNewProcess, (void*)args);
   			//currentThread->Yield();

   		} else if (type == SC_Join) {

   			int id = machine->registers[4];
   			machine->SpaceTable[id].wait = new Semaphore("user wait space", 0);
   			machine->SpaceTable[id].wait->P();
   			machine->SpaceTable[id].inUse = 0;
   			delete machine->SpaceTable[id].wait;

   		} else if (type == SC_Fork) {

   			ForkArg *args = new ForkArg;
   			args->address = machine->registers[4];
   			args->space = currentThread->space;

   			Thread *thread = new Thread("fork thread");
   			thread->Fork(ForkProcess, (void*)args);


   		} else if (type == SC_Yield) {

   			//printf("syscall yield\n");
   			currentThread->Yield();
#endif
   		}

   	}
    else if (which == PageFaultException) {
    	DEBUG('a', "PageFaultException\n");
    	machine->TlbReplace();
    	stats->numTLBMiss++;
    	//printf("PageFaultException: vpn = %d, addr = %x\n", (unsigned)(machine->registers[BadVAddrReg]/PageSize), (unsigned)machine->registers[BadVAddrReg]);
    }
#endif
    else {
		printf("Unexpected user mode exception %d %d\n", which, type);
		ASSERT(FALSE);
    }
}


#ifdef LAB4
void Machine::TlbReplace() {
	unsigned int vpn = (unsigned int)(registers[BadVAddrReg] / PageSize);
	unsigned int ppn = -1;
	DEBUG('a', "TLB replace vpn %d\n", vpn);

	TranslationEntry *tlbEntry = NULL;
	for (int i = 0; i != TLBSize; ++i) {
		if (!tlb[i].valid) {
			tlbEntry = &tlb[i];
			tlbScheduler->Insert(tlbEntry);
			break;			// TLB not full
		}
	}

	if (!tlbEntry) {			// TLB full, replace one
		tlbEntry = tlbScheduler->Remove();
		tlbEntry->valid = false;
		if (!ReversePageTable && tlbEntry->thread == currentThread) {	// backup: !reverse && valid
			ASSERT(pageTable[tlbEntry->virtualPage].valid);
			// set the flags
			if (tlbEntry->dirty) pageTableScheduler->Dirty(&pageTable[tlbEntry->virtualPage]);
			if (tlbEntry->use) pageTableScheduler->Use(&pageTable[tlbEntry->virtualPage]);
		}
	}

	if (ReversePageTable) {
		for (int i = 0; i != NumPhysPages; ++i) {
			int index = Hash(vpn, i);
			if (pageTable[index].valid && pageTable[index].thread == currentThread && pageTable[index].virtualPage == vpn) {
				ppn = pageTable[index].physicalPage;
				//pageTableScheduler->Use(&pageTable[index]);
				break;			// found the page frame
			}
		}
	}
	else {
		if (pageTable[vpn].valid) {
			ppn = pageTable[vpn].physicalPage;
			pageTableScheduler->Use(&pageTable[vpn]);	// Found the page frame in pagetable
		}
	}

	if (ppn == -1) {			// page frame fault, load from disk
		// set the flags first
		if (!ReversePageTable) {
			for (int i = 0; i != TLBSize; ++i) {
				if (tlb[i].valid) {
					ASSERT(pageTable[tlb[i].virtualPage].valid);
					if (tlb[i].dirty) pageTableScheduler->Dirty(&pageTable[tlb[i].virtualPage]);
					if (tlb[i].use) pageTableScheduler->Use(&pageTable[tlb[i].virtualPage]);
				}
			}
		}
		// repalce the page table
		PageTableReplace(vpn, &ppn);
	}

	tlbScheduler->Insert(tlbEntry);
	tlbEntry->valid = true;
	tlbEntry->dirty = false;
	tlbEntry->readOnly = false;
	tlbEntry->use = false;
	tlbEntry->virtualPage = vpn;
	tlbEntry->physicalPage = ppn;
	tlbEntry->thread = currentThread;

	DEBUG('a', "TLB replace after: vpn %d, ppn %d\n", vpn, ppn);

}

void Machine::PageTableReplace(int vpn, int *ppn) {
	DEBUG('a', "page replace vpn %d, ppn %d\n", vpn, *ppn);

	TranslationEntry *entry;

	if (!ReversePageTable) {
		if (memoryMap->NumClear() == 0) {			// no frame available
			entry = pageTableScheduler->Remove();
			*ppn = entry->physicalPage;

			for (int i = 0; i != TLBSize; ++i) {
				if (tlb[i].valid && tlb[i].virtualPage == entry->virtualPage) {
					tlbScheduler->Remove(&tlb[i]);
					if (tlb[i].dirty) entry->dirty = true;
				}
			}

			if (entry->dirty) {
#ifndef LAB6
				currentThread->space->DiskWrite(mainMemory+(entry->physicalPage)*PageSize, (entry->virtualPage)*PageSize, PageSize);
#else
				currentThread->space->FileWrite(mainMemory+(entry->physicalPage)*PageSize, PageSize, (entry->virtualPage)*PageSize);
#endif
			}
			entry->valid = false;

		}
		else {
			*ppn = memoryMap->Find();
		}
#ifndef LAB6
		currentThread->space->DiskRead(mainMemory+(*ppn)*PageSize, vpn*PageSize, PageSize);
#else
		currentThread->space->FileRead(mainMemory+(*ppn)*PageSize, PageSize, vpn*PageSize);
#endif
		pageTableScheduler->Insert(&pageTable[vpn]);
		pageTable[vpn].valid = true;
		pageTable[vpn].dirty = false;
		pageTable[vpn].readOnly = false;
		pageTable[vpn].use = false;
		pageTable[vpn].virtualPage = vpn;
		pageTable[vpn].physicalPage = *ppn;
		pageTable[vpn].thread = currentThread;
	}
	else {
		if (memoryMap->NumClear() == 0) {
			// replace the other thread's pages first
			for (int i = 0; i != NumPhysPages; ++i) {
				int index = Hash(vpn, i);
				if (pageTable[index].thread && pageTable[index].thread != currentThread) {
					if (pageTable[index].valid && pageTable[index].dirty) {
#ifndef LAB6
						((Thread*)(pageTable[index].thread))->space->DiskWrite(mainMemory+pageTable[index].physicalPage*PageSize, pageTable[index].virtualPage*PageSize, PageSize);
#else
						((Thread*)(pageTable[index].thread))->space->FileWrite(mainMemory+pageTable[index].physicalPage*PageSize, PageSize, pageTable[index].virtualPage*PageSize);
#endif
						pageTableScheduler->Remove(&pageTable[index]);
						pageTable[index].thread = NULL;
						pageTable[index].dirty = false;
					}
					*ppn = pageTable[index].physicalPage;
					break;
				}
			}

			// all pages are in current thread, replace
			if (*ppn == -1) {
				entry = pageTableScheduler->Remove();
				entry->valid = false;
				*ppn = entry->physicalPage;

				if (entry->dirty && entry->thread) {
#ifndef LAB6
					((Thread*)(entry->thread))->space->DiskWrite(mainMemory+entry->physicalPage*PageSize, entry->virtualPage*PageSize, PageSize);
#else
					((Thread*)(entry->thread))->space->FileWrite(mainMemory+entry->physicalPage*PageSize, PageSize, entry->virtualPage*PageSize);
#endif
				}

				// clear the TLB entry if the physical page was replaced
				for (int i = 0; i != TLBSize; ++i) {
					if (tlb[i].valid && tlb[i].physicalPage == *ppn) {
						tlbScheduler->Remove(&tlb[i]);
					}
				}
			}
		}
		else {
			// find an available page
			for (int i = 0; i != NumPhysPages; ++i) {
				int index = Hash(vpn, i);
				if (!memoryMap->Test(index)) {
					memoryMap->Mark(index);
					*ppn = index;
					break;
				}
			}
		}
		ASSERT(*ppn != -1);
#ifndef LAB6
		currentThread->space->DiskRead(mainMemory+(*ppn)*PageSize, vpn*PageSize, PageSize);
#else
		currentThread->space->FileRead(mainMemory+(*ppn)*PageSize, PageSize, vpn*PageSize);
#endif
		pageTableScheduler->Insert(&pageTable[*ppn]);
		pageTable[*ppn].valid = true;
		pageTable[*ppn].dirty = false;
		pageTable[*ppn].readOnly = false;
		pageTable[*ppn].use = false;
		pageTable[*ppn].physicalPage = *ppn;
		pageTable[*ppn].virtualPage = vpn;
		pageTable[*ppn].thread = currentThread;
	}
}


#endif
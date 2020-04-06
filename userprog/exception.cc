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

    if ((which == SyscallException) && (type == SC_Halt)) {
		DEBUG('a', "Shutdown, initiated by user program.\n");
   		interrupt->Halt();
   	}
#ifdef LAB4
   	else if (which == SyscallException) {
   		if (type == SC_Exit) {
   			printf("Exit code: %d\n", machine->registers[4]);
   			DEBUG('a', "Exit %d\n", machine->registers[4]);
   			currentThread->Finish();
   			//interrupt->Halt();
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
				currentThread->space->DiskWrite(mainMemory+(entry->physicalPage)*PageSize, (entry->virtualPage)*PageSize, PageSize);
			}
			entry->valid = false;

		}
		else {
			*ppn = memoryMap->Find();
		}
		pageTableScheduler->Insert(&pageTable[vpn]);
		currentThread->space->DiskRead(mainMemory+(*ppn)*PageSize, vpn*PageSize, PageSize);
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
						((Thread*)(pageTable[index].thread))->space->DiskWrite(mainMemory+pageTable[index].physicalPage*PageSize, pageTable[index].virtualPage*PageSize, PageSize);
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
					((Thread*)(entry->thread))->space->DiskWrite(mainMemory+entry->physicalPage*PageSize, entry->virtualPage*PageSize, PageSize);
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

		//printf("%s: %d\n", __FILE__, __LINE__);
		currentThread->space->DiskRead(mainMemory+(*ppn)*PageSize, vpn*PageSize, PageSize);
		//printf("%s: %d\n", __FILE__, __LINE__);

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
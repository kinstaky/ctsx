// progtest.cc 
//	Test routines for demonstrating that Nachos can load
//	a user program and execute it.  
//
//	Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "console.h"
#include "addrspace.h"
#include "synch.h"



//----------------------------------------------------------------------
// StartProcess
// 	Run a user program.  Open the executable, load it into
//	memory, and jump to it.
//----------------------------------------------------------------------

void
StartProcess(char *filename)
{
#ifdef LAB6
    AddrSpace *space;
    space = new AddrSpace(filename);
    currentThread->space = space;
    currentThread->SpaceId = 0;
    machine->SpaceTable[0].inUse = 1;
    //machine->SpaceTable[0].wait = new Semaphore("user wait space", 0);
#else
    OpenFile *executable = fileSystem->Open(filename);
    AddrSpace *space;

    if (executable == NULL) {
    printf("Unable to open file %s\n", filename);
    return;
    }
    space = new AddrSpace(executable);
    currentThread->space = space;
    delete executable;			// close file
#endif
    space->InitRegisters();		// set the initial register values
    space->RestoreState();		// load page table register

    machine->Run();			// jump to the user progam
    ASSERT(FALSE);			// machine->Run never returns;
					// the address space exits
					// by doing the syscall "exit"
}

#ifdef LAB4
//----------------------------------------------------------------------
// StartNProcess
// Run several process by creating several threads
// and fork StartProcess,default N = 2
//----------------------------------------------------------------------
void StartNProcess(char *filename, int count = 2) {
	for (int i = 0; i != count; ++i) {
		Thread *t1 = new Thread("user thread");
		t1->Fork(StartProcess, (void*)filename);
	}
	return;
}
#endif

// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.

static Console *console;
static Semaphore *readAvail;
static Semaphore *writeDone;

//----------------------------------------------------------------------
// ConsoleInterruptHandlers
// 	Wake up the thread that requested the I/O.
//----------------------------------------------------------------------

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

//----------------------------------------------------------------------
// ConsoleTest
// 	Test the console by echoing characters typed at the input onto
//	the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void 
ConsoleTest (char *in, char *out)
{
    char ch;
#ifdef LAB5
    SynchConsole *synConsole = new SynchConsole(in, out);
    for (;;) {
        ch = synConsole->GetChar();
        synConsole->PutChar(ch);
        if (ch == 'q') return;
    }

#else
    console = new Console(in, out, ReadAvail, WriteDone, 0);
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    
    for (;;) {
	readAvail->P();		// wait for character to arrive
	ch = console->GetChar();
	console->PutChar(ch);	// echo it!
	writeDone->P() ;        // wait for write to finish
	if (ch == 'q') return;  // if q, quit
    }
#endif
}

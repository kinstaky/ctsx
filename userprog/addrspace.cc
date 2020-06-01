// addrspace.cc 
//  Routines to manage address spaces (executing user programs).
//
//  In order to run a user program, you must:
//
//  1. link with the -N -T 0 option 
//  2. run coff2noff to convert the object file to Nachos format
//      (Nachos object code format is essentially just a simpler
//      version of the UNIX executable object code format)
//  3. load the NOFF file into the Nachos file system
//      (if you haven't implemented the file system yet, you
//      don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"
#ifdef HOST_SPARC
#include <strings.h>
#endif

//----------------------------------------------------------------------
// SwapHeader
//  Do little endian to big endian conversion on the bytes in the 
//  object file header, in case the file was generated on a little
//  endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
    noffH->noffMagic = WordToHost(noffH->noffMagic);
    noffH->code.size = WordToHost(noffH->code.size);
    noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
    noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
    noffH->initData.size = WordToHost(noffH->initData.size);
    noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
    noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
    noffH->uninitData.size = WordToHost(noffH->uninitData.size);
    noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
    noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

#ifndef LAB6
//----------------------------------------------------------------------
// VirtualDisk::VirtalDisk
// Simulate the disk, just allocate space from the memory
// should be repalced by the filesystem in the next lab
//
// "size" is the size(byte) of the virtual disk
//----------------------------------------------------------------------

VirtualDisk::VirtualDisk(unsigned int size) {
    diskSize = size;
    data = new char[size];
    bzero(data, size);
}

//----------------------------------------------------------------------
// VirtualDisk::~VirtualDisk
// delete the space
//----------------------------------------------------------------------

VirtualDisk::~VirtualDisk() {
    delete[] data;
}

//----------------------------------------------------------------------
// VirtualDisk::DiskMemory
// return the address of the disk memory
//
// "offset": the offset from the data
//----------------------------------------------------------------------

char* VirtualDisk::DiskMemory(int offset = 0) {
    ASSERT(offset >= 0);
    ASSERT(offset < diskSize);
    return data+offset;
}

//----------------------------------------------------------------------
// VirtualDisk::Write
// read from memory and write to the virtual disk
// return the actual size written(not finished)
//
// "memory": the address of source data
// "virtualAddr": the offset of the destination data
// "size": the size(byte) to write
//----------------------------------------------------------------------
int VirtualDisk::Write(char *memory, int virtualAddr, int size) {
    ASSERT(virtualAddr < diskSize);
    ASSERT(virtualAddr >= 0);

    int asize = virtualAddr + size - diskSize;
    if (asize > 0) asize = size - asize;
    else asize = size;
    for (int i = 0; i != asize; ++i) {
        data[virtualAddr+i] = memory[i];
    }
    //printf("write 0x%x, size %d\n", virtualAddr, asize);
    return asize;
}

//----------------------------------------------------------------------
// VirtualDisk::Read
// read from the virtual disk and write to the momory
// return the actual size read(not finished)
//
// "memory": the address of destination data
// "virtualAddr": the offset of the source data
// "size": the size(byte) to read
//----------------------------------------------------------------------
int VirtualDisk::Read(char *memory, int virtualAddr, int size) {
    if (virtualAddr >= diskSize) {
        printf("virtualAddr = 0x%x, diskSize = %x\n", virtualAddr, diskSize);
    }
    ASSERT(virtualAddr < diskSize);
    ASSERT(virtualAddr >= 0);

    int asize = virtualAddr + size - diskSize;
    if (asize > 0) asize = size - asize;
    else asize = size;
    for (int i = 0; i != asize; ++i) {
        memory[i] = data[virtualAddr+i];
    }
    //printf("read 0x%x, size %d\n", virtualAddr, asize);
    return asize;
}


//----------------------------------------------------------------------
// VirtualDisk::Printf
// print the whole memory of disk
//----------------------------------------------------------------------

void VirtualDisk::Print() {
    for (int i = 0; i != diskSize; ++i) {
        printf("%02x", (unsigned char)data[i]);
        if (i % 16 == 15) printf("\n");
        else if (i % 2 == 1) printf(" ");
    }
}
#endif


//----------------------------------------------------------------------
// AddrSpace::AddrSpace
//  Create an address space to run a user program.
//  Load the program from a file "executable", and set everything
//  up so that we can start executing user instructions.
//
//  Assumes that the object code file is in NOFF format.
//
//  First, set up the translation from program memory to physical 
//  memory.  For now, this is really simple (1:1), since we are
//  only uniprogramming, and we have a single unsegmented page table
//
//  "executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable)
{
    NoffHeader noffH;
    unsigned int i, size;

    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
        (WordToHost(noffH.noffMagic) == NOFFMAGIC))
        SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
            + UserStackSize;    // we need to increase the size
                        // to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;

#ifndef LAB4
    ASSERT(numPages <= NumPhysPages);       // check we're not trying
                        // to run anything too big --
                        // at least until we have
                        // virtual memory

#else
    if (!machine->ReversePageTable) {
        DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
                    numPages, size);
        // first, set up the translation 
#endif
        pageTable = new TranslationEntry[numPages];

        for (i = 0; i < numPages; i++) {
#ifdef LAB4
            pageTable[i].virtualPage = i;
            pageTable[i].physicalPage = -1;
            pageTable[i].thread = NULL;
            pageTable[i].valid = false;      // lazy loading, all not available
#else
            pageTable[i].virtualPage = i;   // for now, virtual page # = phys page #
            pageTable[i].physicalPage = i;
            pageTable[i].valid = TRUE;
#endif
            pageTable[i].use = FALSE;
            pageTable[i].dirty = FALSE;
            pageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
                            // a separate page, we could set its 
                            // pages to be read-only
        }
#ifdef LAB4
    }
#endif
#ifndef LAB4
// zero out the entire address space, to zero the unitialized data segment 
// and the stack segment
    bzero(machine->mainMemory, size);

// then, copy in the code and data segments into memory
    if (noffH.code.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
            noffH.code.virtualAddr, noffH.code.size);
        executable->ReadAt(&(machine->mainMemory[noffH.code.virtualAddr]),
            noffH.code.size, noffH.code.inFileAddr);
    }
    if (noffH.initData.size > 0) {
        DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
            noffH.initData.virtualAddr, noffH.initData.size);
        executable->ReadAt(&(machine->mainMemory[noffH.initData.virtualAddr]),
            noffH.initData.size, noffH.initData.inFileAddr);
    }
    if (noffH.code.size > 0) printf("noffH.code.inFileAddr 0x%x, noffH.code.size %x\n", noffH.code.inFileAddr, noffH.code.size);
    if (noffH.initData.size > 0) printf("noffH.initData.inFileAddr 0x%x, noffH.initData.size %x\n", noffH.initData.inFileAddr, noffH.initData.size);
    if (noffH.uninitData.size > 0) printf("noffH.uninitData.inFileAddr 0x%x, noffH.uninitData.size %x\n", noffH.uninitData.inFileAddr, noffH.uninitData.size);
#else
    // set the virtual disk and save the file into the disk
#ifndef LAB6
    disk = new VirtualDisk(size);
    if (noffH.code.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
            noffH.code.virtualAddr, noffH.code.size);
        executable->ReadAt(disk->DiskMemory(noffH.code.virtualAddr),
            noffH.code.size, noffH.code.inFileAddr);
    }
    if (noffH.initData.size > 0) {
        DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
            noffH.initData.virtualAddr, noffH.initData.size);
        executable->ReadAt(disk->DiskMemory(noffH.initData.virtualAddr),
            noffH.initData.size, noffH.initData.inFileAddr);
    }
#endif

    // if (noffH.code.size > 0) {
    //     printf("code segment va %d, size %d, inFileAddr %d\n", noffH.code.virtualAddr, noffH.code.size, noffH.code.inFileAddr);
    // }
    // if (noffH.initData.size > 0) {
    //     printf("init data va %d, size %d, inFileAddr %d\n", noffH.initData.virtualAddr, noffH.initData.size, noffH.initData.inFileAddr);
    // }
    //disk->Print();
#endif // LAB4
}

#ifdef LAB6
AddrSpace::AddrSpace(char *filename) {
    OpenFile *executable = fileSystem->Open(filename);
    NoffHeader noffH;
    unsigned int i, size;

    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
        (WordToHost(noffH.noffMagic) == NOFFMAGIC))
        SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
            + UserStackSize;    // we need to increase the size
                        // to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;


    if (!machine->ReversePageTable) {
        DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
                    numPages, size);
        // first, set up the translation 
        pageTable = new TranslationEntry[numPages];

        for (i = 0; i < numPages; i++) {
            pageTable[i].virtualPage = i;
            pageTable[i].physicalPage = -1;
            pageTable[i].thread = NULL;
            pageTable[i].valid = false;      // lazy loading, all not available
            pageTable[i].use = FALSE;
            pageTable[i].dirty = FALSE;
            pageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
                            // a separate page, we could set its 
                            // pages to be read-only
        }
    }

    fileName = new char[5+strlen(filename)];
    sprintf(fileName, "/tmp/.%s", filename+1);
printf("fileName %s\n", fileName);
    fileSystem->Create(fileName, size);
    file = fileSystem->Open(fileName);

    char buffer[PageSize];

    if (noffH.code.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
            noffH.code.virtualAddr, noffH.code.size);
        int codePages = divRoundDown(noffH.code.size, PageSize);
        for (int i = 0; i != codePages; ++i) {
            executable->ReadAt((char*)buffer, PageSize, noffH.code.inFileAddr+i*PageSize);
            file->WriteAt((char*)buffer, PageSize, noffH.code.virtualAddr+i*PageSize, 0);
        }
        executable->ReadAt((char*)buffer, noffH.code.size-codePages*PageSize, noffH.code.inFileAddr+codePages*PageSize);
        file->WriteAt((char*)buffer, noffH.code.size-codePages*PageSize, noffH.code.virtualAddr+codePages*PageSize, 0);
    }
    if (noffH.initData.size > 0) {
        DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
            noffH.initData.virtualAddr, noffH.initData.size);
        int dataPages = divRoundDown(noffH.initData.size, PageSize);
        for (int i = 0; i != dataPages; ++i) {
            executable->ReadAt((char*)buffer, PageSize, noffH.initData.inFileAddr+i*PageSize);
            file->WriteAt((char*)buffer, PageSize, noffH.initData.virtualAddr+i*PageSize, 0);
        }
        executable->ReadAt((char*)buffer, noffH.initData.size-dataPages*PageSize, noffH.initData.inFileAddr+dataPages*PageSize);
        file->WriteAt((char*)buffer, noffH.initData.size-dataPages*PageSize, noffH.initData.virtualAddr+dataPages*PageSize, 0);
    }
}


#endif

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
//  Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
    delete pageTable;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
//  Set the initial values for the user-level register set.
//
//  We write these directly into the "machine" registers, so
//  that we can immediately jump to user code.  Note that these
//  will be saved/restored into the currentThread->userRegisters
//  when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);   

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!

    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
//  On a context switch, save any machine state, specific
//  to this address space, that needs saving.
//
//  For now, nothing!
//----------------------------------------------------------------------

void AddrSpace::SaveState() {
#ifdef LAB4
    if (machine->ReversePageTable) {
        machine->ClearVirtualPages(false);
    }
    else {
        machine->ClearVirtualPages(true);
    }
#endif
}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
//  On a context switch, restore the machine state so that
//  this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
#ifdef LAB4
    if (!machine->ReversePageTable) {
        machine->pageTable = pageTable;
        machine->pageTableSize = numPages;
    }
    else {
        pageTable = machine->pageTable;
    }
#endif
}

#ifndef LAB6
#ifdef LAB4
//----------------------------------------------------------------------
// AddrSpace::DiskRead
// the public method of disk->Read
//----------------------------------------------------------------------

int AddrSpace::DiskRead(char *memory, int virtualAddr, int size) {
    return disk->Read(memory, virtualAddr, size);
}


//----------------------------------------------------------------------
// AddrSpace::DiskWrite
// the public method of disk->Write
//----------------------------------------------------------------------

int AddrSpace::DiskWrite(char *memory, int virtualAddr, int size) {
    return disk->Write(memory, virtualAddr, size);
}
#endif // LAB4
#else // LAB6
int AddrSpace::FileRead(char *from, int size, int virtualAddr) {
    return file->ReadAt(from, size, virtualAddr);
}

int AddrSpace::FileWrite(char *from, int size, int virtualAddr) {
    return file->WriteAt(from, size, virtualAddr, 0);
}

#endif
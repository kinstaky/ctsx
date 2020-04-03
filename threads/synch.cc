// synch.cc
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(char* debugName, int initialValue)
{
    name = debugName;
    value = initialValue;
    queue = new List;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts

    while (value == 0) { 			// semaphore not available
	queue->Append((void *)currentThread);	// so go to sleep
	currentThread->Sleep();
    }
    value--; 					// semaphore available,
						// consume its value

    (void) interrupt->SetLevel(oldLevel);	// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    thread = (Thread *)queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    (void) interrupt->SetLevel(oldLevel);
}


#ifdef LAB3
//----------------------------------------------------------------------
// Lock::Lock
// init the lock, set the name to debugName and the owner to NULL
// prepare the queue for sleeping thread
//
// "debugName" is an arbitrary name, useful for debugging.
//----------------------------------------------------------------------

Lock::Lock(char *debugName) {
    name = debugName;
    owner = NULL;
    queue = new List;
}


//----------------------------------------------------------------------
// Lock::~Lock
// delete waiting queue
//----------------------------------------------------------------------

Lock::~Lock() {
    delete queue;
}


//----------------------------------------------------------------------
// Lock::Acquire
// Diable the interrupt, change the owner if owner is NULL
// otherwise, sleep and wait in the queue, like the semaphore
//----------------------------------------------------------------------
void Lock::Acquire() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);   // disable interrupts

    while (owner != NULL && owner != currentThread) {            // lock hold by other thread
        queue->Append((void *)currentThread);   // so go to sleep
        currentThread->Sleep();
    }
    owner = currentThread;                    // lock available,
                        // current thread get the lock

    (void) interrupt->SetLevel(oldLevel);   // re-enable interrupts
    return;
}


//----------------------------------------------------------------------
// Lock::Release
// Diable the interrupt, set the owner to NULL
// If the waiting queue isn't empty, wake up the waiting thread.
//----------------------------------------------------------------------
void Lock::Release() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    Thread *thread = queue->Remove();

    if (thread != NULL) {
        scheduler->ReadyToRun(thread);
    }

    owner = NULL;                   // set the owner to NULL

    interrupt->SetLevel(oldLevel);

    return;
}

//----------------------------------------------------------------------
// Lock::isHeldByCurrentThread
// return whether the lock is held by current thread
// the caller should consider the interrupt and schedule
//----------------------------------------------------------------------
bool Lock::isHeldByCurrentThread() {
    return owner == currentThread;
}


//----------------------------------------------------------------------
// Condition::Condition
// construct the Condition, set the name and the init the waiting queue
//----------------------------------------------------------------------
Condition::Condition(char *dubugName) {
    name = dubugName;
    queue = new List;
}

//----------------------------------------------------------------------
// Condition::~Condition
// delete the waiting queue
//----------------------------------------------------------------------

Condition::~Condition() {
    delete queue;
}

//----------------------------------------------------------------------
// Condition::Wait
// put the thread into the waiting queue after disable the interrupt
// but check the lock before and release the lock before sleep
//----------------------------------------------------------------------

void Condition::Wait(Lock *conditionLock) {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    ASSERT(conditionLock->isHeldByCurrentThread());
                                            // current thread should hold the lock
    conditionLock->Release();
                                            // release the lock before sleep
    queue->Append(currentThread);           // append to the waiting queue
    currentThread->Sleep();                 // sleep

    conditionLock->Acquire();               // get the lock

    interrupt->SetLevel(oldLevel);
    return;
}

//----------------------------------------------------------------------
// Condition::Signal
// remove a thread in the queue after disable the interrupt
// but check the lock before and release the lock before return
//----------------------------------------------------------------------
void Condition::Signal(Lock *conditionLock) {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    ASSERT(conditionLock->isHeldByCurrentThread());

    Thread *thread = queue->Remove();
    if (thread != NULL) {
        scheduler->ReadyToRun(thread);
    }

    conditionLock->Release();

    interrupt->SetLevel(oldLevel);

    return;
}


//----------------------------------------------------------------------
// Condition::Broadcast
// remove all threads in the waiting queue after disable the interrupt
// but check the lock before and release the lock at last
//----------------------------------------------------------------------
void Condition::Broadcast(Lock *conditionLock) {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    ASSERT(conditionLock->isHeldByCurrentThread());

    Thread *thread;
    while (!(queue->IsEmpty())) {
        thread = queue->Remove();
        scheduler->ReadyToRun(thread);
    }

    conditionLock->Release();

    interrupt->SetLevel(oldLevel);

    return;
}

//----------------------------------------------------------------------
// ReadWriteLock::ReadWriteLock
// init the locks and name, number of readers
//----------------------------------------------------------------------

ReadWriteLock::ReadWriteLock(char *debugName) {
    name = debugName;
    readerNum = 0;
    mutex = new Lock("ReadWriteLock mutex");
    writeLock = new Lock("ReadWriteLock writeLock");
}


//----------------------------------------------------------------------
// ReadWriteLock::~ReadWriteLock
// delete the locks
//----------------------------------------------------------------------

ReadWriteLock::~ReadWriteLock() {
    delete mutex;
    delete writeLock;
}


//----------------------------------------------------------------------
// ReadWriteLock::ReadAcquire()
// get the writeLock to assure no writers, then increase the
// number of readers
//----------------------------------------------------------------------

void ReadWriteLock::ReadAcquire() {
    mutex->Acquire();
    if (readerNum == 0) writeLock->Acquire();
    readerNum++;
    mutex->Release();
    return;
}


//----------------------------------------------------------------------
// ReadWriteLock::ReadRelease()
// decrease the number of readers
//----------------------------------------------------------------------

void ReadWriteLock::ReadRelease() {
    mutex->Acquire();
    readerNum--;
    if (readerNum == 0) writeLock->Release();
    mutex->Release();
}


//----------------------------------------------------------------------
// ReadWriteLock::WriteAcquire()
// get the writeLock
//----------------------------------------------------------------------

void ReadWriteLock::WriteAcquire() {
    writeLock->Acquire();
}


//----------------------------------------------------------------------
// ReadWriteLock::WriteRelease()
// release the write lock
//----------------------------------------------------------------------

void ReadWriteLock::WriteRelease() {
    writeLock->Release();
}


#else
// Dummy functions -- so we can compile our later assignments
// Note -- without a correct implementation of Condition::Wait(),
// the test case in the network assignment won't work!
Lock::Lock(char* debugName) {}
Lock::~Lock() {}
void Lock::Acquire() {}
void Lock::Release() {}

Condition::Condition(char* debugName) { }
Condition::~Condition() { }
void Condition::Wait(Lock* conditionLock) { ASSERT(FALSE); }
void Condition::Signal(Lock* conditionLock) { }
void Condition::Broadcast(Lock* conditionLock) { }
#endif
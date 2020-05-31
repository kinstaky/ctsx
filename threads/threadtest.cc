// threadtest.cc
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield,
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "elevatortest.h"
#ifdef LAB2
#include "list.h"
#endif
#ifdef LAB3
#include "synch.h"
#endif

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;

    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1\n");
    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, (void*)1);
    SimpleThread(0);
}


#ifdef LAB1
//----------------------------------------------------------------------
// SimpleThread2
//  Loop 3 times, yielding the CPU to another ready thread
//  each iteration and call LivingThreadStatus
//----------------------------------------------------------------------

void SimpleThread2() {
    for (int i = 0; i != 3; ++i) {
        printf("*** thread %s\n", currentThread->getName());
        LivingThreadStatus();
        currentThread->Yield();
    }
    return;
}


//----------------------------------------------------------------------
// ThreadTest2
//  Set up a ping-pong between three threads, by forking 2 threads
//  to call SimpleThread2, and then calling SimpleThread2 ourselves.
//----------------------------------------------------------------------

void ThreadTest2() {
    DEBUG('t', "Entering TreadTest2\n");

    Thread *t1 = new Thread("forked thread 1", 1);
    t1->Fork(SimpleThread2, NULL);

    Thread *t2 = new Thread("forked thread 2", 1);
    t2->Fork(SimpleThread2, NULL);

    SimpleThread2();
    return;
}


//----------------------------------------------------------------------
// SimpleThread3
// Just sleep
//----------------------------------------------------------------------
void SimpleThread3() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);   // disable interrupts
    currentThread->Sleep();
    (void) interrupt->SetLevel(oldLevel);   // re-enable interrupts
    return;
}


//----------------------------------------------------------------------
// ThreadTest3
//  fork 130 threads to show the limit on total of threads
//----------------------------------------------------------------------

void ThreadTest3() {
    DEBUG('t', "Entering ThreadTest3\n");

    Thread* threads[130];
    int successThreads = 0;

    for (int i = 0; i != 130; ++i) {
        threads[i] = new Thread("forked thread", 1);
        int err = threads[i]->Fork(SimpleThread3, NULL);
        // count the successful forked
        successThreads = err ? successThreads : successThreads+1;
    }
    printf("success to fork %d threads\n", successThreads);

    return;
}
#endif

#ifdef LAB2

//----------------------------------------------------------------------
// SimpleThread4
// Sleep for specified ticks
//----------------------------------------------------------------------
void SimpleThread4(uint sleepTime) {
    for (int i = 0; i != 3; ++i) {
        printf("Thread \"%s\" will sleep %d ticks loop %d\n", currentThread->getName(), sleepTime, i);
        currentThread->Sleep(sleepTime);
    }
    return;
}


//----------------------------------------------------------------------
// ThreadTest4
// Fork a new thread with higher privilege, so it
// will occupy the CPU whenever it wake up. The main
// thread simulate being busy, but since nachos does
// not have the real hardware interrupt, we here
// call OneTick to advance the time and simulate being
// busy.
// It can be predicted that the context will switch
// at the time the new thread wake up, even though the
// main thread haven't yield the CPU.
//----------------------------------------------------------------------

void ThreadTest4() {
    Thread *t1 = new Thread("nice -20", 1, -20);
    t1->Fork(SimpleThread4, 300);
    for (int i = 0; i != 10; ++i) {
        printf("\"%s\" busy for %d ticks\n", currentThread->getName(), i*100);
                                            // in the system mode, ticks add 10 each time
        for (int j = 0; j != 10; ++j) interrupt->OneTick();
    }
    return;
}


//----------------------------------------------------------------------
// SimpleThread5
// Aiming to show the schedule order of the threads,
// fork another thread if name not null,
// otherwise just print the begin and end of this thread
//----------------------------------------------------------------------
void SimpleThread5(char *name) {
    printf("Thread %s begin\n", currentThread->getName());
    if (name) {
        Thread *t = new Thread(name, 1, 10);
        t->Fork(SimpleThread5, NULL);
    }
    printf("Thread %s end\n", currentThread->getName());
    return;
}


//----------------------------------------------------------------------
// ThreadTest5
// Fork 3 threads, one with nice value 19 and two with nice
// value 10, the nice value of main thread is default as 0.
//
// Since the scheduler base on the privilege and the higher
// privilege will occupy the CPU, so if a thread fork another
// thread with higher privilege, the new thread will be
// scheduled first and the new thread will show between the
// begin and end of the old thread, otherwise, the old thread
// will end before the new thread begin.
//----------------------------------------------------------------------

void ThreadTest5() {
    Thread *t1 = new Thread("nice 19", 1, 19);
    t1->Fork(SimpleThread5, "nice 10 A");
    SimpleThread5("nice 10 B");
    return;
}

#endif

#ifdef LAB3

//----------------------------------------------------------------------
// global variable for testing semaphore
//----------------------------------------------------------------------
int msgNum;
Semaphore *semaphoreMutex;
Semaphore *semaphoreEmtpy;
Semaphore *semaphoreFull;

//----------------------------------------------------------------------
// semaphoreConsumer
// consume messages until the buffer empty or get enough message
//
// the parameter cnt is the number of the message to consume
//----------------------------------------------------------------------

void semaphoreConsumer(int cnt) {
    while (cnt--) {
        semaphoreFull->P();             // get a full slock

        semaphoreMutex->P();             // get the permission to change

        msgNum--;
        semaphoreEmtpy->V();             // create a empty slock

        printf("%s consume 1 message, now total message %d\n", currentThread->getName(), msgNum);

        semaphoreMutex->V();
    }
    return;
}

//----------------------------------------------------------------------
// semaphoreProducer
// produce messages until the buffer full or produce enough message
//
// the parameter cnt is the number of the message to produce
//----------------------------------------------------------------------

void semaphoreProducer(int cnt) {
    while (cnt--) {
        semaphoreEmtpy->P();             // get a empty slock

        semaphoreMutex->P();

        msgNum++;
        semaphoreFull->V();

        printf("%s produce 1 message, now total message %d\n", currentThread->getName(), msgNum);

        semaphoreMutex->V();
    }
    return;
}

//----------------------------------------------------------------------
// ThreadTest6
// Test the producer and customer with semaphore method.
// Create 2 customer and 3 producer, and the capacity of
// the buffer is 2, so it's easy to get full and empty.
//----------------------------------------------------------------------

void ThreadTest6() {
    msgNum = 0;
    semaphoreMutex = new Semaphore("producer-consumer mutex sem", 1);
    semaphoreEmtpy = new Semaphore("producer-consumer empty sem", 2);               // capacity of buffer is 2
    semaphoreFull = new Semaphore("producer-consumer full sem", 0);

    Thread *consumerA = new Thread("consumer A");
    consumerA->Fork(semaphoreConsumer, 3);

    Thread *consumerB = new Thread("consumer B");
    consumerB->Fork(semaphoreConsumer, 4);

    Thread *producerA = new Thread("producer A");
    producerA->Fork(semaphoreProducer, 1);

    Thread *producerB = new Thread("producer B");
    producerB->Fork(semaphoreProducer, 4);

    Thread *producerC = new Thread("producer C");
    producerC->Fork(semaphoreProducer, 2);

    return;
}

//----------------------------------------------------------------------
// global variable for testing condition
//----------------------------------------------------------------------

Lock *conditionLock;                // lock of condition
int msgCapacity;                    // capacity of the message buffer
Condition *conditionEmpty;          // the buffer is empty
Condition *conditionFull;           // the buffer is full

//----------------------------------------------------------------------
// semaphoreConsumer
// consume messages until the buffer empty or get enough message
//
// the parameter cnt is the number of the message to consume
//----------------------------------------------------------------------

void conditionConsumer(int cnt) {
    while (cnt--) {
        conditionLock->Acquire();

        while (msgNum == 0) {
            conditionEmpty->Wait(conditionLock);            // sleep if empty
        }
        msgNum--;
        conditionFull->Broadcast(conditionLock);        // wake all waiting producer, for testing Broadcast method

        printf("%s consume 1 message, now total message %d\n", currentThread->getName(), msgNum);

        conditionLock->Release();
    }
    return;
}


//----------------------------------------------------------------------
// conditionProducer
// produce messages until the buffer full or produce enough message
//
// the parameter cnt is the number of the message to produce
//----------------------------------------------------------------------

void conditionProducer(int cnt) {
    while (cnt--) {
        conditionLock->Acquire();

        while (msgNum == msgCapacity) {
            conditionFull->Wait(conditionLock);     // sleep if full
        }
        msgNum++;
        conditionEmpty->Signal(conditionLock);   // wake up one consumer, for testing Signal method

        printf("%s produce 1 message, now total message %d\n", currentThread->getName(), msgNum);


        conditionLock->Release();
    }
}


//----------------------------------------------------------------------
// ThreadTest7
// Test the producer and customer with condition method.
// Create 2 customer and 3 producer, and the capacity of
// the buffer is 2, so it's easy to get full and empty.
//----------------------------------------------------------------------

void ThreadTest7() {
    msgNum = 0;
    msgCapacity = 2;
    conditionLock = new Lock("producer-consumer condition lock");
    conditionEmpty = new Condition("msg buffer empty condition");
    conditionFull = new Condition("msg buffer full condition");

    Thread *consumerA = new Thread("consumer A");
    consumerA->Fork(conditionConsumer, 3);

    Thread *consumerB = new Thread("consumer B");
    consumerB->Fork(conditionConsumer, 4);

    Thread *producerA = new Thread("producer A");
    producerA->Fork(conditionProducer, 1);

    Thread *producerB = new Thread("producer B");
    producerB->Fork(conditionProducer, 4);

    Thread *producerC = new Thread("producer C");
    producerC->Fork(conditionProducer, 2);
    return;
}

//----------------------------------------------------------------------
// global variable for testing ReadWriteLock
//----------------------------------------------------------------------
ReadWriteLock *rwlock;      // lock
int readWriteValue;         // value to read or write

//----------------------------------------------------------------------
// reader
// hold the readerlock and read the value for specified times
//
// the parameter cnt is the specified time
//----------------------------------------------------------------------

void reader(int cnt) {
    rwlock->ReadAcquire();
    while (cnt--) {
        printf("%s read value %d\n", currentThread->getName(), readWriteValue);
        currentThread->Yield();
    }
    rwlock->ReadRelease();
}

//----------------------------------------------------------------------
// writer
// hold the writerlock and write the value for specified times
//
// parameter cnt is the specified time
//----------------------------------------------------------------------

void writer(int cnt) {
    rwlock->WriteAcquire();
    while (cnt--) {
        readWriteValue++;
        printf("%s write value as %d\n", currentThread->getName(), readWriteValue);
        currentThread->Yield();
    }
    rwlock->WriteRelease();
}


//----------------------------------------------------------------------
// ThreadTest8
// Test the reader-writer lock
//----------------------------------------------------------------------

void ThreadTest8() {
    rwlock = new ReadWriteLock("read write lock");

    Thread *writerA = new Thread("writer A");
    writerA->Fork(writer, 3);

    Thread *readerA = new Thread("reader A");
    readerA->Fork(reader, 3);

    Thread *readerB = new Thread("reader B");
    readerB->Fork(reader, 3);

    Thread *writerB = new Thread("writer B");
    writerB->Fork(writer, 3);

    return;
}

#endif

//----------------------------------------------------------------------
// ThreadTest
//  Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
    ThreadTest1();
    break;
#ifdef LAB1
    case 2:
    ThreadTest2();
    break;
    case 3:
    ThreadTest3();
    break;
#endif
#ifdef LAB2
    case 4:
    ThreadTest4();
    break;
    case 5:
    ThreadTest5();
    break;
#endif
#ifdef LAB3
    case 6:
    ThreadTest6();
    break;
    case 7:
    ThreadTest7();
    break;
    case 8:
    ThreadTest8();
    break;
#endif
    default:
    printf("No test specified.\n");
    break;
    }
}
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
    for (int i = 0; i != 5; ++i) {
        printf("Thread \"%s\" will sleep %d ticks loop %d\n", currentThread->getName(), sleepTime, i);
        currentThread->Sleep(sleepTime);
    }
    return;
}


//----------------------------------------------------------------------
// ThreadTest4
//  
//----------------------------------------------------------------------


void ThreadTest4() {
    Thread *t1 = new Thread("nice -20", 1, -20);
    //Thread *t2 = new Thread("nice 10", 1, -20);
    t1->Fork(SimpleThread4, 40);
    //t2->Fork(SimpleThread, (void*)(t2->GetNice()));
    SimpleThread4(10);
    return;
}


//----------------------------------------------------------------------
// SimpleThread5
// 
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
//  
//----------------------------------------------------------------------


void ThreadTest5() {
    Thread *t1 = new Thread("nice 19", 1, 19);
    t1->Fork(SimpleThread5, "nice 10 A");
    SimpleThread5("nice 10 B");
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
    default:
    printf("No test specified.\n");
    break;
    }
}
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
void SimpleThread2() {
    for (int i = 0; i != 3; ++i) {
        printf("*** thread %s\n", currentThread->getName());
        LivingThreadStatus();
        currentThread->Yield();
    }
    return;
}



void ThreadTest2() {
    DEBUG('t', "Entering TreadTest2\n");

    Thread *t1 = new Thread("forked thread 1", 1);
    t1->Fork(SimpleThread2, NULL);

    Thread *t2 = new Thread("forked thread 2", 1);
    t2->Fork(SimpleThread2, NULL);

    SimpleThread2();
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
#endif
    default:
    printf("No test specified.\n");
    break;
    }
}
#include "Thread.h"
#include "PCB.h"
#include <iostream.h>
#include <dos.h>


extern volatile int zahtevanaPromenaKonteksta;
extern void timer();

//Create thread
Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(this,stackSize,timeSlice);
}

//Destroy thread
Thread::~Thread(){
	if(myPCB!=0)
		delete myPCB;
	myPCB=0;
}

//Start thread
void Thread::start(){
	myPCB->start();
}

//Get this->ID
ID Thread::getId(){
	int ret;
	ret=myPCB->getId();
	return ret;
}

//Get ID from running thread
ID Thread::getRunningId(){
	int ret;
	ret=PCB::getRunningId();
	return ret;
}

//Get thread by ID
Thread* Thread::getThreadById(ID id){
	Thread* thread;
	thread=PCB::getThreadById(id);
	return thread;
}

//Wait for other threads
void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

/****************SIGNALS****************/
void Thread::signal(SignalId signal){
	myPCB->signal(signal);
}

void Thread::registerHandler(SignalId signal,SignalHandler handler){
	//cout<<"lalala"<<getId()<<endl;
	myPCB->registerHandler(signal,handler);
}

void Thread::unregisterAllHandlers(SignalId id){
	myPCB->unregisterAllHandlers(id);
}

void Thread::blockSignal(SignalId signal){
	myPCB->blockSignal(signal);
}

void Thread::blockSignalGlobally(SignalId signal){
	PCB::blockSignalGlobally(signal);
}

void Thread::unblockSignal(SignalId signal){
	myPCB->unblockSignal(signal);
}

void Thread::unblockSignalGlobally(SignalId signal){
	PCB::unblockSignalGlobally(signal);
}

void Thread::swap(SignalId id,SignalHandler hand1, SignalHandler hand2){
	myPCB->swap(id,hand1,hand2);
}

void dispatch(){
	asm cli
	zahtevanaPromenaKonteksta=1;
	asm int 08h
	asm sti
}

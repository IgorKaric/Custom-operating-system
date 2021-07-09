#include <dos.h>
#include "KernSem.h"
#include "PCB.h"
#include "semaphor.h"
#include "Thread.h"

extern volatile int zahtevanaPromenaKonteksta;

//Create semaphore
Semaphore::Semaphore(int init){
	myImpl=new KernelSem(this, init);
}

//Destroy semaphore
Semaphore::~Semaphore(){
	myImpl->semafor=0;
	delete myImpl;
	myImpl=0;
}

//Return semaphor's value
int Semaphore::val()const{
	int ret;
	ret=myImpl->val();
	return ret;
}

//Signal semaphore
int Semaphore::signal(int n){
	int ret;
	ret=myImpl->signal(n);
	return ret;
}

//Wait semaphore
int Semaphore::wait(Time maxTimeToWait){
	int ret;
	ret=myImpl->wait(maxTimeToWait);
	return ret;
}



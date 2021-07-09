#include <dos.h>
#include "Event.h"
#include "PCB.h"
#include "IVTEntry.h"
#include "KernelEv.h"
#include "Thread.h"

extern volatile int zahtevanaPromenaKonteksta;

//Napravi Event
Event::Event(IVTNo ivtNo){
	myImpl=new KernelEv(ivtNo,this);
}

//Unisti Event
Event::~Event(){
	if(myImpl!=0)
		delete myImpl;
	myImpl=0;
}

//Signal
void Event::signal(){
	myImpl->signal();
}

//wait
void Event::wait(){
	myImpl->wait();
}

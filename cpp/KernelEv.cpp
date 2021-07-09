#include <dos.h>
#include "KernelEv.h"
#include "PCB.h"
#include "Thread.h"
#include "SCHEDULE.H"
#include "Event.h"
#include "IVTEntry.h"

//Napravi KernelEv
KernelEv::KernelEv(IVTNo iv,Event* event){
	valEv=0;
	nit=PCB::running;
	ivtNo=iv;
	blokiranaNit=0;
	IVTEntry::ivtTabela[iv]->postaviEvent(this);
	mojEvent=event;
}

//Unisti KernelEv
KernelEv::~KernelEv(){
	mojEvent->signal();
	mojEvent=0;
	nit=0;
	blokiranaNit=0;
	IVTEntry::ivtTabela[ivtNo]=0;
}

//Signal
void KernelEv::signal(){
	if(blokiranaNit!=0){
		blokiranaNit->status=Spreman;
		Scheduler::put(blokiranaNit);
		blokiranaNit=0;
		dispatch();
	}else
		valEv=1;
}

//wait
void KernelEv::wait(){
	if(nit==PCB::running){
		if(valEv==1)
			valEv=0;
		else{
			blokiranaNit=PCB::running;
			blokiranaNit->status=Blokiran;
			dispatch();
		}
	}else
		return;

}

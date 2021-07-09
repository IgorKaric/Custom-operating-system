#include "KernSem.h"
#include <dos.h>
#include "listaPCB.h"
#include "listaSem.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include <iostream.h>
#include "listKern.h"


listKernel* KernelSem::listaSemafora=new listKernel();

int KernelSem::idnext=0;

//Napravi KernelSem
KernelSem::KernelSem(Semaphore* s, int init){
	valSem=init;
	semafor=s;
	blokiraneNiti=new listaPCB();
	TimerSemafori=new listaSem();
	id=KernelSem::idnext++;
	listaSemafora->stavi(this);
}

//Unisti KernelSem
KernelSem::~KernelSem(){
	valSem=0;
	listaSemafora->izbaci(this);
	if(blokiraneNiti!=0)
		delete blokiraneNiti;
	blokiraneNiti=0;
	if(TimerSemafori!=0)
		delete TimerSemafori;
	TimerSemafori=0;
}

//Wait
int KernelSem::wait(unsigned int maxTimeToWait){
	valSem--;
	if(valSem<0){
		if(maxTimeToWait==0){
			PCB::running->status=Blokiran;
			blokiraneNiti->stavi(PCB::running);
			dispatch();
		}
		else{
			PCB::running->status=Blokiran;
			TimerSemafori->stavi(PCB::running,maxTimeToWait,this);
			dispatch();
		}
	}
	if(PCB::running->fleg==1)
		return 1;
	return 0;

}

//Ispis timer semafora
void KernelSem::ispisi(){
	TimerSemafori->ispisi();
}

//signal
int KernelSem::signal(int n){
	if(n<0){
		return n;
	}
	if(n==0){
		valSem++;
		if(valSem<=0){
			PCB* pom=blokiraneNiti->uzmi();
			if(pom==0){
				return 0;
			}
			pom->status=Spreman;
			pom->fleg=1;
			Scheduler::put(pom);
		}
		return 0;
	}
	else{
		int br=n;
		while(br>0 && valSem<0){
			valSem++;
			PCB* pom=blokiraneNiti->uzmi();
			if(pom==0)
				break;
			pom->status=Spreman;
			pom->fleg=1;
			Scheduler::put(pom);
			br--;
		}
		while(br>0 && valSem<0){
			valSem++;
			PCB* pom2=TimerSemafori->uzmi();
			if(pom2==0)
				break;
			pom2->status=Spreman;
			pom2->fleg=1;
			Scheduler::put(pom2);
			br--;
		}
		int vr=n-br;
		return vr;
	}
}

//Vrati vrednost semafora
int KernelSem::val()const{
	return valSem;
}

//Signaliziraj timer liste za sve semafore
void KernelSem::signalizirajSve(){
	KernelSem::listaSemafora->signaliziraj();
}


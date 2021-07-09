#include <dos.h>
#include "PCB.h"
#include "IVTEntry.h"
#include "KernelEv.h"
#include "Thread.h"

IVTEntry* IVTEntry::ivtTabela[256]={0};//Inicijalizuj celu tabelu

extern volatile int zahtevanaPromenaKonteksta;

//Napravi IVTEntry
IVTEntry::IVTEntry(IVTNo br,pInterrupt novaRutina){
	ivtNo=br;
	myKernelEv=0;
	IVTEntry::ivtTabela[br]=this;
#ifndef BCC_BLOCK_IGNORE
	staraRutina=getvect(br);
	setvect(br,novaRutina);
#endif
}

//Unisti IVTEntry
IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo,staraRutina);
#endif
	ivtNo=0;
	IVTEntry::ivtTabela[ivtNo]=0;
	//pozoviStaru();
}

//Signal
void IVTEntry::signal(){
	if(myKernelEv){
		myKernelEv->signal();
	}
}

//Pozovi staru funkciju
void IVTEntry::pozoviStaru(){
	staraRutina();
}

//Postavi event
void IVTEntry::postaviEvent(KernelEv* ke){
	myKernelEv=ke;
}

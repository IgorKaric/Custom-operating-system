#include "listaPCB.h"
#include <iostream.h>
#include "PCB.h"
#include "SCHEDULE.H"

//Napravi listu
listaPCB::listaPCB(){
	prvi=0;
	poslednji=0;
	brojElem=0;
}

//Obrisi listu
listaPCB::~listaPCB(){
	while(prvi){
		Elem* pom=prvi;
		prvi=prvi->sledeci;
		pom->pcb->status=Spreman;
		Scheduler::put(pom->pcb);
		//delete pom;
	}
	brojElem=0;
	prvi=poslednji=0;
}

//Provera da li je lista prazna
int listaPCB::isEmpty(){
	if(brojElem==0)
		return 1;
	else
		return 0;
}

//Dodavanje u listu
void listaPCB::stavi(PCB* pcbb){
	Elem* pom=new Elem(pcbb);
	/*if(prvi==0){
		prvi=pom;
		poslednji=pom;
	}else{
		poslednji->sledeci=pom;
		poslednji=pom;
	}*/
	poslednji=(prvi==0)?prvi:poslednji->sledeci=pom;
	brojElem++;
}

//Uzmi PCB iz liste
PCB* listaPCB::uzmi(){
	if(isEmpty())
		return 0;
	Elem* pom=prvi;
	prvi=prvi->sledeci;
	brojElem--;
	if(prvi==0){
		poslednji=0;
		prvi=0;
	}
	PCB* pcbb=pom->pcb;
	return pcbb;
}

//Izbaci PCB iz liste svih (po ID-u)
PCB* listaPCB::izbaciIzSvih(int id){
	if(isEmpty())
		return 0;
	Elem* pom=prvi;
	Elem* tmp=pom;
	while(pom!=0 && pom->pcb->id!=id){
		tmp=pom;
		pom=pom->sledeci;
	}
	if(pom==0){
		cout<<"Nit nije u listi svih"<<endl;
		return 0;
	}
	tmp->sledeci=pom->sledeci;
	PCB* rez=pom->pcb;
	pom->sledeci=0;
	brojElem--;
	return rez;
}

//Uzmi nit iz liste svih po ID-u
Thread* listaPCB::uzmiNit(int id){
	if(isEmpty())
		return 0;
	Elem* pom=prvi;
	while(pom!=0 && pom->pcb->id!=id){
		pom=pom->sledeci;
	}
	if(pom==0){
		cout<<"Nit nije u listi svih"<<endl;
		return 0;
	}
	return pom->pcb->thread;
}

/************SIGNALI****************/
void listaPCB::blokirajSve(SignalId id){
	Elem* curr=prvi;
	while(curr!=0){
		curr->pcb->blockSignal(id);
		curr=curr->sledeci;
	}
}

void listaPCB::deblokirajSve(SignalId id){
	Elem* curr=prvi;
	while(curr!=0){
		curr->pcb->unblockSignal(id);
		curr=curr->sledeci;
	}
}


#include "listaSem.h"
#include <dos.h>
#include "PCB.h"
#include "KernSem.h"
#include <iostream.h>

//Napravi listu
listaSem::listaSem(){
	prvi=0;
	poslednji=0;
	brojElem=0;
}

//Ispitivanje da li je lista prazna
int listaSem::isEmpty(){
	if(prvi!=0)
		return 0;
	return 1;
}

//Obrisi listu
listaSem::~listaSem(){
	while(!isEmpty()){
		elem* pom=prvi;
		prvi=prvi->sledeci;
		pom->pcb->status=Spreman;
		Scheduler::put(pom->pcb);
		//delete pom;
	}
	brojElem=0;
	prvi=poslednji=0;
}



//Dodavanje u timer listu
void listaSem::stavi(PCB* pcbb,int time,KernelSem* ks){
	elem* pom=new elem(pcbb,time,ks);
	brojElem++;
	if(prvi!=0){
		elem* p;
		elem* q;
		int tmp;
		p=prvi;
		q=0;
		tmp=time;
		while(p!=0 && p->time<=tmp){
			q=p;
			tmp=tmp-p->time;
			p=p->sledeci;
		}
		if(p==0){//poslednji
			q->sledeci=pom;
			pom->time=tmp;
			pom->sledeci=0;
			poslednji=pom;
			return;
		}
		if(prvi==p && p!=0){//prvi
			pom->sledeci=prvi;
			prvi=pom;
			p->time=p->time-tmp;
			return;
		}
		else{//sredina
			pom->sledeci=p;
			q->sledeci=pom;
			pom->time=tmp;
			p->time=p->time-pom->time;
			return;
		}
	}else{
		prvi=poslednji=pom;
		return;
	}
}


//Ispis liste
void listaSem::ispisi(){
	elem* pom=prvi;
	while(pom!=0){
		cout<<pom->time<<" ";
		pom=pom->sledeci;
	}
	cout<<endl;
}

//Odblokiraj PCB iz liste
PCB* listaSem::uzmi(){
	if(prvi==0)
		return 0;
	elem* pom=prvi;
	prvi=prvi->sledeci;
	brojElem--;
	if(prvi!=0){
		prvi->time+=pom->time;
	}else{
		poslednji=0;
	}
	return pom->pcb;

}

//Signaliziraj
void listaSem::signaliziraj(){
	if(prvi!=0){
		elem* pom=prvi;
		prvi=prvi->sledeci;
		pom->time--;
		if(pom->time!=0){
			prvi=pom;
			return;
		}
		prvi=pom;
		while(prvi!=0 && prvi->time==0){
			PCB* pcb=prvi->pcb;
			KernelSem* ks=prvi->mySem;
			ks->valSem++;
			pcb->status=Spreman;
			pcb->fleg=2;
			Scheduler::put(pcb);
			elem* cur=prvi;
			prvi=prvi->sledeci;
			delete cur;
		}
	}
}

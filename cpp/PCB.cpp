#include "PCB.h"
#include <dos.h>
#include <iostream.h>

listaPCB* PCB::sveNiti=new listaPCB();//Globalna lista  niti
PCB* PCB::running=new PCB(0, 4096,2);
Idle* PCB::myIdle=new Idle();
int PCB::pcbId=0;
extern volatile int lockFlag;

//Create PCB
PCB::PCB(Thread* thread,unsigned long stacksize,unsigned int timeSlice){
	this->thread=thread;
	stacksize/=sizeof(unsigned);
	this->stacksize=stacksize;
	this->timeSlice=timeSlice;
	this->oldTimeSlice=timeSlice;
	id=pcbId++;
	if(id==0)//Main nit nema oca
		parent=0;
	else
		parent=PCB::running;
	fleg=0;
	lockFlag=1;
	sviSignali=new listaSignala();
	//cout<<"TREBA DA BUDE NULL"<<sviSignali->prvi;
	registrovaniSignali=new listaSignala();//Prazna na pocetku
	//pravljenje 16 signala
	if(id==0){
		for(int i=0;i<16;i++){
			sviSignali->dodaj(i);
		}
		sviSignali->dodajHandler(0,oslobodiNit);
	}
	//preuzeti sve od roditelja
	if(parent!=0){
		sviSignali->prekopiraj(parent->sviSignali);
	}


	this->stack=new unsigned[stacksize];
#ifndef BCC_BLOCK_IGNORE
	stack[stacksize - 1] = 0x200;
	stack[stacksize - 2] = FP_SEG(PCB::wrapper);
	stack[stacksize - 3] = FP_OFF(PCB::wrapper);
	ss = FP_SEG(stack + stacksize - 12);
	sp = FP_OFF(stack + stacksize - 12);
#endif
	bp = sp;
	listaCekanja=new listaPCB();
	if(this->id!=0)
		this->status=Nov;
	else{//Za main nit
		this->status=Spreman;
	}
	sveNiti->stavi(this);
}

//Destroy PCB
PCB::~PCB(){
	if(stack!=0){
		delete stack;
		stack=0;
	}
	thread=0;
	delete listaCekanja;
}

//Get this->ID
int PCB::getId(){
	return id;
}

//Get running ID
int PCB::getRunningId(){
	return PCB::running->id;
}

//Get Thread by ID
Thread* PCB::getThreadById(ID id){
	Thread* pom=sveNiti->uzmiNit(id);
	return pom;
}

//Funkcija za zavrsetak i obradu niti
void PCB::wrapper(){
	running->thread->run();
	//cout<<"Nit je zavrsila  "<<running->getId()<<endl;
	running->status=Zavrsen;
	if(running->parent!=0)
		running->parent->signal(1);//Po uslovu zadatka
	running->signal(2);//Po uslovu zadatka
	//running->signalizirajSveNiti();//Po uslovu zadatka 			DA LI OVO TREBA?
	PCB* pom;
	while(pom=running->listaCekanja->uzmi()){
		pom->status=Spreman;
	 	Scheduler::put(pom);
	}
	//cout<<PCB::running->getId();
	dispatch();
}

//Start PCB
void PCB::start(){
	if(status==Nov){
		status=Spreman;
		Scheduler::put(this);
	}
}

//Wait for others
void PCB::waitToComplete(){
//	if(running->getId()==1)
//		return;
	if(status!=Nov && status!=Zavrsen && PCB::running!=this){
		PCB::running->status=Blokiran;
		listaCekanja->stavi(running);
		dispatch();
	}
}

/**************SIGNALI***************/
void PCB::signal(SignalId signal){
	//cout<<"signal broj: "<<signal<<endl;
	//if(signal!=1 && signal!=2)
		registrovaniSignali->dodaj(signal);
		//cout<<getId()<<"  ";
		//registrovaniSignali->ispisi();
}

void PCB::registerHandler(SignalId signal,SignalHandler handler){
	//cout<<"dodat hendler"<<endl;
	sviSignali->dodajHandler(signal,handler);
	//if(getId()==0)
		//cout<<"main nit registerHandler"<<"svi signali"<<sviSignali;
}

void PCB::unregisterAllHandlers(SignalId id){
	sviSignali->obrisiSveHendlere(id);
}

void PCB::blockSignal(SignalId signal){
	sviSignali->blokirajSignal(signal);
}

void PCB::blockSignalGlobally(SignalId signal){
	PCB::sveNiti->blokirajSve(signal);
}

void PCB::unblockSignal(SignalId signal){
	sviSignali->deblokirajSignal(signal);
}

void PCB::unblockSignalGlobally(SignalId signal){
	PCB::sveNiti->deblokirajSve(signal);
}

void oslobodiNit(){
	//cout<<endl<<PCB::running->getId()<<"NIT"<<endl;
	//if(PCB::running->parent!=0)
		//PCB::running->parent->signal(1);
	//PCB::running->signal(2);
//	PCB::running->signalizirajSveNiti();
	PCB* pom;
	while(pom=PCB::running->listaCekanja->uzmi()){
		pom->status=Spreman;
		Scheduler::put(pom);
	}
	//delete PCB::running->listaCekanja;
	//delete PCB::running->sviSignali;
	//delete PCB::running->registrovaniSignali;
	PCB::running->status=Zavrsen;
	dispatch();
}

void PCB::swap(SignalId id,SignalHandler hand1, SignalHandler hand2){
	sviSignali->zameni(id,hand1,hand2);
}

void PCB::signalizirajSveNiti(){
//	if(PCB::running->getId()==2)
//		return;
	sviSignali->signaliziraj(registrovaniSignali);
}
/**************************************************/

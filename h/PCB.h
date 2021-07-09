#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"
#include "listaPCB.h"
#include "Idle.h"
#include "listaSig.h"

class Thread;


typedef void (*SignalHandler)();
typedef unsigned SignalId;

enum Status{Blokiran,Nov,Spreman,Zavrsen};

class PCB{
public:
	PCB(Thread* thread,unsigned long stacksize, unsigned int timeSlice);
	~PCB();


	void start();
	void waitToComplete();

	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);

	static void wrapper();

	unsigned long stacksize;
	unsigned int timeSlice;
	unsigned int oldTimeSlice;
	int id;
	int fleg;
	int lockFlag;
	static int pcbId;
	Thread* thread;
	unsigned* stack;
	unsigned bp,sp,ss;
	listaPCB* listaCekanja;
	static listaPCB* sveNiti;
	Status status;
	PCB* parent;
	static PCB* running;
	static Idle* myIdle;

	listaSignala* sviSignali;
	listaSignala* registrovaniSignali;



	/**************SIGNALI*******************/
	void signal(SignalId signal);//dodati signal u registrovane

	void registerHandler(SignalId signal, SignalHandler handler);//za taj signal dodati hendler u listu hendlera
	void unregisterAllHandlers(SignalId id);//sve hendlere izbaciti iz datog signala
	void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);//zameniti dva hendlera

	void blockSignal(SignalId signal);//blokirati dati signal
	static void blockSignalGlobally(SignalId signal);//blokirati dati signal za sve PCB-ove
	void unblockSignal(SignalId signal);//deblokirati dati signal
	static void unblockSignalGlobally(SignalId signal);//deblokirati dati signal za sve PCB-ove

	void signalizirajSveNiti();//odraditi sve signale na kraju timer-a
	/****************************************/


};

void oslobodiNit();//Za signal0

void idle();

#endif /* PCB_H_ */

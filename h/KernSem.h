#ifndef KERNSEM_H_
#define KERNSEM_H_

class Semaphore;
class listaPCB;
class listaSem;
class listKernel;

class KernelSem{
public:
	KernelSem(Semaphore* s,int init);
	~KernelSem();

	int wait(unsigned int maxTimeToWait);
	int signal(int n=0);
	int val()const;
	void ispisi();
	int id;
	static int idnext;

	static void signalizirajSve();

	listaSem* TimerSemafori;
	int valSem;
	listaPCB* blokiraneNiti;
	Semaphore* semafor;
	static listKernel* listaSemafora;
};

#endif

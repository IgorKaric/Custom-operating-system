#ifndef KERNELEV_H_
#define KERNELEV_H_

class Event;
class PCB;
typedef unsigned char IVTNo;


class KernelEv{
public:
	KernelEv(IVTNo ivtNo, Event* event);
	~KernelEv();

	void wait();
	void signal();

	int valEv;
	IVTNo ivtNo;
	PCB* nit;
	PCB* blokiranaNit;
	Event* mojEvent;

};





#endif /* KERNELEV_H_ */

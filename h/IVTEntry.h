#ifndef IVTENTRY_H_
#define IVTENTRY_H_


typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

class KernelEv;

class IVTEntry{
public:
	IVTEntry(IVTNo br,pInterrupt novaRutina);
	~IVTEntry();


	IVTNo ivtNo;
	pInterrupt staraRutina;
	static IVTEntry* ivtTabela[256];
	KernelEv* myKernelEv;


	void signal();
	void pozoviStaru();
	void postaviEvent(KernelEv* ke);
};





#endif /* IVTENTRY_H_ */

#ifndef LISTAPCB_H_
#define LISTAPCB_H_

class PCB;
class Thread;


typedef unsigned SignalId;

class listaPCB{
private:
	typedef struct elem{
		PCB* pcb;
		struct elem* sledeci;
		elem(PCB* pcbb){
			pcb=pcbb;
			sledeci=0;
		}
	}Elem;
	Elem* prvi;
	Elem* poslednji;
public:
	listaPCB();
	~listaPCB();
	void stavi(PCB* pcbb);
	PCB* uzmi();
	PCB* izbaciIzSvih(int id);
	Thread* uzmiNit(int id);
	int isEmpty();
	int brojElem;

	//signali
	void blokirajSve(SignalId id);
	void deblokirajSve(SignalId id);
};

#endif /* LISTAPCB_H_ */

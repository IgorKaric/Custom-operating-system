#ifndef LISTASEM_H_
#define LISTASEM_H_


class PCB;
class KernelSem;

class listaSem{
public:
	struct elem{
		PCB* pcb;
		KernelSem* mySem;
		elem* sledeci;
		int time;
		elem(PCB* pcbb,int t,KernelSem* sem){
			pcb=pcbb;
			mySem=sem;
			sledeci=0;
			time=t;
		}
	};
	elem* prvi;
	elem* poslednji;
	int brojElem;
	listaSem();
	~listaSem();
	void stavi(PCB* pcbb, int t,KernelSem* ks);
	void signaliziraj();
	int isEmpty();
	void ispisi();
	PCB* uzmi();

};





#endif /* LISTASEM_H_ */

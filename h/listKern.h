/*
 * listKern.h
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#ifndef LISTKERN_H_
#define LISTKERN_H_

class KernelSem;

class listKernel{
public:
	listKernel();
	~listKernel();
	struct elem{
		KernelSem* ks;
		elem* sledeci;
		elem(KernelSem* sem){
			ks=sem;
			sledeci=0;
		}
	};
	elem* prvi;
	elem* poslednji;
	int brojElemenata;
	void stavi(KernelSem*);
	void signaliziraj();
	void izbaci(KernelSem* k);
};



#endif /* LISTKERN_H_ */

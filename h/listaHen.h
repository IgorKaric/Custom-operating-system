/*
 * listaHen.h
 *
 *  Created on: Jul 10, 2020
 *      Author: OS1
 */

#ifndef LISTAHEN_H_
#define LISTAHEN_H_

typedef void (*SignalHandler)();

class listaHendlera{
public:

	struct cvorHendlera{
		SignalHandler hendler;
		cvorHendlera* next;

		cvorHendlera(SignalHandler h){
			hendler=h;
			next=0;
		}
	};

	//Napravi listu
	listaHendlera(){
		prvi=0;
		poslednji=0;
	}

	//Obrisi listu
	~listaHendlera(){
		while(prvi){
			cvorHendlera* pom=prvi;
			prvi=prvi->next;
		//	delete pom;
		}
		prvi=0;
		poslednji=0;
	}

	cvorHendlera* prvi;
	cvorHendlera* poslednji;

	void dodaj(SignalHandler a);
	void izbaci();
	void pozoviFunkciju();
	void prekopirajHendlere(listaHendlera* drugi);
	void zameni(SignalHandler hand1,SignalHandler hand2);

};



#endif /* LISTAHEN_H_ */

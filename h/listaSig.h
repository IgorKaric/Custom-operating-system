/*
 * listaSig.h
 *
 *  Created on: Jul 10, 2020
 *      Author: OS1
 */

#ifndef LISTASIG_H_
#define LISTASIG_H_

#include "listaHen.h"
#include "iostream.h"

typedef void (*SignalHandler)();
typedef unsigned SignalId;

class listaHendlera;

class listaSignala{
public:
	struct signal{
		SignalId id;
		signal* next;
		int blokiran;
		listaHendlera* hendleri;

		signal(SignalId idd){
			id=idd;
			blokiran=0;
			next=0;
			hendleri=new listaHendlera();
		}
	};


	signal* prvi;
	signal* poslednji;
	int brElem;

	listaSignala();
	~listaSignala();
	void dodaj(SignalId idd);//Dodaj signal u listu
	void dodaj(SignalHandler h);//Dodaj u handler
	void dodajHandler(SignalId idd, SignalHandler h);
	void obrisiSveHendlere(SignalId idd);
	void blokirajSignal(SignalId idd);
	void deblokirajSignal(SignalId idd);
	void signaliziraj(listaSignala* registrovani);
	void prekopiraj(listaSignala* registrovani);
	void zameni(SignalId id,SignalHandler hand1,SignalHandler hand2);
	void obrisiSignal(SignalId id);
	void ispisi();
};


#endif /* LISTASIG_H_ */

/*
 * listaHen.cpp
 *
 *  Created on: Jul 10, 2020
 *      Author: OS1
 */

#include "listaHen.h"
#include <iostream.h>

//Dodaj u listu
void listaHendlera::dodaj(SignalHandler a){
	cvorHendlera* pom=new cvorHendlera(a);
	if(prvi==0){
		prvi=pom;
		poslednji=pom;
	}else{
		poslednji->next=pom;
		poslednji=pom;
	}
}

//Izbaci iz liste
void listaHendlera::izbaci(){
	if(prvi!=0){
		cvorHendlera* pom=prvi;
		prvi=prvi->next;
		delete pom;
	}
}

//Pozovi sve hendlere u signalu
void listaHendlera::pozoviFunkciju(){
	cvorHendlera* cur=prvi;
	while(cur!=0){
		cur->hendler();
		cur=cur->next;
	}
}

//Kopiranje hendlera
void listaHendlera::prekopirajHendlere(listaHendlera* drugi){
	cvorHendlera* currDrugi=drugi->prvi;
	while(currDrugi!=0){
		cvorHendlera* pom=new cvorHendlera(currDrugi->hendler);
		if(prvi==0){
			prvi=pom;
			poslednji=pom;
		}else{
			poslednji->next=pom;
			poslednji=pom;
		}
		//dodaj(currDrugi->hendler);
		currDrugi=currDrugi->next;
	}
}

//Zamena dva hendlera
void listaHendlera::zameni(SignalHandler hand1, SignalHandler hand2){
	cvorHendlera* p=0;
	cvorHendlera* q=0;
	cvorHendlera* curr=prvi;
	while(curr!=0){
		if(curr->hendler==hand1)
			p->hendler=hand1;
		if(curr->hendler==hand2)
			q->hendler=hand2;
		curr=curr->next;
	}
	if(p==0 || q==0)
		return;
	p->hendler=hand2;
	q->hendler=hand1;
}

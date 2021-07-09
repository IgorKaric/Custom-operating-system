/*
 * listKern.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */
#include "listKern.h"
#include "KernSem.h"
#include "listaSem.h"

//Napravi listu
listKernel::listKernel(){
	prvi=0;
	poslednji=0;
	brojElemenata=0;
}

//Unisti listu
listKernel::~listKernel(){
	while(prvi!=0){
		elem* pom=prvi;
		prvi=prvi->sledeci;
		delete pom;
	}
	brojElemenata=0;
	poslednji=prvi=0;
}

//Stavi u listu
void listKernel::stavi(KernelSem* s){
	elem* pom=new elem(s);
	brojElemenata++;
	if(prvi==0){
		prvi=pom;
		poslednji=pom;
	}else{
		poslednji->sledeci=pom;
		poslednji=pom;
	}
}

//Signaliziraj sve TimerSemafore
void listKernel::signaliziraj(){
	elem* curr=prvi;
	while(curr!=0){
		curr->ks->TimerSemafori->signaliziraj();
		curr=curr->sledeci;
	}
}

void listKernel::izbaci(KernelSem* k){
	elem* curr=prvi;
	elem* prev=0;
	while(curr!=0 && curr->ks!=k){
		prev=curr;
		curr=curr->sledeci;
	}
	if(curr==0)
		return;
	if(prev==0)
		prvi=curr->sledeci;
	else
		prev->sledeci=curr->sledeci;
	delete curr;
	brojElemenata--;
}


/*
 * listaSig.cpp
 *
 *  Created on: Jul 10, 2020
 *      Author: OS1
 */

#include "listaSig.h"
#include <iostream.h>
#include "PCB.h"

//Napravi listu
listaSignala::listaSignala(){
	prvi=poslednji=0;
	brElem=0;
}

//Obrisi listu
listaSignala::~listaSignala(){
	while(prvi!=0){
		signal* pom=prvi;
		prvi=prvi->next;
//		delete pom;
	}
	prvi=0;
	poslednji=0;
}

//Dodaj novi signal u lisu
void listaSignala::dodaj(SignalId idd){
	signal* pom=new signal(idd);
	pom->blokiran=0;
	if(prvi==0){
		prvi=pom;
		poslednji=pom;
	}else{
		poslednji->next=pom;
		poslednji=pom;
	}
	brElem++;
}

//Za zadati signal dodaj novi hendler
void listaSignala::dodajHandler(SignalId idd,SignalHandler h){
//	cout<<"ID: "<<idd<<endl;
//	if(PCB::running->getId()==2)
//		cout<<"main nit register";
	signal* curr=prvi;
	while(curr!=0 && curr->id!=idd)
		curr=curr->next;
	if(curr==0){
		cout<<"nikad"<<endl;
		return;
	}
//	if(PCB::running->getId()==2)
//		cout<<"hendler za nit 0 "<<curr->id<<endl;
	curr->hendleri->dodaj(h);
}

//Za zadati signal obrisi sve hendlere
void listaSignala::obrisiSveHendlere(SignalId idd){
	signal* curr=prvi;
	while(curr!=0 && curr->id!=idd)
		curr=curr->next;
	if(curr==0)
		return;
	delete curr->hendleri;
}

//Blokiraj zadati signal
void listaSignala::blokirajSignal(SignalId idd){
	signal* curr=prvi;
	while(curr!=0 && curr->id!=idd)
		curr=curr->next;
	if(curr==0)
		return;
	curr->blokiran=1;
}

//Deblokiraj zadati signal
void listaSignala::deblokirajSignal(SignalId idd){
	signal* curr=prvi;
	while(curr!=0 && curr->id!=idd){
		curr=curr->next;
	}
	if(curr==0){
		return;
	}
	//cout<<"DEBLOKIRAN"<<endl;
	curr->blokiran=0;
}

//Dodavanje hendlera za signal0
void listaSignala::dodaj(SignalHandler h){
	signal* curr=prvi;
	while(curr!=0 && curr->id!=0)
		curr=curr->next;
	if(curr==0)
		return;
	curr->hendleri->dodaj(h);
}

//Brisanje signala iz liste registrovanih
void listaSignala::obrisiSignal(SignalId id){
	signal* curr=prvi;
	signal* prev=0;
	while(curr!=0 && curr->id!=id){
		prev=curr;
		curr=curr->next;
	}
	if(curr==0)
		return;
	if(prev==0)
		prvi=curr->next;
	else
		prev->next=curr->next;
	delete curr;
	brElem--;
}

void listaSignala::ispisi(){
	signal* curr=prvi;
	cout<<"SVI SIGNALI   ";
	while(curr!=0){
		cout<<curr->id<<"    ";
		curr=curr->next;
	}
	cout<<endl;
}

//Obradjivanje hendlera za sve signale
void listaSignala::signaliziraj(listaSignala* registrovani){
//	if(PCB::running->getId()==2 || PCB::running->getId()==0) //AKO NE BUDE RADILO
//		return;
	signal* currReg=registrovani->prvi;
	while(currReg!=0){
		signal* currSvi=prvi;
		SignalId cuvajId=currReg->id;
		while(currSvi!=0){
			if(currSvi->id==currReg->id && currSvi->blokiran==0){
				//registrovani->ispisi();
				currSvi->hendleri->pozoviFunkciju();
				registrovani->obrisiSignal(cuvajId);
				break;
			}
			currSvi=currSvi->next;
		}
		currReg=currReg->next;
	}
}

//Kopiranje liste od parent-a
void listaSignala::prekopiraj(listaSignala* registrovani2){
	signal* currCale=registrovani2->prvi;
	while(currCale!=0){
		signal* pom=new signal(currCale->id);
		pom->hendleri->prekopirajHendlere(currCale->hendleri);
		if(prvi==0){
			prvi=pom;
			poslednji=pom;
		}else{
			poslednji->next=pom;
			poslednji=pom;
		}
		currCale=currCale->next;
	}
}

//Za zadati signal zameniti dva data hendlera
void listaSignala::zameni(SignalId id, SignalHandler hand1,SignalHandler hand2){
	signal* curr=prvi;
	while(curr!=0 && curr->id!=id)
		curr=curr->next;
	if(curr==0)
		return;
	curr->hendleri->zameni(hand1,hand2);
}

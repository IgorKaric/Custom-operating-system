/*
 * main.cpp
 *
 *  Created on: May 14, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include "Thread.h"
#include "IVTEntry.h"
#include "semaphor.h"
#include "user.h"
#include "SCHEDULE.H"
#include "bounded.h"
#include <iostream.h>
#include <stdlib.h>
#include "Event.h"
void inic();
void restore();

int povratnaVrednost;
extern int userMain(int argc,char* argv[]);


class mainNit:public Thread{
public:
	mainNit(int argc,char** argv){
		this->argc=argc;
		this->argv=argv;
	}

	void run(){
		//cout<<"nesto"<<endl;
		povratnaVrednost=userMain(argc,argv);
	}

	~mainNit(){waitToComplete();}
	int argc;
	char** argv;
};


int main(int argc,char* argv[]){
	inic();
	mainNit* mainNitt=new mainNit(argc,argv);
	mainNitt->start();
	delete mainNitt;
	restore();
	return povratnaVrednost;
}

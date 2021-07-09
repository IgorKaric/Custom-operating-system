/*
 * Idle.h
 *
 *  Created on: May 14, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include <iostream.h>

class Idle:public Thread{
public:
	Idle():Thread(1024,1){}
	void run(){
		int fleg=1;
		//cout<<"Idle"<<endl;
		while(fleg){

		}
	}
	PCB* dohvatiPCB(){
		return myPCB;
	}
};


#endif /* IDLE_H_ */

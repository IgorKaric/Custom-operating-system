#include <dos.h>
#include "SCHEDULE.H"
#include "PCB.h"
#include "KernSem.h"
#include "listaSem.h"
#include <iostream.h>

volatile unsigned tss;
volatile unsigned tsp;
volatile unsigned tbp;

volatile int brojac=20;
//volatile int lockFlag=1;
volatile int zahtevanaPromenaKonteksta=0;

unsigned oldTimerOFF;
unsigned oldTimerSEG;


extern void tick();
extern void oslobodiNit();

void interrupt timer(){ // prekidna rutina
	if (!zahtevanaPromenaKonteksta) {
		KernelSem::signalizirajSve();
		tick();
		PCB::running->timeSlice--;
		if(PCB::running->timeSlice<0)
			PCB::running->timeSlice=0;
		asm int 60h

	}
	if (PCB::running->timeSlice==0 || zahtevanaPromenaKonteksta) {
		if(!zahtevanaPromenaKonteksta){
				PCB::running->timeSlice=PCB::running->oldTimeSlice;
		}
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;

		if(PCB::running->status==Spreman)
			Scheduler::put(PCB::running);
		PCB::running=Scheduler::get();
		if(PCB::running==0){
			PCB::running=PCB::myIdle->dohvatiPCB();
		}
		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
//			PCB::running->registrovaniSignali->ispisi();
		PCB::running->signalizirajSveNiti();
	}
	zahtevanaPromenaKonteksta=0;
}



void inic(){
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax //ex=0

		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

void restore(){
	asm{
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}



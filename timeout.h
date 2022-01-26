#ifndef TIMEOUT_H

#define TIMEOUT_H


typedef void (*myFuncTimer)(char *Args);


typedef struct pTimer
{
	long next_At;
	long repete;
	long ecart;
	char *args;
	char *type;
	myFuncTimer func;
	struct pTimer *precedent;
	struct pTimer *suivant;
}pTimer;

typedef struct pTimer_at_time
{
	long time;
	char *args;
	myFuncTimer func;
	struct pTimer_at_time *precedent;
	struct pTimer_at_time *suivant;

}pTimer_at_time;


void new_timer(long repete , long ecart, void *proc , char *parametre, char *type);
void execute_timer();
int del_Timer(char *repere , char *type);
int timer_existe(char *repere , char *type);


void new_timer_at_time(long time , void *proc , char *parametre);
void execute_timer_at_time();
int del_Timer_at_time(char *repere);

#endif







#include "main.h"

pTimer *STimer;
pTimer_at_time *STimer_at_time;

/**
 		timer_repete
**/
void new_timer(long repete , long ecart, void *proc , char *parametre , char *type)
{
	pTimer *nTimer;
	nTimer = (pTimer*)malloc(sizeof(pTimer));
	if(!nTimer)
		return;

	nTimer->next_At = time(NULL) + ecart;
	nTimer->ecart = ecart;
	nTimer->repete = repete;
	nTimer->func = proc;

	if(parametre)
	{
		STRDUP(nTimer->args,parametre)
	}
	else
	{
		STRDUP(nTimer->args,"?")
	}

	if(type)
	{
		STRDUP(nTimer->type,type)
	}
	else
	{
		STRDUP(nTimer->type,"?")
	}

	nTimer->precedent = NULL;
	nTimer->suivant = STimer;
	if (STimer)
    	STimer->precedent = nTimer;
	STimer = nTimer;
	return;
}


/**
 		Execution des timers
**/

void execute_timer()
{
	pTimer *tmp;

retour:

	tmp = STimer;
	while(tmp)
	{
		if(time(NULL) >= tmp->next_At)
		{
			tmp->func(tmp->args);

			if(tmp->repete != 100000)
				tmp->repete--;



			if(tmp->repete == 0)
			{
				if(tmp->suivant)
					tmp->suivant->precedent = tmp->precedent;

				if(tmp->precedent)
					tmp->precedent->suivant = tmp->suivant;

				if(tmp == STimer)
					STimer = tmp->suivant;

				FREE(tmp->type);
				FREE(tmp->args);
				FREE(tmp);
				printf("timer detruit\n");
				goto retour;
			}
			else
			{
				tmp->next_At = time(NULL) + tmp->ecart;
			}
		}
		tmp = tmp->suivant;
	}
}

int del_Timer(char *repere , char *type)
{
	pTimer *timer;
	timer = STimer;
	while (timer)
	{
		if(timer->args && !strcmp(timer->args,repere) && !strcmp(timer->type,type))
		{
			if(timer->suivant)
				timer->suivant->precedent = timer->precedent;

			if(timer->precedent)
				timer->precedent->suivant = timer->suivant;

			if(timer == STimer)
				STimer = timer->suivant;

			FREE(timer->type);
			FREE(timer->args);
			FREE(timer);
#ifdef DEBUG_IRC
			printf("timer detruit\n");
#endif
			timer = STimer;
			continue;
		}
		if(!strcmp(repere,"*") && !strcmp(timer->type,type))
		{
			if(timer->suivant)
				timer->suivant->precedent = timer->precedent;

			if(timer->precedent)
				timer->precedent->suivant = timer->suivant;

			if(timer == STimer)
				STimer = timer->suivant;

			FREE(timer->type);
			FREE(timer->args);
			FREE(timer);
#ifdef DEBUG_IRC
			printf("timer detruit\n");
#endif
			timer = STimer;
			continue;
		}

		timer = timer->suivant;
	}
	return 1;
}

int timer_existe(char *repere , char *type)
{
	pTimer *timer;
	timer = STimer;
	while (timer)
	{
		if(timer->args && !strcmp(timer->args,repere) && !strcmp(timer->type,type))
			return 1;

		timer = timer->suivant;
	}
	return 0;
}



void new_timer_at_time(long time , void *proc , char *parametre)
{
	pTimer_at_time *nTimer = (pTimer_at_time*)malloc(sizeof(pTimer_at_time));
	if(!nTimer)
		return;

	nTimer->time = time;
	nTimer->func = proc;

	if(parametre)
	{
		STRDUP(nTimer->args,parametre)
	}
	else
	{
		STRDUP(nTimer->args,"?")
	}

	nTimer->precedent = NULL;
	nTimer->suivant = STimer_at_time;
	if (STimer_at_time)
    	STimer_at_time->precedent = nTimer;
	STimer_at_time = nTimer;
	return;

}

void execute_timer_at_time()
{
	pTimer_at_time *tmp;

retour:

	tmp = STimer_at_time;
	while(tmp)
	{
		if(time(NULL) >= tmp->time)
		{
			tmp->func(tmp->args);


			if(tmp->suivant)
				tmp->suivant->precedent = tmp->precedent;

			if(tmp->precedent)
				tmp->precedent->suivant = tmp->suivant;

			if(tmp == STimer_at_time)
				STimer_at_time = tmp->suivant;

			FREE(tmp->args);
			FREE(tmp);

			goto retour;
		}
		tmp = tmp->suivant;
	}
}


int del_Timer_at_time(char *repere)
{
	pTimer_at_time *timer;
	timer = STimer_at_time;
	while (timer)
	{
		if(timer->args && !strcmp(timer->args,repere))
		{
			if(timer->suivant)
				timer->suivant->precedent = timer->precedent;

			if(timer->precedent)
				timer->precedent->suivant = timer->suivant;

			if(timer == STimer_at_time)
				STimer_at_time = timer->suivant;

			FREE(timer->args);
			FREE(timer);
		}
		timer = timer->suivant;
	}
	return 1;
}









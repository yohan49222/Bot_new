#include "main.h"

extern Config *myconfig;

/**
	************************
	** Gestions des users **
	************************
**/

User *Alluser = NULL;

User *new_user(char *nick,char *handle,char *host,char *real,long Ctime,char *server)
{
	User *use;
	char *t;

	if(!nick || !handle || !host || !server)
		return NULL;

	if(!*nick || !*handle || !*host || !*server)
		return NULL;

	use = get_user(nick);
	if(use)
		del_user(nick,"Doublon");

	use = (User*)malloc(sizeof(User));
	if(!use)
		return NULL;

	STRDUP(use->nick,nick)
	STRDUP(use->host,host)
	STRDUP(use->vhost,host)
	STRDUP(use->handle,handle)
	STRDUP(use->server,server)

	STRDUP(use->ip,"?")
	STRDUP(use->nick_jeux,"?")
	STRDUP(use->Access_Coleen_pseudo,"?")

	use->ModeGlobMaj = 0;
	use->ModeGlobMin = 0;
	use->option = 0;
	use->Access_Coleen = 0;

	if(*real)
	{
		STRDUP(use->real,real)
	}
	else
	{
		STRDUP(use->real,"?")
	}
	if(Ctime)
	{
		use->Ltime = Ctime;
		use->Ctime = Ctime;
	}
	else
	{
		use->Ltime = time(NULL);
		use->Ctime = time(NULL);
	}

	use->precedent = NULL;
	use->suivant = Alluser;
	if (Alluser)
    		Alluser->precedent = use;
	Alluser = use;

	t = resol_host(use->host);
	set_ip(use,t);

	use->Threads_pid = 0;

	return Alluser;
}

int del_user(char *nick,char *mess)
{
	User *use = get_user(nick);
	if(!use)
		return 0;

	if(use->Threads_pid != 0)
		kill_pthread(use);

	printf("debut user_part_allchan(use,mess)\n");
	user_part_allchan(use,mess);
	printf("fin user_part_allchan(use,mess)\n");

	if(use->suivant)
		use->suivant->precedent = use->precedent;

	if(use->precedent)
		use->precedent->suivant = use->suivant;

	if(use == Alluser)
		Alluser = use->suivant;

	printf("fin chainage\n");

	FREE(use->nick)
	FREE(use->handle)
	FREE(use->host)
	FREE(use->vhost)
	FREE(use->real)
	FREE(use->server)
	FREE(use->ip)
	FREE(use->nick_jeux)
	FREE(use->Access_Coleen_pseudo)
	FREE(use);
	printf("fin FREE\n");
	return 1;
}

int clear_user(char *motif)
{
	User *use;
	while (Alluser)
	{
		user_part_allchan(Alluser,motif ? motif : Alluser->nick);

		use = Alluser;
		Alluser = Alluser->suivant;
		FREE(use->nick)
		FREE(use->handle)
		FREE(use->host)
		FREE(use->vhost)
		FREE(use->real)
		FREE(use->server)
		FREE(use->ip)
		FREE(use->nick_jeux)
		FREE(use->Access_Coleen_pseudo)
		FREE(use)
		use = NULL;
	}
	Alluser = NULL;
	return 1;
}

long User_t()
{
	int count = 0;

	User *u;
	u = Alluser;
	while (u)
	{
		count++;
		u = u->suivant;
	}
	return sizeof(User) * (count+1);
}

User *get_user(char *nick)
{
	User *use = Alluser;
	while(use)
	{
		if(!strcasecmp(use->nick,nick))
			return use;

		use = use->suivant;
	}
	return NULL;
}

int set_nick(char *nick,char *newnick)
{
	User *use = get_user(nick);
	if(!use)
		return 0;

	set_Ltime(nick);

	FREE(use->nick)
	STRDUP(use->nick,newnick)

	return 1;
}

int set_handle(char *nick,char *handle,char *from)
{
	User *use = get_user(nick);
	if(!use)
		return 0;

	FREE(use->handle)
	STRDUP(use->handle,handle)

	return 1;
}

int set_vhost(char *nick,char *vhost,char *from)
{
	User *use = get_user(nick);
	if(!use)
		return 0;

	FREE(use->vhost)
	STRDUP(use->vhost,vhost)

	return 1;

}

int set_real(char *nick,char *real,char *from)
{
	User *use = get_user(nick);
	if(!use)
		return 0;

	FREE(use->real)
	STRDUP(use->real,real)

	return 1;

}

int set_Ltime(char *nick)
{
	User *use = get_user(nick);
	if(!use)
		return 0;

	use->Ltime = time(NULL);

	return 1;
}

int set_ip(User *use,char *ip)
{
	FREE(use->ip)
	STRDUP(use->ip,ip)
	
	return 1;
}

int set_nick_jeux(User *use,char *newnick)
{
	FREE(use->nick_jeux)
	STRDUP(use->nick_jeux,newnick)

	return 1;
}

/*
	modification des flags de l'user
*/

void set_flag(User *use,char *from, char flag,int onoff)
{
	set_Ltime(use->nick);

	if(onoff == 1)
	{
		switch(flag)
		{
			case'A':
				use->ModeGlobMaj |= U_MODE_A ;
				use->option |= IS_PROTECT ;
				break;

			case'B':
				use->ModeGlobMaj |= U_MODE_B ;
				break;
			case'C':
				use->ModeGlobMaj |= U_MODE_C ;
				use->option |= IS_PROTECT ;
				break;
			case'D':
				use->ModeGlobMaj |= U_MODE_D ;
				break;
			case'G':
				use->ModeGlobMaj |= U_MODE_G ;
				break;
			case'H':
				use->ModeGlobMaj |= U_MODE_H ;
				break;
			case'K':
				use->ModeGlobMaj |= U_MODE_K ;
				break;
			case'L':
				use->ModeGlobMaj |= U_MODE_L ;
				break;
			case'N':
				use->ModeGlobMaj |= U_MODE_N ;
				break;
			case'O':
				use->ModeGlobMaj |= U_MODE_O ;
				use->option |= IS_PROTECT ;
				break;
			case'R':
				use->ModeGlobMaj |= U_MODE_R ;
				break;
			case'S':
				use->ModeGlobMaj |= U_MODE_S ;
				break;
			case'T':
				use->ModeGlobMaj |= U_MODE_T ;
				break;
			case'V':
				use->ModeGlobMaj |= U_MODE_V ;
				break;
			case'W':
				use->ModeGlobMaj |= U_MODE_W ;
				break;
			case'X':
				use->ModeGlobMaj |= U_MODE_X ;
				break;
			case'Z':
				use->ModeGlobMaj |= U_MODE_Z ;
				break;

			case'a':
				use->ModeGlobMin |= U_MODE_a ;
				break;
			case'b':
				use->ModeGlobMin |= U_MODE_b ;
				break;
			case'c':
				use->ModeGlobMin |= U_MODE_c ;
				break;
			case'd':
				use->ModeGlobMin |= U_MODE_d ;
				break;
			case'g':
				use->ModeGlobMin |= U_MODE_g ;
				break;
			case'h':
				use->ModeGlobMin |= U_MODE_h ;
				break;
			case'i':
				use->ModeGlobMin |= U_MODE_i ;
				break;
			case'k':
				use->ModeGlobMin |= U_MODE_k ;
				break;
			case'n':
				use->ModeGlobMin |= U_MODE_n ;
				break;
			case'o':
				use->ModeGlobMin |= U_MODE_o ;
				use->option |= IS_PROTECT ;
				break;
			case'p':
				use->ModeGlobMin |= U_MODE_p ;
				break;
			case'q':
				use->ModeGlobMin |= U_MODE_q ;
				break;
			case'r':
				use->ModeGlobMin |= U_MODE_r ;
				break;
			case's':
				use->ModeGlobMin |= U_MODE_s ;
				break;
			case't':
				use->ModeGlobMin |= U_MODE_t ;
				break;
			case'v':
				use->ModeGlobMin |= U_MODE_v ;
				break;
			case'w':
				use->ModeGlobMin |= U_MODE_w ;
				break;
			case'x':
				use->ModeGlobMin |= U_MODE_x ;
				break;
			case'z':
				use->ModeGlobMin |= U_MODE_z ;
				break;
		}
	}
	else
	{
		switch(flag)
		{
			case'A':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_A);
				break;
			case'B':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_B);
				break;
			case'C':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_C);
				break;
			case'D':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_D);
				break;
			case'G':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_G);
				break;
			case'H':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_H);
				break;
			case'K':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_K);
				break;
			case'L':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_L);
				break;
			case'N':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_N);
				break;
			case'O':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_O);
				break;
			case'R':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_R);
				break;
			case'S':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_S);
				break;
			case'T':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_T);
				break;
			case'V':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_V);
				break;
			case'W':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_W);
				break;
			case'X':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_X);
				break;
			case'Z':
				use->ModeGlobMaj &= (0xFFFFFFFF ^ U_MODE_Z);
				break;

			case'a':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_a);
				break;
			case'b':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_b);
				break;
			case'c':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_c);
				break;
			case'd':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_d);
				break;
			case'g':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_g);
				break;
			case'h':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_h);
				break;
			case'i':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_i);
				break;
			case'k':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_k);
				break;
			case'n':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_n);
				break;
			case'o':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_o);
				break;
			case'p':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_p);
				break;
			case'q':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_q);
				break;
			case'r':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_r);
				break;
			case's':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_s);
				break;
			case't':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_t);
				break;
			case'v':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_v);
				break;
			case'w':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_w);
				break;
			case'x':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_x);
				break;
			case'z':
				use->ModeGlobMin &= (0xFFFFFFFF ^ U_MODE_z);
				break;
		}
	}
}


char *list_Mode_User(User *user)
{
	int x = 0;
	char mode[MAXLEN];
	if(user->ModeGlobMin & U_MODE_a) mode[x++] = 'a';
	if(user->ModeGlobMin & U_MODE_b) mode[x++] = 'b';
	if(user->ModeGlobMin & U_MODE_c) mode[x++] = 'c';
	if(user->ModeGlobMin & U_MODE_d) mode[x++] = 'd';
	if(user->ModeGlobMin & U_MODE_g) mode[x++] = 'g';
	if(user->ModeGlobMin & U_MODE_h) mode[x++] = 'h';
	if(user->ModeGlobMin & U_MODE_i) mode[x++] = 'i';
	if(user->ModeGlobMin & U_MODE_k) mode[x++] = 'k';
	if(user->ModeGlobMin & U_MODE_n) mode[x++] = 'n';
	if(user->ModeGlobMin & U_MODE_o) mode[x++] = 'o';
	if(user->ModeGlobMin & U_MODE_p) mode[x++] = 'p';
	if(user->ModeGlobMin & U_MODE_q) mode[x++] = 'q';
	if(user->ModeGlobMin & U_MODE_r) mode[x++] = 'r';
	if(user->ModeGlobMin & U_MODE_s) mode[x++] = 's';
	if(user->ModeGlobMin & U_MODE_t) mode[x++] = 't';
	if(user->ModeGlobMin & U_MODE_v) mode[x++] = 'v';
	if(user->ModeGlobMin & U_MODE_w) mode[x++] = 'w';
	if(user->ModeGlobMin & U_MODE_x) mode[x++] = 'x';
	if(user->ModeGlobMin & U_MODE_z) mode[x++] = 'z';

	if(user->ModeGlobMaj & U_MODE_A) mode[x++] = 'A';
	if(user->ModeGlobMaj & U_MODE_B) mode[x++] = 'B';
	if(user->ModeGlobMaj & U_MODE_C) mode[x++] = 'C';
	if(user->ModeGlobMaj & U_MODE_D) mode[x++] = 'D';
	if(user->ModeGlobMaj & U_MODE_G) mode[x++] = 'G';
	if(user->ModeGlobMaj & U_MODE_H) mode[x++] = 'H';
	if(user->ModeGlobMaj & U_MODE_K) mode[x++] = 'K';
	if(user->ModeGlobMaj & U_MODE_L) mode[x++] = 'L';
	if(user->ModeGlobMaj & U_MODE_N) mode[x++] = 'N';
	if(user->ModeGlobMaj & U_MODE_O) mode[x++] = 'O';
	if(user->ModeGlobMaj & U_MODE_R) mode[x++] = 'R';
	if(user->ModeGlobMaj & U_MODE_S) mode[x++] = 'S';
	if(user->ModeGlobMaj & U_MODE_T) mode[x++] = 'T';
	if(user->ModeGlobMaj & U_MODE_V) mode[x++] = 'V';
	if(user->ModeGlobMaj & U_MODE_W) mode[x++] = 'W';
	if(user->ModeGlobMaj & U_MODE_X) mode[x++] = 'X';
	if(user->ModeGlobMaj & U_MODE_Z) mode[x++] = 'Z';
	mode[x] = '\0';
	return strdup(mode);
}


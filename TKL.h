#ifndef TKL_H

#define TKL_H

typedef struct Tkl
{
	char *mask;
	
	struct Tkl *suivant;
	struct Tkl *precedent;
}Tkl;

Tkl *new_Tkl(char *mask);
int clear_Tkl();
void del_Tkl(char *mask);
Tkl *get_tkl(char *mask);



#endif



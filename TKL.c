
#include "main.h"

extern Config *myconfig;

Tkl *pTkl = NULL;

Tkl *new_Tkl(char *mask)
{
	Tkl *tkl;

	tkl = (Tkl*)malloc(sizeof(Tkl));
	if(!tkl)
		return NULL;

	STRDUP(tkl->mask,mask)

	tkl->precedent = NULL;
	tkl->suivant = pTkl;
	if (pTkl)
    		pTkl->precedent = tkl;
	pTkl = tkl;

	return pTkl;
}

int clear_Tkl()
{
	Tkl *tkl;
	while (pTkl)
	{
		tkl = pTkl;
		pTkl = pTkl->suivant;
		FREE(tkl->mask)
		FREE(tkl)
		tkl = NULL;
	}
	pTkl = NULL;
	return 1;
}

void del_Tkl(char *mask)
{
	Tkl *tkl;
	tkl = get_tkl(mask);
	if(!tkl)
		return;

	if(tkl->suivant)
		tkl->suivant->precedent = tkl->precedent;

	if(tkl->precedent)
		tkl->precedent->suivant = tkl->suivant;

	if(tkl == pTkl)
		pTkl = tkl->suivant;

	FREE(tkl->mask)
	FREE(tkl)

	return;
}

Tkl *get_tkl(char *mask)
{
	Tkl *tkl;
	tkl = pTkl;
	while(tkl)
	{
		if(!strcasecmp(tkl->mask,mask))
			return tkl;

		tkl = tkl->suivant;
	}
	return NULL;
}



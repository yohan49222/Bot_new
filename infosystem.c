#include "main.h"

char *sys_machine()
{
	char *t;
	struct utsname *u = (struct utsname*)malloc(sizeof(struct utsname));
	uname(u);
	STRDUP(t,u->machine);
	FREE(u);
	return t;
}

char *sys_nodename()
{
	char *t;
	struct utsname *u = (struct utsname*)malloc(sizeof(struct utsname));
	uname(u);
	STRDUP(t,u->nodename);
	FREE(u);
	return t;
}

char *sys_release()
{
	char *t;
	struct utsname *u = (struct utsname*)malloc(sizeof(struct utsname));
	uname(u);
	STRDUP(t,u->release);
	FREE(u);
	return t;
}

char *sys_sysname()
{
	char *t;
	struct utsname *u = (struct utsname*)malloc(sizeof(struct utsname));
	uname(u);
	STRDUP(t,u->sysname);
	FREE(u);
	return t;
}

char *sys_version()
{
	char *t;
	struct utsname *u = (struct utsname*)malloc(sizeof(struct utsname));
	uname(u);
	STRDUP(t,u->version);
	FREE(u);
	return t;
}





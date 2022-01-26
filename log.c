
#include "main.h"
extern Config *myconfig;

FILE *FileLog;
int fileopen = 0;

void init_log()
{
	char buf[100];
	struct tm *phd;
	time_t tps;

	tps = time(NULL);
	phd = localtime(&tps);
	sprintf(buf,"log/%02d%02d%04d.txt",phd->tm_mday,phd->tm_mon+1,1900+phd->tm_year);
	FileLog = fopen(buf, "a+");
	if(FileLog)
		fileopen = 1;

	put_log("Demarrage\n");
}

void put_log(char *txt)
{
	char *date;
	if(!fileopen)
		return;

	date = time_fr(time(NULL));
	fprintf(FileLog,"%s -> %s\015",date,txt);
	FREE(date);
}

void close_log()
{
	if(FileLog)
		fileopen = 0;

	fclose(FileLog);
}


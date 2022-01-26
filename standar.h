#ifndef MAIN_H

#define MAIN_H

#ifdef WIN32

	#include <windows.h>
	#define strcasecmp stricmp
	#define strncasecmp strnicmp
	#define snprintf _snprintf
	#define sleep Sleep

#else

	#include <sys/time.h>
	#include <pthread.h>

#endif

/* include standard */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#endif


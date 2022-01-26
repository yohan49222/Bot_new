#ifndef IRCSOCKET_H

#define IRCSOCKET_H

/* includes de windows */
#ifdef WIN32
	#include <winsock.h>
	#pragma comment(lib,"ws2_32.lib") // link lib winsock
	typedef unsigned int u_int32_t; /* utilise par linux mais non defiini dans winsock.h */

//	JMJ : Coercion pour compatibilitï¿½avec Nux
#define close closesocket

#else
/* les includes de linux */
	typedef int SOCKET; 
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <sys/types.h>
	#define SOCKET_ERROR (-1) /* défini dans winsock.h */
       		typedef struct sockaddr_in SOCKADDR_IN; /* idem */
#endif

int connect_serveur();
int my_sock_recv_line();
int _send(char *s);

void pool_one();
void pool_two();
void pool_tree();
void sock_deconnect();

#endif


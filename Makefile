#
# InFo_BoT_V2
#
# par yoyo49
#

CC=gcc
FLAGS=-Wall -O6 -O2 -Werror -D_REENTRANT
LIBS= -lcrypt -ldl -pthread
DEBUG=-g -DDEBUG
LOG=-DNOLOG

#sources -W

SRCS= main.c log.c ircSocket.c message.csend.c user.c channel.c  raw.c raw_string.c raw_numeric.c \
bot_clone.c nickserv.c operserv.c command.c timeout.c protection.c radio.c antispam.c coleen.c globalserv.c principale.c masstoolz.c my_regex.c antiproxy.c TKL.c scrabble.c infosystem.c error.c
#

#objects
OBJS= main.o log.c ircSocket.o message.o send.o user.o channel.o raw.o raw_string.o raw_numeric.o \
bot_clone.o nickserv.o operserv.o command.o timeout.o protection.o radio.o antispam.o coleen.o globalserv.o principale.o masstoolz.o my_regex.o antiproxy.o TKL.o scrabble.o infosystem.o error.o
#


all: service

.c.o: ; $(CC) $(FLAGS) $(INCLUDES) $(DEBUG) $(LOG)  -c $<

service:  $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f service *.o core


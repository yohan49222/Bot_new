
#include "main.h"
extern Config *myconfig;
User *commandeur = NULL;
ComAction *comAction = NULL;

/**
					RAW NUMERIQUE
											**/

void p_RPL_WELCOME(  message_irc *message  )            /* 001 */
{
	/*
	:<source> 001 <pseudo> :Welcome to the <server> IRC Network <pseudo>!<handle>@<host>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}

void p_RPL_YOURHOST(  message_irc *message  )           /* 002 */
{
	/*
	:<source> 002 <pseudo> :Your host is <server>, running version <version>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_CREATED(  message_irc *message  )            /* 003 */
{
	/*
	:<source> 003 <pseudo> :This server was created <date>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MYINFO(  message_irc *message  )             /* 004 */
{
	/*
	:<source> 004 <pseudo> %s %s %s %s
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ISUPPORT(  message_irc *message  )           /* 005 */
{
	/*
	:<source> 005 <pseudo> %s :are supported by this server
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_REDIR(  message_irc *message  )              /* 010 */
{
	/*
	:<source> 010 <pseudo> <server> <port> :Please use this Server/Port instead
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_REMOTEISUPPORT(  message_irc *message  )    	/* 105 */
{
	/*
	:<source> 105 <pseudo> %s :are supported by this server
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOSUCHNICK(  message_irc *message  )         /* 401 */
{
	/*
	:<source> 401 <pseudo> <target> :No such nick/channel
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOSUCHSERVER(  message_irc *message  )               /* 402 */
{
	/*
	:<source> 402 <pseudo> <server> :No such server"
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOSUCHCHANNEL(  message_irc *message  )              /* 403 */
{
	/*
	:<source> 403 <pseudo> <channel> :No such channel
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CANNOTSENDTOCHAN(  message_irc *message  )           /* 404 */
{
	/*
	:<source> 404 <pseudo> <channel> :<channel> (<mode>)"
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TOOMANYCHANNELS(  message_irc *message  )            /* 405 */
{
	/*
	:<source> 405 <pseudo> <channel> :You have joined too many channels
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_WASNOSUCHNICK(  message_irc *message  )              /* 406 */
{
	/*
	:<source> 406 <pseudo> <nick> :There was no such nickname
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TOOMANYTARGETS(  message_irc *message  )             /* 407 */
{
	/*
	:<source> 407 <pseudo> <target> :Duplicate recipients. No message delivered"
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOSUCHSERVICE(  message_irc *message  )              /* 408 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOORIGIN(  message_irc *message  )           /* 409 */
{
	/*
	:<source> 409 <pseudo> :No origin specified
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NORECIPIENT(  message_irc *message  )                /* 411 */
{
	/*
	:<source> 411 <pseudo> :No recipient given (<var>)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOTEXTTOSEND(  message_irc *message  )               /* 412 */
{
	/*
	:<source> 412 <pseudo> :No text to send
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOTOPLEVEL(  message_irc *message  )         /* 413 */
{
	/*
	:<source> 413 <pseudo> <level> :No toplevel domain specified
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_WILDTOPLEVEL(  message_irc *message  )               /* 414 */
{
	/*
	:<source> 414 <pseudo> <wild> :Wildcard in toplevel Domain
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}

void p_ERR_UNKNOWNCOMMAND(  message_irc *message  )             /* 421 */
{
	/*
	:<source> 421 <pseudo> <var> :Unknown command
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOMOTD(  message_irc *message  )             /* 422 */
{
	/*
	:<source> 422 <pseudo> :MOTD File is missing
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOADMININFO(  message_irc *message  )                /* 423 */
{
	/*
	:<source> 423 <pseudo> <var> :No administrative info available
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_FILEERROR(  message_irc *message  )          /* 424 */
{
	/*
	:<source> 424 <pseudo> :File error doing <var> on <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOOPERMOTD(  message_irc *message  )         /* 425 */
{
	/*
	:<source> 425 <pseudo> :OPERMOTD File is missing
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TOOMANYAWAY(  message_irc *message  )                /* 429 */
{
	/*
	:<var> 429 <var> :Too Many aways - Flood Protection activated
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NONICKNAMEGIVEN(  message_irc *message  )            /* 431 */
{
	/*
	:<var> 431 <var> :No nickname given
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_ERRONEUSNICKNAME(  message_irc *message  )           /* 432 */
{
	/*
	:<var> 432 <var> <var> :Erroneous Nickname: <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NICKNAMEINUSE(  message_irc *message  )              /* 433 */
{
	/*
	:<var> 433 <var> <var> :Nickname is already in use.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NORULES(  message_irc *message  )            /* 434 */
{
	/*
	:<var> 434 <var> :RULES File is missing
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_SERVICECONFUSED(  message_irc *message  )            /* 435 */
{
	/*
		dalnet
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NICKCOLLISION(  message_irc *message  )              /* 436 */
{
	/*
	:<var> 436 <var> <var> :Nickname collision KILL
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_BANNICKCHANGE(  message_irc *message  )              /* 437 */
{
	/*
	:<var> 437 <var> <var> :Cannot change nickname while banned on channel
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NCHANGETOOFAST(  message_irc *message  )             /* 438 */
{
	/*
	:<var> 438 <var> <var> :Nick change too fast. Please wait <var> seconds
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TARGETTOOFAST(  message_irc *message  )              /* 439 */
{
	/*
	:<var> 439 <var> <var> :Message target change too fast. Please wait <var> seconds
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_SERVICESDOWN(  message_irc *message  )               /* 440 */
{
	/*
	:<var> 440 <var> <var> :Services are currently down. Please try again later.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_USERNOTINCHANNEL(  message_irc *message  )           /* 441 */
{
	/*
	:<var> 441 <var> <var> <var> :They aren't on that channel
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOTONCHANNEL(  message_irc *message  )               /* 442 */
{
	/*
	:<var> 442 <var> <var> :You're not on that channel
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_USERONCHANNEL(  message_irc *message  )              /* 443 */
{
	/*
	:<source> 443 <pseudo> <target> <channel> :is already on channel
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOLOGIN(  message_irc *message  )            /* 444 */
{
	/*
	:<var> 444 <var> <var> :User not logged in
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_SUMMONDISABLED(  message_irc *message  )             /* 445 */
{
	/*
	:<var> 445 <var> :SUMMON has been disabled
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_USERSDISABLED(  message_irc *message  )              /* 446 */
{
	/*
	:<var> 446 <var> :USERS has been disabled
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NONICKCHANGE(  message_irc *message  )               /* 447 */
{
	/*
	:<var> 447 <var> :Can not change nickname while on <var> (+N)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOTREGISTERED(  message_irc *message  )              /* 451 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_HOSTILENAME(  message_irc *message  )                /* 455 */
{
	/*
	:<var> 455 <var> :Your username <var> contained the invalid ""character(s) <var> and has been changed  <var>. ""Please use only the characters 0-9 a-z A-Z _ - ""or . in your username. Your username is the part ""before the @ in your email address.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOHIDING(  message_irc *message  )           /* 459 */
{
	/*
	:<var> 459 <var> <var> :Cannot join channel (+H)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOTFORHALFOPS(  message_irc *message  )              /* 460 */
{
	/*
	:<var> 460 <var> :Halfops cannot set mode <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NEEDMOREPARAMS(  message_irc *message  )             /* 461 */
{
	/*
	:<var> 461 <var> <var> :Not enough parameters
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_ALREADYREGISTRED(  message_irc *message  )           /* 462 */
{
	/*
	:<var> 462 <var> :You may not reregister
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOPERMFORHOST(  message_irc *message  )              /* 463 */
{
	/*
	:<var> 463 <var> :Your host isn't among the privileged
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_PASSWDMISMATCH(  message_irc *message  )             /* 464 */
{
	/*
	:<var> 464 <var> :Password Incorrect
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_YOUREBANNEDCREEP(  message_irc *message  )           /* 465 */
{
	/*
	:<var> 465 <var> :You are banned from this server.  Mail <var> for more information
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_YOUWILLBEBANNED(  message_irc *message  )            /* 466 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_KEYSET(  message_irc *message  )             /* 467 */
{
	/*
	:<var> 467 <var> <var> :Channel key already set
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_ONLYSERVERSCANCHANGE(  message_irc *message  )               /* 468 */
{
	/*
	:<var> 468 <var> <var> :Only servers can change that mode
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_LINKSET(  message_irc *message  )            /* 469 */
{
	/*
	:<var> 469 <var> <var> :Channel link already set
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_LINKCHANNEL(  message_irc *message  )                /* 470 */
{
	/*
	:<var> 470 <var> [Link] <var> has become full, so you are automatically being transferred to the linked channel <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CHANNELISFULL(  message_irc *message  )              /* 471 */
{
	/*
	:<var> 471 <var> <var> :Cannot join channel (+l)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_UNKNOWNMODE(  message_irc *message  )                /* 472 */
{
	/*
	:<var> 472 <var> <var> :is unknown mode char to me
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_INVITEONLYCHAN(  message_irc *message  )             /* 473 */
{
	/*
	:<var> 473 <var> <var> :Cannot join channel (+i)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_BANNEDFROMCHAN(  message_irc *message  )             /* 474 */
{
	/*
	:<var> 474 <var> <var> :Cannot join channel (+b)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_BADCHANNELKEY(  message_irc *message  )              /* 475 */
{
	/*
	:<var> 475 <var> <var> :Cannot join channel (+k)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_BADCHANMASK(  message_irc *message  )                /* 476 */
{
	/*
	:<var> 476 <var> <var> :Bad Channel Mask
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NEEDREGGEDNICK(  message_irc *message  )             /* 477 */
{
	/*
	:<var> 477 <var> <var> :You need a registered nick to join that channel.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_BANLISTFULL(  message_irc *message  )                /* 478 */
{
	/*
	:<var> 478 <var> <var> <var> :Channel ban/ignore list is full
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_LINKFAIL(  message_irc *message  )           /* 479 */
{
	/*
	:<var> 479 <var> <var> :Sorry, the channel has an invalid channel link set.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CANNOTKNOCK(  message_irc *message  )                /* 480 */
{
	/*
	:<var> 480 <var> :Cannot knock on <var> (<var>)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOPRIVILEGES(  message_irc *message  )               /* 481 */
{
	/*
	:<var> 481 <var> :Permission Denied- You do not have the correct IRC operator privileges
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CHANOPRIVSNEEDED(  message_irc *message  )           /* 482 */
{
	/*
	:<var> 482 <var> <var> :You're not channel operator
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CANTKILLSERVER(  message_irc *message  )             /* 483 */
{
	/*
	:<var> 483 <var> :You cant kill a server!
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_ATTACKDENY(  message_irc *message  )         /* 484 */
{
	/*
	:<var> 484 <var> <var> :Cannot kick protected user <var>.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_KILLDENY(  message_irc *message  )           /* 485 */
{
	/*
	:<var> 485 <var> :Cannot kill protected user <var>.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NONONREG(  message_irc *message  )           /* 486 */
{
	/*
	:<var> 486 <var> :You must identify to a registered nick to private message <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOTFORUSERS(  message_irc *message  )                /* 487 */
{
	/*
	:<var> 487 <var> :<var> is a server only command
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_HTMDISABLED(  message_irc *message  )                /* 488 */
{
	/*
	:<var> 488 <var> :<var> is currently disabled, please try again later.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_SECUREONLYCHAN(  message_irc *message  )             /* 489 */
{
	/*
	:<var> 489 <var> <var> :Cannot join channel (SSL is required)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOSWEAR(  message_irc *message  )            /* 490 */
{
	/*
	:<var> 490 <var> :<var> does not accept private messages containing swearing.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOOPERHOST(  message_irc *message  )         /* 491 */
{
	/*
	:<var> 491 <var> :No O-lines for your host
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOCTCP(  message_irc *message  )             /* 492 */
{
	/*
	:<var> 492 <var> :<var> does not accept CTCPs
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CHANOWNPRIVNEEDED(  message_irc *message  )          /* 499 */
{
	/*
	:<var> 499 <var> <var> :You're not a channel owner
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TOOMANYJOINS(  message_irc *message  )               /* 500 */
{
	/*
	:<var> 500 <var> <var> :Too many join requests. Please wait a while and try again.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_UMODEUNKNOWNFLAG(  message_irc *message  )           /* 501 */
{
	/*
	:<var> 501 <var> :Unknown MODE flag
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_USERSDONTMATCH(  message_irc *message  )             /* 502 */
{
	/*
	:<var> 502 <var> :Cant change mode for other users
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_SILELISTFULL(  message_irc *message  )               /* 511 */
{
	/*
	:<var> 511 <var> <var> :Your silence list is full
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TOOMANYWATCH(  message_irc *message  )               /* 512 */
{
	/*
	:<var> 512 <var> <var> :Maximum size for WATCH-list is 128 entries
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NEEDPONG(  message_irc *message  )           /* 513 */
{
	/*
	:<var> 513 <var> :To connect, type /QUOTE PONG <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_TOOMANYDCC(  message_irc *message  )         /* 514 */
{
	/*
	:<var> 514 <var> <var> :Your dcc allow list is full. Maximum size is <var> entries
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_DISABLED(  message_irc *message  )           /* 517 */
{
	/*
	:<var> 517 <var> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NOINVITE(  message_irc *message  )           /* 518 */
{
	/*
	:<var> 518 <var> :Cannot invite (+V) at channel <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_ADMONLY(  message_irc *message  )            /* 519 */
{
	/*
	:<var> 519 <var> :Cannot join channel <var> (Admin only)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_OPERONLY(  message_irc *message  )           /* 520 */
{
	/*
	:<var> 520 <var> :Cannot join channel <var> (IRCops only)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_LISTSYNTAX(  message_irc *message  )         /* 521 */
{
	/*
	:<var> 521 <var> :Bad list syntax, type /quote list ? or /raw list ?
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NONE(  message_irc *message  )               /* 300 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_AWAY(  message_irc *message  )               /* 301 */
{
	/*
	:<var> 301 <var> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_USERHOST(  message_irc *message  )           /* 302 */
{
	/*
	:<var> 302 <var> :<var> <var> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ISON(  message_irc *message  )               /* 303 */
{
	/*
	":<var> 303 <var> :(option)"
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TEXT(  message_irc *message  )               /* 304 */
{
	/*
	:<source> 304 <nick> :<char> <char> <badword> <censored>
	*/
}
void p_RPL_UNAWAY(  message_irc *message  )             /* 305 */
{
	/*
	:<var> 305 <var> :You are no longer marked as being away
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NOWAWAY(  message_irc *message  )            /* 306 */
{
	/*
	:<var> 306 <var> :You have been marked as being away
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISREGNICK(  message_irc *message  )               /* 307 */
{
	/*
	:<var> 307 <var> <var> :is a registered nick
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_RULESSTART(  message_irc *message  )         /* 308 */
{
	/*
	:<var> 308 <var> :- <var> Server Rules -
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFRULES(  message_irc *message  )         /* 309 */
{
	/*
	:<var> 309 <var> :End of RULES command.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISHELPOP(  message_irc *message  )                /* 310 */
{
	/*
	:<var> 310 <var> <var> :is available for help.
	*/
	fsend_com(":%s 310 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);
}
void p_RPL_WHOISUSER(  message_irc *message  )          /* 311 */
{
	/*
	:<source> 311 <pseudo> <target> <handle> <host> * :<realname>
	*/

	fsend_com(":%s 311 %s %s %s %s * :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->RAW[4],message->RAW[5],message->message);

}
void p_RPL_WHOISSERVER(  message_irc *message  )                /* 312 */
{
	/*
	:<var> 312 <var> <var> <var> :<var>
	*/
	fsend_com(":%s 312 %s %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->RAW[4],message->message);

}
void p_RPL_WHOISOPERATOR(  message_irc *message  )              /* 313 */
{
	/*
	:<var> 313 <var> <var> :is <var>
	*/
	fsend_com(":%s 313 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);

}
void p_RPL_WHOWASUSER(  message_irc *message  )         /* 314 */
{
	/*
	:<var> 314 <var> <var> <var> <var> * :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFWHO(  message_irc *message  )           /* 315 */
{
	/*
	:<var> 315 <var> <var> :End of /WHO list.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}

void p_RPL_ENDOFWHOWAS(  message_irc *message  )                /* 369 */
{
	/*
	:<var> 369 <var> <var> :End of WHOWAS
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISCHANOP(  message_irc *message  )                /* 316 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISIDLE(  message_irc *message  )          /* 317 */
{
	/*
	:<source> 317 <pseudo> <target> <idle> <signon> :seconds idle, signon time
	*/
	fsend_com(":%s 317 %s %s %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->RAW[4],message->RAW[5],message->message);

}
void p_RPL_ENDOFWHOIS(  message_irc *message  )         /* 318 */
{
	/*
	:<var> 318 <var> <var> :End of /WHOIS list.
	*/
	fsend_com(":%s 318 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);
	commandeur = get_user(myconfig->botnick);
}
void p_RPL_WHOISCHANNELS(  message_irc *message  )              /* 319 */
{
	/*
	:<var> 319 <var> <var> :<var>
	*/
	fsend_com(":%s 319 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);

}
void p_RPL_WHOISSPECIAL(  message_irc *message  )               /* 320 */
{
	/*
	:<var> 320 <var> <var> :<var>
	*/
	fsend_com(":%s 320 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);

}
void p_RPL_LISTSTART(  message_irc *message  )          /* 321 */
{
	/*
	:<source> 321 yoyo49 Channel :Users  Name
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LIST(  message_irc *message  )               /* 322 */
{
	/*
	:<source> 322 <nick> <channel> <user count> :<mode> <topic>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LISTEND(  message_irc *message  )            /* 323 */
{
	/*
	:<source> 323 <nick> :End of /LIST
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_CHANNELMODEIS(  message_irc *message  )              /* 324 */
{
	/*
	:<source> 324 <nick> <channel> <mode>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_CREATIONTIME(  message_irc *message  )               /* 329 */
{
	/*
	:<source> 329 <nick> <channel> <time creation>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NOTOPIC(  message_irc *message  )            /* 331 */
{
	/*
	:<source> 331 <nick> <channel> :No topic is set
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TOPIC(  message_irc *message  )              /* 332 */
{
	/*
	:<source> 332 <nick> <channel> :<topic>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TOPICWHOTIME(  message_irc *message  )               /* 333 */
{
	/*
	:<source> 333 <nick> <channel> <nick topic> <date topic>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_INVITELIST(  message_irc *message  )         /* 336 */
{
	/*
	:<var> 336 <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFINVITELIST(  message_irc *message  )            /* 337 */
{
	/*
	:<var> 337 <var> :End of /INVITE list.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LISTSYNTAX(  message_irc *message  )         /* 334 */
{
	/*
	:<var> 334 <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISBOT(  message_irc *message  )           /* 335 */
{
	/*
	:<source> 335 <nick> <target> :is a Bot on irc.ax-proxima.net
	*/
	fsend_com(":%s 335 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);

}
void p_RPL_USERIP(  message_irc *message  )             /* 340 */
{
	/*
	:<source> 340 <nick> :yoyo49*=+yoyo49@213.103.210.85
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_INVITING(  message_irc *message  )           /* 341 */
{
	/*
	:<source> 341 <pseudo> yohan_ #!accueil!
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SUMMONING(  message_irc *message  )          /* 342 */
{
	/*
	:<source> 342 <pseudo> <var> :User summoned to irc
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_VERSION(  message_irc *message  )            /* 351 */
{
	/*
	:<source> 351 <pseudo> <var>.<var> <var> :<var><var><var> [<var>=<var>]
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOREPLY(  message_irc *message  )           /* 352 */
{
	/*
	 :<source> 352 <pseudo> <channel> <handle> <host> <server> <nick> H*(+|%|@) :<realname>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
}
void p_RPL_NAMREPLY(  message_irc *message  )           /* 353 */
{
	/*
	:<source> 353 <pseudo> = <channel> :<(@|+|%|)nick> <(@|+|%|)nick> ...
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
}
void p_RPL_ENDOFNAMES(  message_irc *message  )         /* 366 */
{
	/*
	:<source> 366 <pseudo> <var> :End of /NAMES list.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_INVEXLIST(  message_irc *message  )          /* 346 */
{
	/*
	:<source> 346 <pseudo> <var> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFINVEXLIST(  message_irc *message  )             /* 347 */
{
	/*
	:<source> 347 <pseudo> <var> :End of Channel Invite List
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_EXLIST(  message_irc *message  )             /* 348 */
{
	/*
	:<source> 348 <pseudo> <var> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFEXLIST(  message_irc *message  )                /* 349 */
{
	/*
	:<source> 349 <pseudo> <var> :End of Channel Exception List
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_KILLDONE(  message_irc *message  )           /* 361 */
{
	/*
		dalnet
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_CLOSING(  message_irc *message  )            /* 362 */
{
	/*
	:<source> 362 <pseudo> <var> :Closed. Status = <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_CLOSEEND(  message_irc *message  )           /* 363 */
{
	/*
	:<source> 363 <pseudo> <var>: Connections Closed
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LINKS(  message_irc *message  )              /* 364 */
{
	/*
	:<source> 364 <pseudo> <var> <var> :<var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFLINKS(  message_irc *message  )         /* 365 */
{
	/*
	:<source> 365 <pseudo> <var> :End of /LINKS list.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_BANLIST(  message_irc *message  )            /* 367 */
{
	/*
	:<source> 367 <pseudo> <channel> <mask> <nick> <timestamp>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFBANLIST(  message_irc *message  )               /* 368 */
{
	/*
	:<source> 368 <pseudo> <var> :End of Channel Ban List
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFWHOWASABOVE(  message_irc *message  )           /* 369 */
{
	/*
	:<source> 369 <pseudo> <var> :End of WHOWAS
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_INFO(  message_irc *message  )               /* 371 */
{
	/*
	:<source> 371 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MOTD(  message_irc *message  )               /* 372 */
{
	/*
	:<source> 372 <pseudo> :- 13/6/2006 10:13
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_INFOSTART(  message_irc *message  )          /* 373 */
{
	/*
	:<source> 373 <pseudo> :Server INFO
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFINFO(  message_irc *message  )          /* 374 */
{
	/*
	:<source> 374 <pseudo> :End of /INFO list.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MOTDSTART(  message_irc *message  )          /* 375 */
{
	/*
	:<source> 375 <pseudo> :- yoyo49.ax-proxima.net Message of the Day -
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFMOTD(  message_irc *message  )          /* 376 */
{
	/*
	:<source> 376 <pseudo> :End of /MOTD command.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISHOST(  message_irc *message  )          /* 378 */
{
	/*
	:<source> 378 <pseudo> <var> :is connecting from *@<var> <ip>
	*/
	fsend_com(":%s 378 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);
}
void p_RPL_WHOISMODES(  message_irc *message  )         /* 379 */
{
	/*
	:<source> 379 <pseudo> <var> :is using modes <var> <var>
	*/
	fsend_com(":%s 379 %s %s :%s\n", myconfig->host,commandeur->nick,message->RAW[3],message->message);
}
void p_RPL_YOUREOPER(  message_irc *message  )          /* 381 */
{
	/*
	:<source> 381 <pseudo> :You are now an IRC Operator
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_REHASHING(  message_irc *message  )          /* 382 */
{
	/*
	:<source> 382 <pseudo> <var> :Rehashing
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_YOURESERVICE(  message_irc *message  )               /* 383 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MYPORTIS(  message_irc *message  )           /* 384 */
{
	/*
	:<source> 384 <pseudo> <var> :Port to local server is
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NOTOPERANYMORE(  message_irc *message  )             /* 385 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_QLIST(  message_irc *message  )              /* 386 */
{
	/*
	:<source> 386 <pseudo> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}

void p_RPL_ENDOFQLIST(  message_irc *message  )         /* 387 */
{
	/*
	:<source> 387 <pseudo> <var> :End of Channel Owner List
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ALIST(  message_irc *message  )              /* 388 */
{
	/*
	:<source> 388 <pseudo> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFALIST(  message_irc *message  )         /* 389 */
{
	/*
	:<source> 389 <pseudo> <var> :End of Protected User List
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TIME(  message_irc *message  )               /* 391 */
{
	/*
	:<source> 391 <pseudo> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_USERSSTART(  message_irc *message  )         /* 392 */
{
	/*
	:<source> 392 <pseudo> :UserID   Terminal  Host
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_USERS(  message_irc *message  )              /* 393 */
{
	/*
	:<source> 393 <pseudo> :<var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFUSERS(  message_irc *message  )         /* 394 */
{
	/*
	:<source> 394 <pseudo> :End of Users
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NOUSERS(  message_irc *message  )            /* 395 */
{
	/*
	:<source> 395 <pseudo> :Nobody logged in.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACELINK(  message_irc *message  )          /* 200 */
{
	/*
	:<source> 200 <pseudo> Link <var><var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACECONNECTING(  message_irc *message  )            /* 201 */
{
	/*
	:<source> 201 <pseudo> Attempt <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}

void p_RPL_TRACEHANDSHAKE(  message_irc *message  )             /* 202 */
{
	/*
	:<source> 202 <pseudo> Handshaking <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACEUNKNOWN(  message_irc *message  )               /* 203 */
{
	/*
	:<source> 203 <pseudo> ???? <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACEOPERATOR(  message_irc *message  )              /* 204 */
{
	/*
	:<source> 204 <pseudo> Operator <var> <var> [<var>] <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACEUSER(  message_irc *message  )          /* 205 */
{
	/*
	:<source> 205 <pseudo> User <var> <var> [<var>] <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACESERVER(  message_irc *message  )                /* 206 */
{
	/*
	:<source> 206 <pseudo> Server <class> <var> <var> <host> <var>!<var>@<var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACESERVICE(  message_irc *message  )               /* 207 */
{
	/*
	:<var> 207 <pseudo> Service <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACENEWTYPE(  message_irc *message  )               /* 208 */
{
	/*
	:<source> 208 <pseudo> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACECLASS(  message_irc *message  )         /* 209 */
{
	/*
	:<source> 209 <pseudo> Class <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSHELP(  message_irc *message  )          /* 210 */
{
	/*
	:<source> 210 <pseudo> :<aide stats>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSLINKINFO(  message_irc *message  )              /* 211 */
{
	/*
	:<source> 211 <pseudo> SendQ SendM SendBytes RcveM RcveBytes Open_since :Idle
	*/
	char buffer[1024];
	sprintf(buffer,"\0034LINKINFO \0031:\0033 %s \0031SendQ :\0033 %s \0031, SendM : \0033 %s \0031, SendBytes : \0033 %s \0031, RcveM : \0033 %s \0031, SRcveBytes : \0033 %s \0031, Open_since : \0033 %s \0031, Idle : \0033 %s", message->RAW[3],message->RAW[4],message->RAW[5],message->RAW[6],message->RAW[7],message->RAW[8],message->RAW[9],message->message);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSCOMMANDS(  message_irc *message  )              /* 212 */
{
	/*
	:<source> 212 <pseudo> <commande> <nsession> <ntotal>
	*/
	char buffer[1024];
	sprintf(buffer,"\0034COMMANDS \0031:\0033 %s \0031session :\0033 %s \0031, total : \0033 %s ", message->RAW[3],message->RAW[4],message->RAW[5]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSCLINE(  message_irc *message  )         /* 213 */
{
	/*
	:<source> 213 <pseudo> C *@* * DeStRuCtOr.ax-proxima.net 4001 servers
	*/
	char buffer[1024];
	sprintf(buffer,"\0034CLINE %s\0031:\0033 %s \0031port :\0033 %s \0031, type : \0033 %s",message->RAW[3],message->RAW[6],message->RAW[7],message->RAW[8]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSOLDNLINE(  message_irc *message  )              /* 214 */
{
	/*
	:<source> 214 <pseudo> <var> <var> * <var> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSILINE(  message_irc *message  )         /* 215 */
{
	/*
	:<source> 215 <pseudo> I *@prodhosting.com * *@* 99 clients irc.ax-proxima.net 6667
	*/
	char buffer[1024];
	sprintf(buffer,"\0034ILINE %s\0031:\0033 %s ",message->RAW[3],message->RAW[4]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSKLINE(  message_irc *message  )         /* 216 */
{
	/*
	:<source> 216 <pseudo> K <mask> <motif>
	:<source> 216 <pseudo> E <mask>
	:<source> 216 <pseudo> Z <mask>
	*/
	char buffer[1024];
	sprintf(buffer,"\0034KLINE %s\0031:\0033 %s",message->RAW[3],message->RAW[4]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSQLINE(  message_irc *message  )         /* 217 */
{
	/*
	:<source> 217 <pseudo> q <mask> <expire> <timestamp> <server> :<motif>
	*/
	char buffer[1024];
	sprintf(buffer,"\0034QLINE %s\0031:\0033 %s",message->RAW[3],message->RAW[4]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSYLINE(  message_irc *message  )         /* 218 */
{
	/*
	:<source> 218 <pseudo> Y servers 90 100 10 1000000 8000
	*/
	char buffer[1024];
	sprintf(buffer,"\0034YLINE %s\0031:\0033 %s %s %s %s %s %s", message->RAW[3],message->RAW[4],message->RAW[5],message->RAW[6],message->RAW[7],message->RAW[8],message->RAW[9]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_ENDOFSTATS(  message_irc *message  )         /* 219 */
{
	/*
	:<source> 210 <pseudo> * :End of /STATS report
	*/

	//extern ComAction *comAction;
	char title[100];
	char c = '\0';

	c = *message->RAW[3];
	switch(c)
	{
		case 'B':sprintf(title,"****** Fin des banversion    ******");break;
		case 'b':sprintf(title,"****** Fin des badword    ******");break;
		case 'C':sprintf(title,"****** Fin des link    ******");break;
		case 'd':sprintf(title,"****** Fin des denylinkauto    ******");break;
		case 'D':sprintf(title,"****** Fin des denylinkall    ******");break;
		case 'e':sprintf(title,"****** Fin des exceptthrottle    ******");break;
		case 'E':sprintf(title,"****** Fin des exceptban    ******");break;
		case 'f':sprintf(title,"****** Fin des spamfilter    ******");break;
		case 'F':sprintf(title,"****** Fin des denydcc    ******");break;
		case 'G':sprintf(title,"****** Fin des gline    ******");break;
		case 'I':sprintf(title,"****** Fin des allow    ******");break;
		case 'j':sprintf(title,"****** Fin des officialchans    ******");break;
		case 'K':sprintf(title,"****** Fin des kline    ******");break;
		case 'l':sprintf(title,"****** Fin des linkinfo    ******");break;
		case 'L':sprintf(title,"****** Fin des linkinfoall    ******");break;
		case 'M':sprintf(title,"****** Fin des command    ******");break;
		case 'n':sprintf(title,"****** Fin des banrealname    ******");break;
		case 'O':sprintf(title,"****** Fin des oper    ******");break;
		case 'P':sprintf(title,"****** Fin des port    ******");break;
		case 'q':sprintf(title,"****** Fin des bannick    ******");break;
		case 'Q':sprintf(title,"****** Fin des sqline    ******");break;
		case 'r':sprintf(title,"****** Fin des chanrestrict    ******");break;
		case 'S':sprintf(title,"****** Fin des set    ******");break;
		case 's':sprintf(title,"****** Fin des shun    ******");break;
		case 't':sprintf(title,"****** Fin des tld    ******");break;
		case 'T':sprintf(title,"****** Fin des traffic    ******");break;
		case 'u':sprintf(title,"****** Fin des uptime    ******");break;
		case 'U':sprintf(title,"****** Fin des uline    ******");break;
		case 'v':sprintf(title,"****** Fin des denyver    ******");break;
		case 'V':sprintf(title,"****** Fin des vhost    ******");break;
		case 'X':sprintf(title,"****** Fin des notlink    ******");break;
		case 'Y':sprintf(title,"****** Fin des class    ******");break;
		case 'Z':sprintf(title,"****** Fin des memory    ******");break;
	}

	if(commandeur->nick)
		fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,title);

	commandeur = get_user(myconfig->botnick);
	//_strcpy(comAction->action,"NULL",sizeof(comAction->action));
}

void p_RPL_STATSBLINE(  message_irc *message  )         /* 220 */
{
	/*
	:<source> 220 <pseudo> <var> <var> <var> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_UMODEIS(  message_irc *message  )            /* 221 */
{
	/*
	:<source> 221 <pseudo> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SQLINE_NICK(  message_irc *message  )        /* 222 */
{
	/*
	:<source> 222 <pseudo> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSGLINE(  message_irc *message  )         /* 223 */
{
	/*
	:<source> 223 <pseudo> G <mask> <expire> <timestamp> <host poser> :<motif>
	*/

	char buffer[1024];
	//extern ComAction *comAction;

	if(strcmp(comAction->action,"CLEAR") == 0)
	{
		fsend_com(COM_OPER_GLINE_REM,myconfig->botnick,message->RAW[4]);
	}

	if(strcmp(comAction->action,"CLEAR") != 0)
	{
		if(atoi(message->RAW[5]) == 0)
		{
			sprintf(buffer,"\0034GLINE %s\0031:\0033 %s \0031expire\0031 jamais",message->RAW[3],message->RAW[4]);
		}
		else
		{
			sprintf(buffer,"\0034Gline %s\0031:\0033 %s \0031expire le :\0031 %s", message->RAW[3], message->RAW[4],time_fr(atol(message->RAW[5])));
		}
		fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
	}
}

void p_RPL_STATSTLINE(  message_irc *message  )         /* 224 */
{
	/*
	:<source> 224 <nick> T *@* ircd.motd.fr ircd.rules.fr
	*/

	char buffer[1024];

	int i = 5;

	sprintf(buffer,"\0034TLINE %s\0031:\0033 %s",message->RAW[3],message->RAW[4]);
	while(message->RAW[i] != NULL)
	{
		strcat(buffer," ");
		strcat(buffer,message->RAW[i++]);
	}
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}

void p_RPL_STATSELINE(  message_irc *message  )         /* 225 */
{
	/*
	:<source> 225 <nick> e <mask>
	*/

	char buffer[1024];

	sprintf(buffer,"\0034ELINE %s\0031:\0033 %s",message->RAW[3],message->RAW[4]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSNLINE(  message_irc *message  )         /* 226 */
{
	/*
	:<source> 226 <pseudo> n sub7server sub7
	*/

	char buffer[1024];

	int i = 5;

	sprintf(buffer,"\0034NLINE %s\0031:\0033 %s",message->RAW[3],message->RAW[4]);
	while(message->RAW[i] != NULL)
	{
		strcat(buffer," ");
		strcat(buffer,message->RAW[i++]);
	}
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSVLINE(  message_irc *message  )         /* 227 */
{
	/*
	:<source> 227 <pseudo> v <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSBANVER(  message_irc *message  )                /* 228 */
{
	/*
	:<source> 228 <pseudo> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSSPAMF(  message_irc *message  )         /* 229 */
{
	/*
	:<source> 229 <pseudo> f c gline 0 74752 86400 Attempting_to_login_to_a_GTBot yoyo49.ax-proxima.net :^!login Wasszup!$
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSEXCEPTTKL(  message_irc *message  )             /* 230 */
{
	/*
	:<source> 230 <pseudo> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SERVICEINFO(  message_irc *message  )                /* 231 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_RULES(  message_irc *message  )              /* 232 */
{
	/*
	:<source> 232 <pseudo> :- <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SERVICE(  message_irc *message  )            /* 233 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SERVLIST(  message_irc *message  )           /* 234 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SERVLISTEND(  message_irc *message  )                /* 235 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}

void p_RPL_STATSLLINE(  message_irc *message  )         /* 241 */
{
	/*
	:<source> 241 <pseudo> <var> <var> * <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSUPTIME(  message_irc *message  )                /* 242 */
{
	/*
	:<source> 242 <pseudo> :Server Up 0 days, 22:15:39
	*/
	char buffer[1024];
	sprintf(buffer,"\0034UPTIME \0031:\0033 %s",message->message);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSOLINE(  message_irc *message  )         /* 243 */
{
	/*
	:<source> 243 <pseudo> O * * <nick> rhgwlcLkKbBnGCzWHtvd clients
	*/
	char buffer[1024];
	sprintf(buffer,"\0034OLINE %s\0031:\0033 %s",message->RAW[3],message->RAW[6]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSHLINE(  message_irc *message  )         /* 244 */
{
	/*
	:<source> 244 <pseudo> <flag> * * <host>
	*/
	char buffer[1024];
	sprintf(buffer,"\0034HLINE %s\0031:\0033 %s",message->RAW[3],message->RAW[6]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSSLINE(  message_irc *message  )         /* 245 */
{
	/*
	:<source> 245 <pseudo> <var> <var> * <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSXLINE(  message_irc *message  )         /* 247 */
{
	/*
	:<source> 247 <pseudo> X DeStRuCtOr.ax-proxima.net 4001
	*/
	char buffer[1024];
	sprintf(buffer,"\0034XLINE %s\0031:\0033 %s \0031sur le port\0033 %s", message->RAW[3],message->RAW[4],message->RAW[5]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSULINE(  message_irc *message  )         /* 248 */
{
	/*
	:<source> 248 <pseudo> U <host>
	*/
	char buffer[1024];
	sprintf(buffer,"\0034ULINE %s\0031:\0033 %s",message->RAW[3],message->RAW[4]);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSDEBUG(  message_irc *message  )         /* 249 */
{
	/*
	:<source> 249 <pseudo> :accepts 22 refused 0
	*/
	char buffer[1024];
	sprintf(buffer,"\0034DEBUG \0031:\0033 %s",message->message);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_STATSCONN(  message_irc *message  )          /* 250 */
{
	/*
	:<source> 250 <pseudo> :Highest connection count: 2 (4 clients)
	*/
	char buffer[1024];
	sprintf(buffer,"\0034CONN \0031:\0033 %s",message->message);
	fsend_com(LINK_COM_USER_NOTICE,myconfig->botnick,commandeur->nick,buffer);
}
void p_RPL_LUSERCLIENT(  message_irc *message  )                /* 251 */
{
	/*
	:<source> 251 <pseudo> :There are 1 users and 2 invisible on 1 servers
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LUSEROP(  message_irc *message  )            /* 252 */
{
	/*
	:<source> 252 <pseudo> 2 :operator(s) online
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LUSERUNKNOWN(  message_irc *message  )               /* 253 */
{
	/*
	:<source> 253 <pseudo> -1 :unknown connection(s)
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LUSERCHANNELS(  message_irc *message  )              /* 254 */
{
	/*
	:<source> 254 <pseudo> 3 :channels formed
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LUSERME(  message_irc *message  )            /* 255 */
{
	/*
	:<source> 255 <pseudo> :I have 3 clients and 0 servers
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ADMINME(  message_irc *message  )            /* 256 */
{
	/*
	:<source> 256 <pseudo> :Administrative info about <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ADMINLOC1(  message_irc *message  )           /* 257 */
{
	/*
	:<source> 257 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ADMINLOC2(  message_irc *message  )           /* 258 */
{
	/*
	:<source> 258 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ADMINEMAIL(  message_irc *message  )         /* 259 */
{
	/*
	:<source> 259 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_TRACELOG(  message_irc *message  )           /* 261 */
{
	/*
	:<source> 261 <pseudo> File <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LOCALUSERS(  message_irc *message  )         /* 265 */
{
	/*
	:<source> 265 <pseudo> :Current Local Users: 3  Max: 4
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_GLOBALUSERS(  message_irc *message  )                /* 266 */
{
	/*
	:<source> 266 <pseudo> :Current Global Users: 3  Max: 8
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SILELIST(  message_irc *message  )           /* 271 */
{
	/*
	:<source> 271 <pseudo> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFSILELIST(  message_irc *message  )              /* 272 */
{
	/*
	:<source> 272 <pseudo> :End of Silence List
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_STATSDLINE(  message_irc *message  )         /* 275 */
{
	/*
	:<source> 275 <pseudo> <var> <var> <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_HELPHDR(  message_irc *message  )            /* 290 */
{
	/*
	:<source> 290 <pseudo> :<text>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_HELPOP(  message_irc *message  )             /* 291 */
{
	/*
		dalnet
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_HELPTLR(  message_irc *message  )            /* 292 */
{
	/*
	:<source> 292 <pseudo> :<text>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_HELPHLP(  message_irc *message  )            /* 293 */
{
	/*
		dalnet
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_HELPFWD(  message_irc *message  )            /* 294 */
{
	/*
	:<source> 294 <pseudo> :Your help-request has been forwarded to Help Operators
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_HELPIGN(  message_irc *message  )            /* 295 */
{
	/*
	:<source> 295 <pseudo> :Your address has been ignored from forwarding
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MAP(  message_irc *message  )                /* 006 */
{
	/*
	:<source> 006 <pseudo> :%s%-*s(%ld)  %s
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MAPMORE(  message_irc *message  )            /* 610 */
{
	/*
	:<source> 610 <pseudo> :<var><var> --> *more*
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_MAPEND(  message_irc *message  )             /* 007 */
{
	/*
	:<source> 007 <pseudo> :End of /MAP
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_WHOSYNTAX(  message_irc *message  )          /* 522 */
{
	/*
	:<source> 522 <pseudo> :/WHO Syntax incorrect, use /who ? for help
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_WHOLIMEXCEED(  message_irc *message  )               /* 523 */
{
	/*
	:<source> 523 <pseudo> :Error, /who limit of <var> exceeded. Please narrow your search down and try again
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_OPERSPVERIFY(  message_irc *message  )               /* 524 */
{
	/*
	:<source> 524 <pseudo> :Trying to join +s or +p channel as an oper. Please invite yourself first.
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SNOMASK(  message_irc *message  )            /* 008 */
{
	/*
	":<source> 008 <pseudo> :Server notice mask (%s)"
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LOGON(  message_irc *message  )              /* 600 */
{
	/*
	:<source> 600 <pseudo> <var> <var> <var> <var> :logged online
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_LOGOFF(  message_irc *message  )             /* 601 */
{
	/*
	:<source> 601 <pseudo> <var> <var> <var> <var> :logged offline
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WATCHOFF(  message_irc *message  )           /* 602 */
{
	/*
	:<source> 602 <pseudo> <var> <var> <var> <var> :stopped watching
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WATCHSTAT(  message_irc *message  )          /* 603 */
{
	/*
	:<source> 603 <pseudo> :You have <var> and are on <var> WATCH entries
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NOWON(  message_irc *message  )              /* 604 */
{
	/*
	:<source> 604 <pseudo> <var> <var> <var> <var> :is online
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_NOWOFF(  message_irc *message  )             /* 605 */
{
	/*
	:<source> 605 <pseudo> <var> <var> <var> <var> :is offline
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WATCHLIST(  message_irc *message  )          /* 606 */
{
	/*
	:<source> 606 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFWATCHLIST(  message_irc *message  )             /* 607 */
{
	/*
	:<source> 607 <pseudo> :End of WATCH <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_DCCSTATUS(  message_irc *message  )          /* 617 */
{
	/*
	:<source> 617 <pseudo> :<var> has been <var> your DCC allow list
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_DCCLIST(  message_irc *message  )            /* 618 */
{
	/*
	:<source> 618 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_ENDOFDCCLIST(  message_irc *message  )               /* 619 */
{
	/*
	:<source> 619 <pseudo> :End of DCCALLOW <var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_DCCINFO(  message_irc *message  )            /* 620 */
{
	/*
	:<source> 620 <pseudo> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_DUMPING(  message_irc *message  )            /* 640 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_DUMPRPL(  message_irc *message  )            /* 641 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_EODUMP(  message_irc *message  )             /* 642 */
{
	/*

	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_SPAMCMDFWD(  message_irc *message  )         /* 659 */
{
	/*
	:<source> 659 <pseudo> <var> :Command processed, but a copy has been sent to ircops for evaluation (anti-spam) purposes. [<var>]
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_RPL_WHOISSECURE(  message_irc *message  )                /* 671 */
{
	/*
	:<source> 671 <pseudo> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CANNOTDOCOMMAND(  message_irc *message  )            /* 972 */
{
	/*
	:<source> 972 <pseudo> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_CANNOTCHANGECHANMODE(  message_irc *message  )               /* 974 */
{
	/*
	:<source> 974 <pseudo> <var> :<var>
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}
void p_ERR_NUMERICERR(  message_irc *message  )         /* 999 */
{
	/*
	:<source> 999 <pseudo> Numeric error!
	*/
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	return;
}


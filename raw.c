
#include "main.h"

/**
	Gestion de Raw de gestion

	les raws de gestion sont les raws sevant a la gestion des users et des channels
**/


Raw_IN_Gestion *pRaw_IN_Gestion = NULL;

Raw_IN_Gestion *Create_Raw_Gestion( char *name , myFuncRawPtr func)
{
	Raw_IN_Gestion *nRaw;
	nRaw = (Raw_IN_Gestion*)malloc(sizeof(Raw_IN_Gestion));
	STRDUP(nRaw->rawName,name);
	nRaw->func = func;

	/* mise en liste doublement chainee */
	nRaw->precedent = NULL;
	nRaw->suivant = pRaw_IN_Gestion;
	if (pRaw_IN_Gestion)
    	pRaw_IN_Gestion->precedent = nRaw;
	pRaw_IN_Gestion = nRaw;

	/* return le Raw_IN nouvellement crée */
	return pRaw_IN_Gestion;
}

int clear_Raw_Gestion()
{
	Raw_IN_Gestion *nRaw;
	while (pRaw_IN_Gestion)
	{
		nRaw = pRaw_IN_Gestion;
		pRaw_IN_Gestion = pRaw_IN_Gestion->suivant;
		FREE(nRaw->rawName);
		FREE(nRaw);
		nRaw = NULL;
	}
	pRaw_IN_Gestion = NULL;
	return 1;
}

long Raw_IN_t_Gestion()
{
	int count = 0;

	Raw_IN_Gestion *nRaw;
	nRaw = pRaw_IN_Gestion;
	while (nRaw)
	{
		count++;
		nRaw = nRaw->suivant;
	}
	return sizeof(Raw_IN_Gestion) * (count+1);
}

/*
	void de declaration des raws
*/
void init_Raw_Gestion( void )
{

	Create_Raw_Gestion("CONNECT"	,&p_MSG_CONNECT); //fini
	Create_Raw_Gestion("PASS"  		,&p_MSG_PASS); //fini
	Create_Raw_Gestion("SERVER"  	,&p_MSG_SERVER); //fini
	Create_Raw_Gestion("NETINFO"  	,&p_MSG_NETINFO); //fini
	Create_Raw_Gestion("PROTOCTL"  	,&p_MSG_PROTOCTL); //fini
	Create_Raw_Gestion("EOS"  		,&p_MSG_EOS); //fini
	Create_Raw_Gestion("TKL"  		,&p_MSG_TKL); //fini
	Create_Raw_Gestion("CHGHOST"  	,&p_MSG_CHGHOST); //fini
	Create_Raw_Gestion("CHGIDENT"  	,&p_MSG_CHGIDENT); //fini
	Create_Raw_Gestion("CHGNAME"  	,&p_MSG_CHGNAME); //fini
	Create_Raw_Gestion("SETHOST"  	,&p_MSG_SETHOST); //fini
	Create_Raw_Gestion("SETIDENT"  	,&p_MSG_SETIDENT); //fini
	Create_Raw_Gestion("SETNAME"  	,&p_MSG_SETNAME); //fini
	Create_Raw_Gestion("TOPIC"  	,&p_MSG_TOPIC); //fini
	Create_Raw_Gestion("AWAY"  		,&p_MSG_AWAY); //fini
	Create_Raw_Gestion("INVITE"  	,&p_MSG_INVITE); //fini
	Create_Raw_Gestion("KILL"  		,&p_MSG_KILL); //fini
	Create_Raw_Gestion("WALLOPS"  	,&p_MSG_WALLOPS); //fini
	Create_Raw_Gestion("WHOIS"  	,&p_MSG_WHOIS); //fini
	Create_Raw_Gestion("GLOBOPS"  	,&p_MSG_GLOBOPS); //fini
	Create_Raw_Gestion("SMO"  		,&p_MSG_SMO); //fini
	Create_Raw_Gestion("NACHAT"  	,&p_MSG_NACHAT); //fini
	Create_Raw_Gestion("CHATOPS"  	,&p_MSG_CHATOPS); //fini
	Create_Raw_Gestion("ADCHAT"  	,&p_MSG_ADCHAT); //fini
	Create_Raw_Gestion("SENDNO"  	,&p_MSG_ADCHAT); //fini
	Create_Raw_Gestion("PRIVMSG"  	,&p_MSG_PRIVMSG); //fini
	Create_Raw_Gestion("JOIN"  		,&p_MSG_JOIN); //fini
	Create_Raw_Gestion("PART"  		,&p_MSG_PART); //fini
	Create_Raw_Gestion("NOTICE"  	,&p_MSG_NOTICE); //fini
	Create_Raw_Gestion("MODE"  		,&p_MSG_MODE); //fini
	Create_Raw_Gestion("NICK"  		,&p_MSG_NICK); //fini
	Create_Raw_Gestion("KICK"  		,&p_MSG_KICK); //fini
	Create_Raw_Gestion("QUIT"  		,&p_MSG_QUIT); //fini
	Create_Raw_Gestion("ERROR"  	,&p_MSG_ERROR); //fini
	Create_Raw_Gestion("PING"  		,&p_MSG_PING); //fini

	//Create_Raw_Gestion("001"  	,&p_RPL_WELCOME);
	//Create_Raw_Gestion("002"  	,&p_RPL_YOURHOST);
	//Create_Raw_Gestion("003"  	,&p_RPL_CREATED);
	//Create_Raw_Gestion("004"  	,&p_RPL_MYINFO);
	//Create_Raw_Gestion("005"  	,&p_RPL_ISUPPORT);
	//Create_Raw_Gestion("010"  	,&p_RPL_REDIR);
	//Create_Raw_Gestion("105"  	,&p_RPL_REMOTEISUPPORT);
	//Create_Raw_Gestion("401"  	,&p_ERR_NOSUCHNICK);
	//Create_Raw_Gestion("402"  	,&p_ERR_NOSUCHSERVER);
	//Create_Raw_Gestion("403"  	,&p_ERR_NOSUCHCHANNEL);
	//Create_Raw_Gestion("404"  	,&p_ERR_CANNOTSENDTOCHAN);
	//Create_Raw_Gestion("405"  	,&p_ERR_TOOMANYCHANNELS);
	//Create_Raw_Gestion("406"  	,&p_ERR_WASNOSUCHNICK);
	//Create_Raw_Gestion("407"  	,&p_ERR_TOOMANYTARGETS);
	//Create_Raw_Gestion("408"  	,&p_ERR_NOSUCHSERVICE);
	//Create_Raw_Gestion("409"  	,&p_ERR_NOORIGIN);
	//Create_Raw_Gestion("411"  	,&p_ERR_NORECIPIENT);
	//Create_Raw_Gestion("412"  	,&p_ERR_NOTEXTTOSEND);
	//Create_Raw_Gestion("413"  	,&p_ERR_NOTOPLEVEL);
	//Create_Raw_Gestion("414"  	,&p_ERR_WILDTOPLEVEL);
	//Create_Raw_Gestion("421"  	,&p_ERR_UNKNOWNCOMMAND);
	//Create_Raw_Gestion("422"  	,&p_ERR_NOMOTD);
	//Create_Raw_Gestion("423"  	,&p_ERR_NOADMININFO);
	//Create_Raw_Gestion("424"  	,&p_ERR_FILEERROR);
	//Create_Raw_Gestion("425"  	,&p_ERR_NOOPERMOTD);
	//Create_Raw_Gestion("429"  	,&p_ERR_TOOMANYAWAY);
	//Create_Raw_Gestion("431"  	,&p_ERR_NONICKNAMEGIVEN);
	//Create_Raw_Gestion("432"  	,&p_ERR_ERRONEUSNICKNAME);
	//Create_Raw_Gestion("433"  	,&p_ERR_NICKNAMEINUSE);
	//Create_Raw_Gestion("434"  	,&p_ERR_NORULES);
	//Create_Raw_Gestion("435"  	,&p_ERR_SERVICECONFUSED);
	//Create_Raw_Gestion("436"  	,&p_ERR_NICKCOLLISION);
	//Create_Raw_Gestion("437"  	,&p_ERR_BANNICKCHANGE);
	//Create_Raw_Gestion("438"  	,&p_ERR_NCHANGETOOFAST);
	//Create_Raw_Gestion("439"  	,&p_ERR_TARGETTOOFAST);
	//Create_Raw_Gestion("440"  	,&p_ERR_SERVICESDOWN);
	//Create_Raw_Gestion("441"  	,&p_ERR_USERNOTINCHANNEL);
	//Create_Raw_Gestion("442"  	,&p_ERR_NOTONCHANNEL);
	//Create_Raw_Gestion("443"  	,&p_ERR_USERONCHANNEL);
	//Create_Raw_Gestion("444"  	,&p_ERR_NOLOGIN);
	//Create_Raw_Gestion("445"  	,&p_ERR_SUMMONDISABLED);
	//Create_Raw_Gestion("446"  	,&p_ERR_USERSDISABLED);
	//Create_Raw_Gestion("447"  	,&p_ERR_NONICKCHANGE);
	//Create_Raw_Gestion("451"  	,&p_ERR_NOTREGISTERED);
	//Create_Raw_Gestion("455"  	,&p_ERR_HOSTILENAME);
	//Create_Raw_Gestion("459"  	,&p_ERR_NOHIDING);
	//Create_Raw_Gestion("460"  	,&p_ERR_NOTFORHALFOPS);
	//Create_Raw_Gestion("461"  	,&p_ERR_NEEDMOREPARAMS);
	//Create_Raw_Gestion("462"  	,&p_ERR_ALREADYREGISTRED);
	//Create_Raw_Gestion("463"  	,&p_ERR_NOPERMFORHOST);
	//Create_Raw_Gestion("464"  	,&p_ERR_PASSWDMISMATCH);
	//Create_Raw_Gestion("465"  	,&p_ERR_YOUREBANNEDCREEP);
	//Create_Raw_Gestion("466"  	,&p_ERR_YOUWILLBEBANNED);
	//Create_Raw_Gestion("467"  	,&p_ERR_KEYSET);
	//Create_Raw_Gestion("468"  	,&p_ERR_ONLYSERVERSCANCHANGE);
	//Create_Raw_Gestion("469"  	,&p_ERR_LINKSET);
	//Create_Raw_Gestion("470"  	,&p_ERR_LINKCHANNEL);
	//Create_Raw_Gestion("471"  	,&p_ERR_CHANNELISFULL);
	//Create_Raw_Gestion("472"  	,&p_ERR_UNKNOWNMODE);
	//Create_Raw_Gestion("473"  	,&p_ERR_INVITEONLYCHAN);
	//Create_Raw_Gestion("474"  	,&p_ERR_BANNEDFROMCHAN);
	//Create_Raw_Gestion("475"  	,&p_ERR_BADCHANNELKEY);
	//Create_Raw_Gestion("476"  	,&p_ERR_BADCHANMASK);
	//Create_Raw_Gestion("477"  	,&p_ERR_NEEDREGGEDNICK);
	//Create_Raw_Gestion("478"  	,&p_ERR_BANLISTFULL);
	//Create_Raw_Gestion("479"  	,&p_ERR_LINKFAIL);
	//Create_Raw_Gestion("480"  	,&p_ERR_CANNOTKNOCK);
	//Create_Raw_Gestion("481"  	,&p_ERR_NOPRIVILEGES);
	//Create_Raw_Gestion("482"  	,&p_ERR_CHANOPRIVSNEEDED);
	//Create_Raw_Gestion("483"  	,&p_ERR_CANTKILLSERVER);
	//Create_Raw_Gestion("484"  	,&p_ERR_ATTACKDENY);
	//Create_Raw_Gestion("485"  	,&p_ERR_KILLDENY);
	//Create_Raw_Gestion("486"  	,&p_ERR_NONONREG);
	//Create_Raw_Gestion("487"  	,&p_ERR_NOTFORUSERS);
	//Create_Raw_Gestion("488"  	,&p_ERR_HTMDISABLED);
	//Create_Raw_Gestion("489"  	,&p_ERR_SECUREONLYCHAN);
	//Create_Raw_Gestion("490"  	,&p_ERR_NOSWEAR);
	//Create_Raw_Gestion("491"  	,&p_ERR_NOOPERHOST);
	//Create_Raw_Gestion("492"  	,&p_ERR_NOCTCP);
	//Create_Raw_Gestion("499"  	,&p_ERR_CHANOWNPRIVNEEDED);
	//Create_Raw_Gestion("500"  	,&p_ERR_TOOMANYJOINS);
	//Create_Raw_Gestion("501"  	,&p_ERR_UMODEUNKNOWNFLAG);
	//Create_Raw_Gestion("502"  	,&p_ERR_USERSDONTMATCH);
	//Create_Raw_Gestion("511"  	,&p_ERR_SILELISTFULL);
	//Create_Raw_Gestion("512"  	,&p_ERR_TOOMANYWATCH);
	//Create_Raw_Gestion("513"  	,&p_ERR_NEEDPONG);
	//Create_Raw_Gestion("514"  	,&p_ERR_TOOMANYDCC);
	//Create_Raw_Gestion("517"  	,&p_ERR_DISABLED);
	//Create_Raw_Gestion("518"  	,&p_ERR_NOINVITE);
	//Create_Raw_Gestion("519"  	,&p_ERR_ADMONLY);
	//Create_Raw_Gestion("520"  	,&p_ERR_OPERONLY);
	//Create_Raw_Gestion("521"  	,&p_ERR_LISTSYNTAX);
	//Create_Raw_Gestion("300"  	,&p_RPL_NONE);
	//Create_Raw_Gestion("301"  	,&p_RPL_AWAY);
	//Create_Raw_Gestion("302"  	,&p_RPL_USERHOST);
	//Create_Raw_Gestion("303"  	,&p_RPL_ISON);
	//Create_Raw_Gestion("304"  	,&p_RPL_TEXT);
	//Create_Raw_Gestion("305"  	,&p_RPL_UNAWAY);
	//Create_Raw_Gestion("306"  	,&p_RPL_NOWAWAY);
	//Create_Raw_Gestion("307"  	,&p_RPL_WHOISREGNICK);
	//Create_Raw_Gestion("308"  	,&p_RPL_RULESSTART);
	//Create_Raw_Gestion("309"  	,&p_RPL_ENDOFRULES);
	Create_Raw_Gestion("310"  	,&p_RPL_WHOISHELPOP);
	Create_Raw_Gestion("311"  	,&p_RPL_WHOISUSER);
	Create_Raw_Gestion("312"  	,&p_RPL_WHOISSERVER);
	Create_Raw_Gestion("313"  	,&p_RPL_WHOISOPERATOR);
	Create_Raw_Gestion("314"  	,&p_RPL_WHOWASUSER);
	//Create_Raw_Gestion("315"  	,&p_RPL_ENDOFWHO);
	//Create_Raw_Gestion("369"  	,&p_RPL_ENDOFWHOWAS);
	//Create_Raw_Gestion("316"  	,&p_RPL_WHOISCHANOP);
	Create_Raw_Gestion("317"  	,&p_RPL_WHOISIDLE);
	Create_Raw_Gestion("318"  	,&p_RPL_ENDOFWHOIS);
	Create_Raw_Gestion("319"  	,&p_RPL_WHOISCHANNELS);
	Create_Raw_Gestion("320"  	,&p_RPL_WHOISSPECIAL);
	//Create_Raw_Gestion("321"  	,&p_RPL_LISTSTART);
	//Create_Raw_Gestion("322"  	,&p_RPL_LIST);
	//Create_Raw_Gestion("323"  	,&p_RPL_LISTEND);
	//Create_Raw_Gestion("324"  	,&p_RPL_CHANNELMODEIS);
	//Create_Raw_Gestion("329"  	,&p_RPL_CREATIONTIME);
	//Create_Raw_Gestion("331"  	,&p_RPL_NOTOPIC);
	//Create_Raw_Gestion("332"  	,&p_RPL_TOPIC);
	//Create_Raw_Gestion("333"  	,&p_RPL_TOPICWHOTIME);
	//Create_Raw_Gestion("336"  	,&p_RPL_INVITELIST);
	//Create_Raw_Gestion("337"  	,&p_RPL_ENDOFINVITELIST);
	//Create_Raw_Gestion("334"  	,&p_RPL_LISTSYNTAX);
	Create_Raw_Gestion("335"  	,&p_RPL_WHOISBOT);
	//Create_Raw_Gestion("340"  	,&p_RPL_USERIP);
	//Create_Raw_Gestion("341"  	,&p_RPL_INVITING);
	//Create_Raw_Gestion("342"  	,&p_RPL_SUMMONING);
	//Create_Raw_Gestion("351"  	,&p_RPL_VERSION);
	//Create_Raw_Gestion("352"  	,&p_RPL_WHOREPLY);
	//Create_Raw_Gestion("315"  	,&p_RPL_ENDOFWHO);
	//Create_Raw_Gestion("353"  	,&p_RPL_NAMREPLY);
	//Create_Raw_Gestion("366"  	,&p_RPL_ENDOFNAMES);
	//Create_Raw_Gestion("346"  	,&p_RPL_INVEXLIST);
	//Create_Raw_Gestion("347"  	,&p_RPL_ENDOFINVEXLIST);
	//Create_Raw_Gestion("348"  	,&p_RPL_EXLIST);
	//Create_Raw_Gestion("349"  	,&p_RPL_ENDOFEXLIST);
	//Create_Raw_Gestion("361"  	,&p_RPL_KILLDONE);
	//Create_Raw_Gestion("362"  	,&p_RPL_CLOSING);
	//Create_Raw_Gestion("363"  	,&p_RPL_CLOSEEND);
	//Create_Raw_Gestion("364"  	,&p_RPL_LINKS);
	//Create_Raw_Gestion("365"  	,&p_RPL_ENDOFLINKS);
	//Create_Raw_Gestion("366"  	,&p_RPL_ENDOFNAMES);
	//Create_Raw_Gestion("367"  	,&p_RPL_BANLIST);
	//Create_Raw_Gestion("368"  	,&p_RPL_ENDOFBANLIST);
	//Create_Raw_Gestion("369"  	,&p_RPL_ENDOFWHOWASABOVE);
	//Create_Raw_Gestion("371"  	,&p_RPL_INFO);
	//Create_Raw_Gestion("372"  	,&p_RPL_MOTD);
	//Create_Raw_Gestion("373"  	,&p_RPL_INFOSTART);
	//Create_Raw_Gestion("374"  	,&p_RPL_ENDOFINFO);
	//Create_Raw_Gestion("375"  	,&p_RPL_MOTDSTART);
	//Create_Raw_Gestion("376"  	,&p_RPL_ENDOFMOTD);
	Create_Raw_Gestion("378"  	,&p_RPL_WHOISHOST);
	Create_Raw_Gestion("379"  	,&p_RPL_WHOISMODES);
	//Create_Raw_Gestion("381"  	,&p_RPL_YOUREOPER);
	//Create_Raw_Gestion("382"  	,&p_RPL_REHASHING);
	//Create_Raw_Gestion("383"  	,&p_RPL_YOURESERVICE);
	//Create_Raw_Gestion("384"  	,&p_RPL_MYPORTIS);
	//Create_Raw_Gestion("385"  	,&p_RPL_NOTOPERANYMORE);
	//Create_Raw_Gestion("386"  	,&p_RPL_QLIST);
	//Create_Raw_Gestion("387"  	,&p_RPL_ENDOFQLIST);
	//Create_Raw_Gestion("388"  	,&p_RPL_ALIST);
	//Create_Raw_Gestion("389"  	,&p_RPL_ENDOFALIST);
	//Create_Raw_Gestion("391"  	,&p_RPL_TIME);
	//Create_Raw_Gestion("392"  	,&p_RPL_USERSSTART);
	//Create_Raw_Gestion("393"  	,&p_RPL_USERS);
	//Create_Raw_Gestion("394"  	,&p_RPL_ENDOFUSERS);
	//Create_Raw_Gestion("395"  	,&p_RPL_NOUSERS);
	////Create_Raw_Gestion("200"  	,&p_RPL_TRACELINK);
	//Create_Raw_Gestion("201"  	,&p_RPL_TRACECONNECTING);
	//Create_Raw_Gestion("202"  	,&p_RPL_TRACEHANDSHAKE);
	//Create_Raw_Gestion("203"  	,&p_RPL_TRACEUNKNOWN);
	//Create_Raw_Gestion("204"  	,&p_RPL_TRACEOPERATOR);
	//Create_Raw_Gestion("205"  	,&p_RPL_TRACEUSER);
	//Create_Raw_Gestion("206"  	,&p_RPL_TRACESERVER);
	//Create_Raw_Gestion("207"  	,&p_RPL_TRACESERVICE);
	//Create_Raw_Gestion("208"  	,&p_RPL_TRACENEWTYPE);
	//Create_Raw_Gestion("209"  	,&p_RPL_TRACECLASS);
	//Create_Raw_Gestion("210"  	,&p_RPL_STATSHELP);
	Create_Raw_Gestion("211"  	,&p_RPL_STATSLINKINFO);
	Create_Raw_Gestion("212"  	,&p_RPL_STATSCOMMANDS);
	Create_Raw_Gestion("213"  	,&p_RPL_STATSCLINE);
	Create_Raw_Gestion("214"  	,&p_RPL_STATSOLDNLINE);
	Create_Raw_Gestion("215"  	,&p_RPL_STATSILINE);
	Create_Raw_Gestion("216"  	,&p_RPL_STATSKLINE);
	Create_Raw_Gestion("217"  	,&p_RPL_STATSQLINE);
	Create_Raw_Gestion("218"  	,&p_RPL_STATSYLINE);
	Create_Raw_Gestion("219"  	,&p_RPL_ENDOFSTATS);
	//Create_Raw_Gestion("220"  	,&p_RPL_STATSBLINE);
	//Create_Raw_Gestion("221"  	,&p_RPL_UMODEIS);
	//Create_Raw_Gestion("222"  	,&p_RPL_SQLINE_NICK);
	Create_Raw_Gestion("223"  	,&p_RPL_STATSGLINE);
	Create_Raw_Gestion("224"  	,&p_RPL_STATSTLINE);
	Create_Raw_Gestion("225"  	,&p_RPL_STATSELINE);
	Create_Raw_Gestion("226"  	,&p_RPL_STATSNLINE);
	//Create_Raw_Gestion("227"  	,&p_RPL_STATSVLINE);
	//Create_Raw_Gestion("228"  	,&p_RPL_STATSBANVER);
	//Create_Raw_Gestion("229"  	,&p_RPL_STATSSPAMF);
	//Create_Raw_Gestion("230"  	,&p_RPL_STATSEXCEPTTKL);
	//Create_Raw_Gestion("231"  	,&p_RPL_SERVICEINFO);
	//Create_Raw_Gestion("232"  	,&p_RPL_RULES);
	//Create_Raw_Gestion("233"  	,&p_RPL_SERVICE);
	//Create_Raw_Gestion("234"  	,&p_RPL_SERVLIST);
	//Create_Raw_Gestion("235"  	,&p_RPL_SERVLISTEND);
	//Create_Raw_Gestion("241"  	,&p_RPL_STATSLLINE);
	Create_Raw_Gestion("242"  	,&p_RPL_STATSUPTIME);
	Create_Raw_Gestion("243"  	,&p_RPL_STATSOLINE);
	Create_Raw_Gestion("244"  	,&p_RPL_STATSHLINE);
	//Create_Raw_Gestion("245"  	,&p_RPL_STATSSLINE);
	Create_Raw_Gestion("247"  	,&p_RPL_STATSXLINE);
	Create_Raw_Gestion("248"  	,&p_RPL_STATSULINE);
	Create_Raw_Gestion("249"  	,&p_RPL_STATSDEBUG);
	Create_Raw_Gestion("250"  	,&p_RPL_STATSCONN);
	//Create_Raw_Gestion("251"  	,&p_RPL_LUSERCLIENT);
	//Create_Raw_Gestion("252"  	,&p_RPL_LUSEROP);
	//Create_Raw_Gestion("253"  	,&p_RPL_LUSERUNKNOWN);
	//Create_Raw_Gestion("254"  	,&p_RPL_LUSERCHANNELS);
	//Create_Raw_Gestion("255"  	,&p_RPL_LUSERME);
	//Create_Raw_Gestion("256"  	,&p_RPL_ADMINME);
	//Create_Raw_Gestion("257"  	,&p_RPL_ADMINLOC1);
	//Create_Raw_Gestion("258"  	,&p_RPL_ADMINLOC2);
	//Create_Raw_Gestion("259"  	,&p_RPL_ADMINEMAIL);
	//Create_Raw_Gestion("261"  	,&p_RPL_TRACELOG);
	//Create_Raw_Gestion("265"  	,&p_RPL_LOCALUSERS);
	//Create_Raw_Gestion("266"  	,&p_RPL_GLOBALUSERS);
	//Create_Raw_Gestion("271"  	,&p_RPL_SILELIST);
	//Create_Raw_Gestion("272"  	,&p_RPL_ENDOFSILELIST);
	//Create_Raw_Gestion("275"  	,&p_RPL_STATSDLINE);
	//Create_Raw_Gestion("290"  	,&p_RPL_HELPHDR);
	//Create_Raw_Gestion("291" 	,&p_RPL_HELPOP); //dalnet
	//Create_Raw_Gestion("292"  	,&p_RPL_HELPTLR);
	//Create_Raw_Gestion("293"  	,&p_RPL_HELPHLP); //dalnet
	//Create_Raw_Gestion("294"  	,&p_RPL_HELPFWD);
	//Create_Raw_Gestion("295"  	,&p_RPL_HELPIGN);
	//Create_Raw_Gestion("006"  	,&p_RPL_MAP);
	//Create_Raw_Gestion("610"  	,&p_RPL_MAPMORE);
	//Create_Raw_Gestion("007"  	,&p_RPL_MAPEND);
	//Create_Raw_Gestion("522"  	,&p_ERR_WHOSYNTAX);
	//Create_Raw_Gestion("523"  	,&p_ERR_WHOLIMEXCEED);
	//Create_Raw_Gestion("524"  	,&p_ERR_OPERSPVERIFY);
	//Create_Raw_Gestion("008"  	,&p_RPL_SNOMASK);
	//Create_Raw_Gestion("600"  	,&p_RPL_LOGON);
	//Create_Raw_Gestion("601"  	,&p_RPL_LOGOFF);
	//Create_Raw_Gestion("602"  	,&p_RPL_WATCHOFF);
	//Create_Raw_Gestion("603"  	,&p_RPL_WATCHSTAT);
	//Create_Raw_Gestion("604"  	,&p_RPL_NOWON);
	//Create_Raw_Gestion("605"  	,&p_RPL_NOWOFF);
	//Create_Raw_Gestion("606"  	,&p_RPL_WATCHLIST);
	//Create_Raw_Gestion("607"  	,&p_RPL_ENDOFWATCHLIST);
	//Create_Raw_Gestion("617"  	,&p_RPL_DCCSTATUS);
	//Create_Raw_Gestion("618"  	,&p_RPL_DCCLIST);
	//Create_Raw_Gestion("619"  	,&p_RPL_ENDOFDCCLIST);
	//Create_Raw_Gestion("620"  	,&p_RPL_DCCINFO);
	//Create_Raw_Gestion("640"  	,&p_RPL_DUMPING);
	//Create_Raw_Gestion("641"  	,&p_RPL_DUMPRPL);
	//Create_Raw_Gestion("642"  	,&p_RPL_EODUMP);
	//Create_Raw_Gestion("659"  	,&p_RPL_SPAMCMDFWD);
	//Create_Raw_Gestion("671"  	,&p_RPL_WHOISSECURE);
	//Create_Raw_Gestion("972"  	,&p_ERR_CANNOTDOCOMMAND);
	//Create_Raw_Gestion("974"  	,&p_ERR_CANNOTCHANGECHANMODE);
	//Create_Raw_Gestion("999"  	,&p_ERR_NUMERICERR);
}


/*
	void d'execution des raws
*/
void executeRaw_Gestion( message_irc *message )
{
	Raw_IN_Gestion *myRaw;
	myRaw = pRaw_IN_Gestion;

	if(!strcmp(message->RAW[0],"NICK"))
	{
		while(myRaw)
		{
			if(!strcmp(myRaw->rawName, "CONNECT"))
			{
				myRaw->func(message);
				printf("Raw gestion :%s\n",myRaw->rawName);
			}
			myRaw = myRaw->suivant;
		}
		return;
	}

	myRaw = pRaw_IN_Gestion;
	while(myRaw)
	{
		if(message->RAW[0] != NULL)
		{
			if(!strcmp(myRaw->rawName, message->RAW[0]))
			{
				printf("Raw gestion :%s\n",myRaw->rawName);
				myRaw->func(message);
			}
		}
		if(message->RAW[1] != NULL)
		{
			if(strcmp(myRaw->rawName, message->RAW[1]) == 0)
			{
				printf("Raw gestion :%s\n",myRaw->rawName);
				myRaw->func(message);
			}
		}
		myRaw = myRaw->suivant;
	}
}


/**
	Gestion des raws de bot

	Les raws de bots sont les raws neccessaire a chaque robot
**/

Raw_IN_Bot *pRaw_IN_Bot = NULL;

Raw_IN_Bot *Create_Raw_Bot( char *name , myFuncRawPtr func,char *botnick)
{
	Raw_IN_Bot *nRaw;
	nRaw = (Raw_IN_Bot*)malloc(sizeof(Raw_IN_Bot));
	STRDUP(nRaw->rawName,name);
	STRDUP(nRaw->rawBot,botnick);
	nRaw->func = func;

	/* mise en liste doublement chainee */
	nRaw->precedent = NULL;
	nRaw->suivant = pRaw_IN_Bot;
	if (pRaw_IN_Bot)
    	pRaw_IN_Bot->precedent = nRaw;
	pRaw_IN_Bot = nRaw;

	/* return le Raw_IN nouvellement crée */
	return pRaw_IN_Bot;
}

int clear_Raw_Bot()
{
	Raw_IN_Bot *nRaw;
	while (pRaw_IN_Bot)
	{
		nRaw = pRaw_IN_Bot;
		pRaw_IN_Bot = pRaw_IN_Bot->suivant;
		FREE(nRaw->rawName);
		FREE(nRaw->rawBot);
		FREE(nRaw);
		nRaw = NULL;
	}
	pRaw_IN_Bot = NULL;
	return 1;
}

long Raw_IN_t_Bot()
{
	int count = 0;

	Raw_IN_Bot *nRaw;
	nRaw = pRaw_IN_Bot;
	while (nRaw)
	{
		count++;
		nRaw = nRaw->suivant;
	}
	return sizeof(Raw_IN_Bot) * (count+1);
}

int del_Raw_Bot(char *botname)
{
	Raw_IN_Bot *nRaw = pRaw_IN_Bot;
	while(nRaw)
	{
		if(!strcmp(nRaw->rawBot,botname))
		{
			if(nRaw->suivant)
				nRaw->suivant->precedent = nRaw->precedent;

			if(nRaw->precedent)
				nRaw->precedent->suivant = nRaw->suivant;

			if(nRaw == pRaw_IN_Bot)
				pRaw_IN_Bot = nRaw->suivant;

			FREE(nRaw->rawName);
			FREE(nRaw->rawBot);
			FREE(nRaw);
			nRaw = pRaw_IN_Bot;
			continue;
		}
		nRaw = nRaw->suivant;
	}
	return 1;
}



void executeRaw_Bot( message_irc *message )
{
	Raw_IN_Bot *myRaw;
	myRaw = pRaw_IN_Bot;

	if(!strcmp(message->RAW[0],"NICK"))
	{
		while(myRaw)
		{
			if(!strcmp(myRaw->rawName, "CONNECT"))
			{
				printf("Raw bot :%s\n",myRaw->rawName);
				myRaw->func(message);
			}
			myRaw = myRaw->suivant;
		}
		return;
	}

	myRaw = pRaw_IN_Bot;
	while(myRaw)
	{
		if(message->RAW[0] != NULL)
		{
			if(!strcmp(myRaw->rawName, message->RAW[0]))
			{
				printf("Raw bot :%s\n",myRaw->rawName);
				myRaw->func(message);
			}
		}
		if(message->RAW[1] != NULL)
		{
			if(strcmp(myRaw->rawName, message->RAW[1]) == 0)
			{
				printf("Raw bot :%s\n",myRaw->rawName);
				myRaw->func(message);
			}
		}
		myRaw = myRaw->suivant;
	}
}


/**
	Gestion des raws de Protect 

	Les raws de bots sont les raws neccessaire aux Protect 
**/

Raw_IN_Protect *pRaw_IN_Protect = NULL;

Raw_IN_Protect *Create_Raw_Protect( char *name , myFuncRawPtr func)
{
	Raw_IN_Protect *nRaw;
	nRaw = (Raw_IN_Protect*)malloc(sizeof(Raw_IN_Protect));
	STRDUP(nRaw->rawName,name);
	nRaw->func = func;

	/* mise en liste doublement chainee */
	nRaw->precedent = NULL;
	nRaw->suivant = pRaw_IN_Protect;
	if (pRaw_IN_Protect)
    	pRaw_IN_Protect->precedent = nRaw;
	pRaw_IN_Protect = nRaw;

	/* return le Raw_IN nouvellement crée */
	return pRaw_IN_Protect;
}

int clear_Raw_Protect()
{
	Raw_IN_Protect *nRaw;
	while (pRaw_IN_Protect)
	{
		nRaw = pRaw_IN_Protect;
		pRaw_IN_Protect = pRaw_IN_Protect->suivant;
		FREE(nRaw->rawName);
		FREE(nRaw);
		nRaw = NULL;
	}
	pRaw_IN_Protect = NULL;
	return 1;
}

long Raw_IN_t_Protect()
{
	int count = 0;

	Raw_IN_Protect *nRaw;
	nRaw = pRaw_IN_Protect;
	while (nRaw)
	{
		count++;
		nRaw = nRaw->suivant;
	}
	return sizeof(Raw_IN_Protect) * (count+1);
}

void executeRaw_Protect( message_irc *message )
{
	Raw_IN_Protect *myRaw;
	myRaw = pRaw_IN_Protect;

	if(!strcmp(message->RAW[0],"NICK"))
	{
		while(myRaw)
		{
			if(!strcmp(myRaw->rawName, "CONNECT"))
			{
				printf("Raw Protect :%s\n",myRaw->rawName);
				myRaw->func(message);
			}
			myRaw = myRaw->suivant;
		}
		return;
	}
}


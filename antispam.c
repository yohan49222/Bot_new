#include "main.h"
extern Config *myconfig;

As_Mask *pAs_mask = NULL;
As_Actif *pAs_Actif = NULL;

static char *me = "SpamServ";
char *channelAs = NULL;
int QuantiteAs = 0;
int activeAs = 1;

static char *nick_bot_spam[] = {
"Mercure","Venus","Terre","Mars","Jupiter",
"Saturne","Neptune","Pluton","Luna","Phobos",
"Io","Mimas","Ariel","Triton","Charon",
"Deimos","Europe","Encelade","Umbriel","Nereide",
"Ganymede","Tethys","Titania","Protee","Callisto",
"Dione","Larissa","Amalthee","Rhea","Miranda",
"Despina","Hymalia","Titan","Cordelia","Galatee",
"Elara","Hyperion","Thalassa","Pasiphae","Japet",
"Bianca","Naiade","Sinope","Pan","Cressida",
"Lysithea","Phoebe","Desdemona","Carme","Juliet",

"Ananke","Epimethee","Portia","Leda","Helene",
"Rosalind","Thebe","Telesto","Belinda","Adrastee",
"Calypso","Puck","Metis","Caliban","Callirrhoe",
"Promethee","Sycorax","Themisto","Pandore","Prospero",
"Kalyke","Ymir","Setebos","Iocaste","Paaliaq",
"Stephano","Erinome","Siarnaq","Trinculo","Harpalyke",
"Tarvos","Isonoe","Kiviuq","Praxidike","Ijiraq","Magaclite",
"Thrym","Taygete","Skadi","Chaldene","Mundilfari",
"Erriapo","Autonoe","Albiorix","Thyone","Suttung",
"Hermippe","Eurydome","Sponde","Pasithee","Euanthe",

"Kale","Euporie","Aitne","Yamakasgeule","Bad_Boy",
"BabyDoll","Coccinelle","papillotte","willy20","caro_no_pv",
"Bellissima","Tite__Libe","ReX","le_chacal","gost26",
"BoGosse","VanilleChoco","Tacos_21","Congo","tite_fraise",
"Twister","KOOL","petite_fleur","dennis_","BoomGirl",
"ludo_32","Malback","TaHiTi73","keanu","rOlLeRbAlL",
"__LeBest","NouNours","cobra","sanDye","Susie__",
"Fripouille","blacknoir","franky","Colibri","DAK",
"Jengo","lilo__","celtic_33","Phenix","TrUmAn",
"speedy","Moulouk","nicololo","picsou","Stanley_17",

"CarpeDiem","_TanTine","louane54","guillaume_","Labrea",
"le_Patriote","Biscotte","frisette","cactus01","pikachu",
"NoWell","craquinette","half_","MrLoeuf","Titeuf_35",
"daikiri_","A_Rivia","_Doriane_","zamiss","KiKi26",
"le_rital","LeLover","cartouche","la_volta","_mario",
"jenny_","cooKies","canadoux","peche","Apparence",
"gavroche","LiMit","space_man","Shumi","bidou_",
"gomette_","LiOoO","peps","alizee","Plume",
"_natacha_","guigui08","Leo","ribendelle","lagaffe",
"ptitpingu","murane","jymmy97","fire_mike","PaPriKa",

"Selmac59","Bozo","pinkfaby","cally93","frog3r",
"michoda_","CdeLaBombe","Finflot_","Yommuse","coco2b",
"jouloux","DealerDamour","_nandouye","ToOons","jolie_manue",
"boy3r3","olivialola","YMAS","tite_brunette","gregibiza",
"chmarzec","marvin_15","zappy","Pincette","chanel92",
"lapinou_","Krvstalix","miniknaki","laTaupe","cheepCheep",
"wheshdidi","_Gounours","sosoni2","froggy","nono50",
"num_s","kizou","mongolito","KatmandoU","biyouk",
"_Eph3m3r3_","mamanlilik","magicsweet","Sioux","popkorn",
"MissNess","Moofonde","bobo_57","patata","diseKRArew",

"tartemolle","platoon","Rosace","IdalGo","bruno_02",
"lucas","benjiii","G3N3Gis","titeFEE","_justine_",
"Oceane","belleDeJour","Pitch","mylenna","framboisine",
"Marinette","pelagie","bomec_39","brindille","Acrylique",
"Salomee","SCAR","fille_cam","feufolet","pinnacle",
"rockette","kevin_63","camelotte","ZORG","ToRiTo",
"criscolo","viva_zita","Stryke","sapristi","poucinette",
"frany_","santoi","BouBou","Warrior","Badaboum",
"amarie","_jadore_","Revedetoi","ptitludo","Kings",
"dgedge_","penelope","Scala","petite_lulu","Flo_36",

"Seb_49","ScoopS","Toundra","Mec_Parfait"
};

static char *real_bot_spam[] = {
"Je suis le diable !",
"whois ? hein ?",
"Shaman Exterm Script modified",
"Best script ever : Rastafarai",
"SpOoOfff plus la",
"Regarde pas ici",
"Qu'est ce que ca peut te faire",
"Brunette a forte poitrine",
"Curious isn't it ?",
"Elton John is dead",
"I love rock'n'roll",
"Etre ou ne pas etre",
"Saga Africa",
"viens donc, je t'explose",
"blondinette peroxyd\xe9",
"here no need to care",
"sois pas timide",
"It's so delight",
"Happy Halloween",
"That'is the question",
"I love sex",
"arrAche TOA !"
};

static char *As_quit[] = {
"I'll be back !!!","Je reviendrai !",

"@ tte :) Restez sages hein !","Proxima-Script Powa !",

"\0030,4CommenT ETrE InSenSiBle A\0031 SoulShine'S ScRipT V2\0030, Tien l'url\0038 www.rastafarai.com \0036 [ SoulShine Script V2 ]",

"\00310Tu VeuX Un Bon ScRipT Je Te ConSeiL D'Aller Sur \00312www.rastafarai.com \00310, Tu y TrouVeRa \00313>> \0033SoulShine'S ScRipT V2 \00313<< \0036[ SoulShine Script V2 ]",

"\0030,1 .: \0030  \0037Fri$$on \0030Sc \0037 \0030ipt \0037 \0030[V 4.6] \0039UltiMe \0030 \0037By TeniX \0038 Dispo Sur \0037 http://www.SalonFrisson.fr.tc/ \0030:. ",

"\00314,1|\0030,1 Use \0034,1{ \00314,1R \00314,1a \00315,1T \00315,1a \0030,1M \0030,1- \0030,1S \00315,1c \00315,1R \00314,1i \00314,1P \00314,1t \00314,1V \0036,1- \00314,1e\0036,1- \00315,1R \0036,1- \00315,1S \0036,1- \0030,1i \0036,1- \0030,1O \0036,1- \00315,1n \0036,1- \00314,1Z  \0034,1- \0034,1- \00314,12.2 \0034} \0030,1Dispo sur \0030h\0030t\0030t\0030p\0030:\0030/\0030/\0030w\0030w\0030w\0030.ratam-script\0030.\0030c\0030o\0030m \00314|",

" \00311 \0039,1Bon t'ch@t a tous !! \0030J'utilise \0030C\0033yber\0030S\0033cript \0030T\xe9l\xe9hargeable sur : ( \0034A plus tard all \0030)",

"Quand mille personnes s'habillent comme un con, c'est l'arm\xe9 françise. [Pierre Desproges]",

"\00311,1 .o \0030\00311Fri$$on \0030Sc\00311\0030ipt\00311 \0030V5 \00311GLACIAL\0030 Par TeniX\00311o.",

"\00314.:. \0036PredatorScript \0034v6.7\0031 :: Moderation/Slaps/Skins/Mp3 player/Divx Player/Complet::Disponible sur \0034Http://www.PuMaZouNeT.NeT\00314.:.",

"Si un r\xe9ve devient la r\xe9lit\xe9,alors l'imagination n'a plus de limite...",

"\0030,1D\00311r\00312E\0030a\00311M\00312S\0030c\00311R\00312i\0030P\00311t \00312V\0030-\003114 \00312P\0030a\00311R \00312V\0030e\00311s\00312t\0030a\00311X \0034je t'aime mon cheri DrEaM ScRiPt V-4 PaR VestaX www.universal-djs.com"
};

/**
	initalisation du service
**/
void init_spam()
{
	int i = 0;
	int n = 0;

	/**
		verifie que ce clone n'est pas dejas chargé
	**/
	if(get_clone(me))
		return;

	/**
		creation du clone
	**/
	new_clone(me,myconfig->flags,myconfig->real,NULL);

	
	/**
		creation des commandes
	**/
	Create_Com("help" , me, &antispam_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");

	Create_Com("add_mask_spam",me,&add_mask_spam,"ACN","/msg %s ADD_MASK_SPAM <regex>","Ajoute une expression reguliere a la liste des exceptions");

	Create_Com("active",me,&antispam_active,"o","/msg %s ACTIVE <ON|OFF>","Active le d\xe9tection de spam");

	/**
		creation des raws
	**/
	Create_Raw_Bot("PRIVMSG"  	,&ANTISPAM_PRIVMSG	,me);
	Create_Raw_Bot("NOTICE"  	,&ANTISPAM_PRIVMSG	,me);
	Create_Raw_Bot("KILL"  		,&ANTISPAM_KILL		,me);
	Create_Raw_Bot("KICK"  		,&ANTISPAM_KICK		,me);

	/**
		lecture du fichier de configuration
	**/
	load_config_Antispam("bot.conf");

	/**
		chargement de la liste des expressions reguliere protegée
	**/
	load_db_antispam();

	/**
		creation des timers de connection des bots
	**/
	do
	{
		while(i < 60)
		{
			i = my_rand(1800);
		}
		new_timer(1,i,&connect_As,NULL,"ANTISPAM");
		i = 0;

	}while( n++ < QuantiteAs);
}

/**
	liberation memoire de tout ce qui ne sert plus et quit du bot et des AS
**/
void unload_spam()
{
	clear_mask_spam();
	del_command(me);
	del_Raw_Bot(me);
	deconnect_allAs();
	del_clone(me,"Aurevoir tout le monde");
	FREE(channelAs);
}

/**
	Raw antispam
**/

/**
	gestion des Message PRIVMSG et NOTICE
**/
void ANTISPAM_PRIVMSG(message_irc *message)
{
	int result = 0;
	char txt[MAXLEN];

	/** 
		si les destinataire est le bot de gestion des As , excute la commande et return
	**/
	if(!strcasecmp(message->RAW[2],me))
	{
		User *use = get_user(message->RAW[0]);
		if(!use)
			return;

		executeCom( use, message , me);
		return;
	}

	/**
		test si les as sont active ou non
	**/
	if(!activeAs)
		return;

	/**
		Spam sur channel ou Notice ou Prive
	**/
	if(!strcasecmp(message->RAW[2],channelAs) || get_As_Actif(message->RAW[2]))
	{
		User *use = get_user(message->RAW[0]);
		if(!use)
			return;

		result = find_spam(message);
		if(result == 1)
		{

			if(use->option & IS_PROTECT)
			{
				fsend_service(me,FORMAT_SPAMUSERPROTECT,message->RAW[0],message->message);
				return;
			}

			fsend_service(me,FORMAT_SPAM,message->RAW[0],message->message);
			fsend_service(me,FORMAT_KILL,me,use->nick,"Spam interdit sur ce serveur");
			sprintf(txt,"[%s] Local kill by %s (Spam interdit sur ce serveur)",myconfig->host,me);
			fsend_com(COM_SERV_SVSKILL,myconfig->host,use->nick,txt,myconfig->host,me);
			del_user(use->nick,"Spam interdit sur ce serveur");
		}
	}
}

/**
	gestion des kill des As
**/
void ANTISPAM_KILL(message_irc *message)
{
	/**
		si c un as_actif
	**/
	if(get_As_Actif(message->RAW[2]))
	{
		fsend_service(me,FORMAT_KILL, message->RAW[0],message->RAW[2],message->message);

		/**
			destruction de l'as
		**/
		del_As_Actif(message->RAW[2]);

		/**
			destruction du clone
		**/
		del_clone(message->RAW[2],message->message);
		
		/**
			reconnection d'un AS
		**/
		connect_As();
	}

	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
}

void ANTISPAM_KICK(message_irc *message)
{
	As_Actif *n = get_As_Actif(message->RAW[3]);
	if(n)
	{
		bot_join(n->nick, message->RAW[2] , "+");
	}

	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+");
	}
}

void load_config_Antispam(char *Fichier )
{
	char ligne[256];
	char *var = NULL;
	char *val = NULL;
	char *p;
	FILE *myFile = fopen(Fichier, "r");
	if(!myFile)
		return;

	while(fgets(ligne, sizeof ligne, myFile))
	{
		if( (ligne[0] != '#') && (ligne[0] != '/') && (strlen(ligne) > 1 ))
		{
			p = strchr(ligne, '\n');
			if (p)
			{
				*p = '\0';
			}
			var = strtok(ligne , "\"");
			sscanf(var,"%s",var);
			val = strtok(NULL , "\"");
				
			if(!val)
				continue;

			if(var && val)
			{

				if(!strcmp("CHANNELAS",var))
					STRDUP(val,channelAs);

				if(!strcmp("QAS",var))
					QuantiteAs = atoi(val);
			}
		}
	}

	fclose(myFile);
	
	return;
}

void save_db_antispam()
{

	As_Mask *n = pAs_mask;
	FILE *myFile = fopen("base/spam_auto.db", "w");
	if(!myFile)
		return;

	while(n)
	{
		fprintf(myFile,"%s\n",n->mask);
		n = n->suivant;
	}

	fclose(myFile);
	fsend_service(me,SAVE_BD_OK,"Spam");
}

void load_db_antispam()
{
	char ligne[256];
	char *var;
	char *p;
	FILE *myFile = fopen("base/spam_auto.db", "r");
	if(!myFile)
		return;

	while(fgets(ligne, sizeof ligne, myFile))
	{
		if( (ligne[0] != '#') && (strlen(ligne) > 1 ))
		{
			p = strchr(ligne, '\n');
			if (p)
				*p = '\0';

			p = strchr(ligne, '\r');
			if (p)
				*p = '\0';

			var = strtok(ligne , "\n");
			if(var)
				new_mask(var);
		}
	}
	fclose(myFile);
	fsend_service(me,CHAR_BD_OK,"Spam");
}

As_Actif *new_As_Actif(char *nick)
{
	As_Actif *n = (As_Actif*)malloc(sizeof(As_Actif));
	if(!n)
		return NULL;

	if(!nick || !*nick)
	{
		FREE(n);
		return NULL;
	}

	STRDUP(n->nick,nick);
	n->precedent = NULL;
	n->suivant = pAs_Actif;
	if (pAs_Actif)
    	pAs_Actif->precedent = n;
	pAs_Actif = n;
	return pAs_Actif;
}

int del_As_Actif(char *nick)
{
	As_Actif *n = get_As_Actif(nick);
	if(!n)
		return 0;

	if(n->suivant)
		n->suivant->precedent = n->precedent;

	if(n->precedent)
		n->precedent->suivant = n->suivant;

	if(n == pAs_Actif)
		pAs_Actif = n->suivant;

	FREE(n->nick);
	FREE(n);

	return 1;
}

As_Actif *get_As_Actif(char *nick)
{
	As_Actif *n = pAs_Actif;
	while(n)
	{
		if(!strcasecmp(n->nick,nick))
			return n;

		n = n->suivant;
	}
	return NULL;
}

void connect_As()
{
	long i = 0;
	long j = 0;
	long vie = 0;

	char *host = codage_host();
	User *use;
	As_Actif *as;

	while (vie < 7200) vie = my_rand(86400);
	i = my_rand(303);

	use = get_user(nick_bot_spam[i]);
	if(use)
	{
		new_timer(1,120,&connect_As,NULL,"ANTISPAM");
		return;
	}

	j = my_rand(22);
	use = new_clone(nick_bot_spam[i],"ixw",real_bot_spam[j],host);
	FREE(host);

	as = new_As_Actif(nick_bot_spam[i]);

	bot_join(use->nick, channelAs , "+");

	new_timer(1,vie,&deconnect_As,use->nick,"ANTISPAM");
}

void deconnect_allAs()
{
	As_Actif *as;
	int i = 0;
	char *nick;
	while(pAs_Actif)
	{
		as = pAs_Actif;
		STRDUP(nick,as->nick);
		i = my_rand(10);
		del_Timer("*","ANTISPAM");
		del_As_Actif(nick);
		del_clone(nick,As_quit[i]);
		FREE(nick);
	}
}

void deconnect_As(char *Array)
{
	int i = 0;
	i = my_rand(10);
	del_As_Actif(Array);
	del_clone(Array,As_quit[i]);
	new_timer(1,3,&connect_As,NULL,"ANTISPAM");
}

As_Mask *new_mask(char *mask)
{
	As_Mask *n = (As_Mask*)malloc(sizeof(As_Mask));
	if(!n)
		return NULL;

	if(!mask || !*mask)
	{
		FREE(n);
		return NULL;
	}

	STRDUP(n->mask,mask);

	n->precedent = NULL;
	n->suivant = pAs_mask;
	if (pAs_mask)
    		pAs_mask->precedent = n;
	pAs_mask = n;

	fsend_service(me,FORMAT_ADDMASKSPAM,n->mask);

	return pAs_mask;
}

int clear_mask_spam()
{
	As_Mask *mask;
	while (pAs_mask)
	{
		mask = pAs_mask;
		pAs_mask = pAs_mask->suivant;
		FREE(mask->mask);
		FREE(mask);
		mask = NULL;
	}
	pAs_mask = NULL;
	return 1;
}

int find_spam(message_irc *message)
{
	int result = 0;

	result = is_spam(message->message);
	if(result == 0)
	{
		result = is_spam_ok(message->message);
		if(result == 0)
			return 0;
		else
			return 1;
	}
	return 0;
}

char *codage_host()
{
	char *table_host[] = {
			"x-********.w**-***.abo.wanadoo.fr",
			"x-********.w**-**.abo.wanadoo.fr",
			"x-********.cust.tele2.fr",
			"x-********.adsl.proxad.net",
			"x-********.fbx.proxad.net",
			"d-********.d4.club-internet.fr",
			"d-********.ipt.aol.com",
			"m**.net**-**-***.noos.fr" };

	char letter[] = { 'A' , 'B' , 'C' , 'D' , 'F' , 'G' , 'H' };
	char chiffre[] = { '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' };
	char host[50];
	strcpy(host,table_host[my_rand(8)]);

	if(	strstr(host,"abo") != 0 ||
		strstr(host,"tele2") != 0 ||
		strstr(host,"proxad") != 0 ||
		strstr(host,"club") != 0 ||
		strstr(host,"aol") != 0 )
	{
		host[2] = letter[my_rand(7)];
		host[3] = chiffre[my_rand(10)];
		host[4] = chiffre[my_rand(10)];
		host[5] = letter[my_rand(7)];
		host[6] = chiffre[my_rand(10)];
		host[7] = chiffre[my_rand(10)];
		host[8] = letter[my_rand(7)];
		host[9] = chiffre[my_rand(10)];

		if(	strstr(host,"abo") != 0 )
		{
			host[12] = chiffre[my_rand(10)];
			host[13] = chiffre[my_rand(10)];

			host[15] = chiffre[my_rand(10)];
			host[16] = chiffre[my_rand(10)];

			if(strlen(host) == 33)
				host[17] = chiffre[my_rand(10)];
		}
	}
	else
	{
		host[1] = chiffre[my_rand(10)];
		host[2] = chiffre[my_rand(10)];
		host[7] = chiffre[my_rand(10)];
		host[8] = chiffre[my_rand(10)];
		host[10] = chiffre[my_rand(10)];
		host[11] = chiffre[my_rand(10)];
		host[13] = chiffre[my_rand(10)];
		host[14] = chiffre[my_rand(10)];
		host[15] = chiffre[my_rand(10)];
	}
	return strdup(host);
}

void antispam_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void antispam_active(User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	if(!strcasecmp(message->ARG[1],"ON"))
	{
		activeAs = 1;
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Les AS sont activ\xe9s");
		return;
	}

	if(!strcasecmp(message->ARG[1],"OFF"))
	{
		activeAs = 0;
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Les AS sont d\xe9sactiv\xe9s");
		return;
	}
	help_on_error(use,message->ARG[0],me);
}

void add_mask_spam(User *use ,message_irc *message)
{
	char txt[MAXLEN];
	int result = 0;

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	result = verif_compile(message->ARG[1]);
	if(result == 0)
	{
		new_mask(message->ARG[1]);
		sprintf(txt,"Votre expression reguliere %s a \xe9t\xe9 ajout\xe9\x65",message->ARG[1]);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		save_db_antispam();
	}
	else
	{
		sprintf(txt,"Votre expression reguliere %s contient une erreur",message->ARG[1]);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
	}
}

/**
	verifie su str_request est une url
**/
int is_spam (const char *str_request)
{
	char *str_regex = "(/server (-m )?(.*)|((news?|https?|ftp|irc)://)|([wW]{3}\\.))";
	int result = verif_pattern(str_regex ,str_request);
	return result;
}
/**
	verifie su str_request est une url protege **/
int is_spam_ok(const char *str_request)
{
	int result = 0;
	As_Mask *mask = pAs_mask;
	while(mask)
	{
		result = verif_pattern(mask->mask ,str_request);
		if(result == 0)
			return 0;

		mask = mask->suivant;
	}
	return 1;
}


#ifndef RAWNUMERIC_H

#define RAWNUMERIC_H

void p_RPL_WELCOME( message_irc *message );             	/* 001 */
void p_RPL_YOURHOST( message_irc *message );            	/* 002 */
void p_RPL_CREATED( message_irc *message );             	/* 003 */
void p_RPL_MYINFO( message_irc *message );              	/* 004 */
void p_RPL_ISUPPORT( message_irc *message );            	/* 005 */
void p_RPL_REDIR( message_irc *message );               	/* 10 */
void p_RPL_REMOTEISUPPORT( message_irc *message );              /* 105 */
void p_ERR_NOSUCHNICK( message_irc *message );          	/* 401 */
void p_ERR_NOSUCHSERVER( message_irc *message );                /* 402 */
void p_ERR_NOSUCHCHANNEL( message_irc *message );               /* 403 */
void p_ERR_CANNOTSENDTOCHAN( message_irc *message );            /* 404 */
void p_ERR_TOOMANYCHANNELS( message_irc *message );             /* 405 */
void p_ERR_WASNOSUCHNICK( message_irc *message );               /* 406 */
void p_ERR_TOOMANYTARGETS( message_irc *message );              /* 407 */
void p_ERR_NOSUCHSERVICE( message_irc *message );               /* 408 */
void p_ERR_NOORIGIN( message_irc *message );            	/* 409 */
void p_ERR_NORECIPIENT( message_irc *message );                 /* 411 */
void p_ERR_NOTEXTTOSEND( message_irc *message );                /* 412 */
void p_ERR_NOTOPLEVEL( message_irc *message );          	/* 413 */
void p_ERR_WILDTOPLEVEL( message_irc *message );                /* 414 */
void p_ERR_UNKNOWNCOMMAND( message_irc *message );              /* 421 */
void p_ERR_NOMOTD( message_irc *message );              	/* 422 */
void p_ERR_NOADMININFO( message_irc *message );                 /* 423 */
void p_ERR_FILEERROR( message_irc *message );           	/* 424 */
void p_ERR_NOOPERMOTD( message_irc *message );          	/* 425 */
void p_ERR_TOOMANYAWAY( message_irc *message );                 /* 429 */
void p_ERR_NONICKNAMEGIVEN( message_irc *message );             /* 431 */
void p_ERR_ERRONEUSNICKNAME( message_irc *message );            /* 432 */
void p_ERR_NICKNAMEINUSE( message_irc *message );               /* 433 */
void p_ERR_NORULES( message_irc *message );             	/* 434 */
void p_ERR_SERVICECONFUSED( message_irc *message );             /* 435 */
void p_ERR_NICKCOLLISION( message_irc *message );               /* 436 */
void p_ERR_BANNICKCHANGE( message_irc *message );               /* 437 */
void p_ERR_NCHANGETOOFAST( message_irc *message );              /* 438 */
void p_ERR_TARGETTOOFAST( message_irc *message );               /* 439 */
void p_ERR_SERVICESDOWN( message_irc *message );                /* 440 */
void p_ERR_USERNOTINCHANNEL( message_irc *message );            /* 441 */
void p_ERR_NOTONCHANNEL( message_irc *message );                /* 442 */
void p_ERR_USERONCHANNEL( message_irc *message );               /* 443 */
void p_ERR_NOLOGIN( message_irc *message );             	/* 444 */
void p_ERR_SUMMONDISABLED( message_irc *message );              /* 445 */
void p_ERR_USERSDISABLED( message_irc *message );               /* 446 */
void p_ERR_NONICKCHANGE( message_irc *message );                /* 447 */
void p_ERR_NOTREGISTERED( message_irc *message );               /* 451 */
void p_ERR_HOSTILENAME( message_irc *message );                 /* 455 */
void p_ERR_NOHIDING( message_irc *message );            	/* 459 */
void p_ERR_NOTFORHALFOPS( message_irc *message );               /* 460 */
void p_ERR_NEEDMOREPARAMS( message_irc *message );              /* 461 */
void p_ERR_ALREADYREGISTRED( message_irc *message );            /* 462 */
void p_ERR_NOPERMFORHOST( message_irc *message );               /* 463 */
void p_ERR_PASSWDMISMATCH( message_irc *message );              /* 464 */
void p_ERR_YOUREBANNEDCREEP( message_irc *message );            /* 465 */
void p_ERR_YOUWILLBEBANNED( message_irc *message );             /* 466 */
void p_ERR_KEYSET( message_irc *message );              	/* 467 */
void p_ERR_ONLYSERVERSCANCHANGE( message_irc *message );	/* 468 */
void p_ERR_LINKSET( message_irc *message );             	/* 469 */
void p_ERR_LINKCHANNEL( message_irc *message );                 /* 470 */
void p_ERR_CHANNELISFULL( message_irc *message );               /* 471 */
void p_ERR_UNKNOWNMODE( message_irc *message );                 /* 472 */
void p_ERR_INVITEONLYCHAN( message_irc *message );              /* 473 */
void p_ERR_BANNEDFROMCHAN( message_irc *message );              /* 474 */
void p_ERR_BADCHANNELKEY( message_irc *message );               /* 475 */
void p_ERR_BADCHANMASK( message_irc *message );                 /* 476 */
void p_ERR_NEEDREGGEDNICK( message_irc *message );              /* 477 */
void p_ERR_BANLISTFULL( message_irc *message );                 /* 478 */
void p_ERR_LINKFAIL( message_irc *message );            	/* 479 */
void p_ERR_CANNOTKNOCK( message_irc *message );                 /* 480 */
void p_ERR_NOPRIVILEGES( message_irc *message );                /* 481 */
void p_ERR_CHANOPRIVSNEEDED( message_irc *message );            /* 482 */
void p_ERR_CANTKILLSERVER( message_irc *message );              /* 483 */
void p_ERR_ATTACKDENY( message_irc *message );          	/* 484 */
void p_ERR_KILLDENY( message_irc *message );            	/* 485 */
void p_ERR_NONONREG( message_irc *message );            	/* 486 */
void p_ERR_NOTFORUSERS( message_irc *message );                 /* 487 */
void p_ERR_HTMDISABLED( message_irc *message );                 /* 488 */
void p_ERR_SECUREONLYCHAN( message_irc *message );              /* 489 */
void p_ERR_NOSWEAR( message_irc *message );             	/* 490 */
void p_ERR_NOOPERHOST( message_irc *message );          	/* 491 */
void p_ERR_NOCTCP( message_irc *message );              	/* 492 */
void p_ERR_CHANOWNPRIVNEEDED( message_irc *message );           /* 499 */
void p_ERR_TOOMANYJOINS( message_irc *message );                /* 500 */
void p_ERR_UMODEUNKNOWNFLAG( message_irc *message );            /* 501 */
void p_ERR_USERSDONTMATCH( message_irc *message );              /* 502 */
void p_ERR_SILELISTFULL( message_irc *message );                /* 511 */
void p_ERR_TOOMANYWATCH( message_irc *message );                /* 512 */
void p_ERR_NEEDPONG( message_irc *message );            	/* 513 */
void p_ERR_TOOMANYDCC( message_irc *message );          	/* 514 */
void p_ERR_DISABLED( message_irc *message );            	/* 517 */
void p_ERR_NOINVITE( message_irc *message );            	/* 518 */
void p_ERR_ADMONLY( message_irc *message );             	/* 519 */
void p_ERR_OPERONLY( message_irc *message );            	/* 520 */
void p_ERR_LISTSYNTAX( message_irc *message );          	/* 521 */
void p_RPL_NONE( message_irc *message );                	/* 300 */
void p_RPL_AWAY( message_irc *message );                	/* 301 */
void p_RPL_USERHOST( message_irc *message );            	/* 302 */
void p_RPL_ISON( message_irc *message );                	/* 303 */
void p_RPL_TEXT( message_irc *message );                	/* 304 */
void p_RPL_UNAWAY( message_irc *message );              	/* 305 */
void p_RPL_NOWAWAY( message_irc *message );             	/* 306 */
void p_RPL_WHOISREGNICK( message_irc *message );                /* 307 */
void p_RPL_RULESSTART( message_irc *message );          	/* 308 */
void p_RPL_ENDOFRULES( message_irc *message );          	/* 309 */
void p_RPL_WHOISHELPOP( message_irc *message );                 /* 310 */
void p_RPL_WHOISUSER( message_irc *message );           	/* 311 */
void p_RPL_WHOISSERVER( message_irc *message );                 /* 312 */
void p_RPL_WHOISOPERATOR( message_irc *message );               /* 313 */
void p_RPL_WHOWASUSER( message_irc *message );          	/* 314 */
void p_RPL_ENDOFWHO( message_irc *message );            	/* 315 */
void p_RPL_ENDOFWHOWAS( message_irc *message );        		/* 369 */
void p_RPL_WHOISCHANOP( message_irc *message );                 /* 316 */
void p_RPL_WHOISIDLE( message_irc *message );           	/* 317 */
void p_RPL_ENDOFWHOIS( message_irc *message );          	/* 318 */
void p_RPL_WHOISCHANNELS( message_irc *message );               /* 319 */
void p_RPL_WHOISSPECIAL( message_irc *message );                /* 320 */
void p_RPL_LISTSTART( message_irc *message );           	/* 321 */
void p_RPL_LIST( message_irc *message );                	/* 322 */
void p_RPL_LISTEND( message_irc *message );             	/* 323 */
void p_RPL_CHANNELMODEIS( message_irc *message );               /* 324 */
void p_RPL_CREATIONTIME( message_irc *message );                /* 329 */
void p_RPL_NOTOPIC( message_irc *message );             	/* 331 */
void p_RPL_TOPIC( message_irc *message );               	/* 332 */
void p_RPL_TOPICWHOTIME( message_irc *message );                /* 333 */
void p_RPL_INVITELIST( message_irc *message );          	/* 336 */
void p_RPL_ENDOFINVITELIST( message_irc *message );             /* 337 */
void p_RPL_LISTSYNTAX( message_irc *message );          	/* 334 */
void p_RPL_WHOISBOT( message_irc *message );            	/* 335 */
void p_RPL_USERIP( message_irc *message );              	/* 340 */
void p_RPL_INVITING( message_irc *message );            	/* 341 */
void p_RPL_SUMMONING( message_irc *message );           	/* 342 */
void p_RPL_VERSION( message_irc *message );             	/* 351 */
void p_RPL_WHOREPLY( message_irc *message );            	/* 352 */
void p_RPL_ENDOFWHO( message_irc *message );            	/* 315 */
void p_RPL_NAMREPLY( message_irc *message );            	/* 353 */
void p_RPL_ENDOFNAMES( message_irc *message );          	/* 366 */
void p_RPL_INVEXLIST( message_irc *message );           	/* 346 */
void p_RPL_ENDOFINVEXLIST( message_irc *message );              /* 347 */
void p_RPL_EXLIST( message_irc *message );              	/* 348 */
void p_RPL_ENDOFEXLIST( message_irc *message );                 /* 349 */
void p_RPL_KILLDONE( message_irc *message );            	/* 361 */
void p_RPL_CLOSING( message_irc *message );             	/* 362 */
void p_RPL_CLOSEEND( message_irc *message );            	/* 363 */
void p_RPL_LINKS( message_irc *message );               	/* 364 */
void p_RPL_ENDOFLINKS( message_irc *message );          	/* 365 */
void p_RPL_ENDOFNAMES( message_irc *message );          	/* 366 */
void p_RPL_BANLIST( message_irc *message );             	/* 367 */
void p_RPL_ENDOFBANLIST( message_irc *message );                /* 368 */
void p_RPL_ENDOFWHOWASABOVE( message_irc *message );            /* 369 */
void p_RPL_INFO( message_irc *message );                	/* 371 */
void p_RPL_MOTD( message_irc *message );                	/* 372 */
void p_RPL_INFOSTART( message_irc *message );           	/* 373 */
void p_RPL_ENDOFINFO( message_irc *message );           	/* 374 */
void p_RPL_MOTDSTART( message_irc *message );           	/* 375 */
void p_RPL_ENDOFMOTD( message_irc *message );           	/* 376 */
void p_RPL_WHOISHOST( message_irc *message );           	/* 378 */
void p_RPL_WHOISMODES( message_irc *message );          	/* 379 */
void p_RPL_YOUREOPER( message_irc *message );           	/* 381 */
void p_RPL_REHASHING( message_irc *message );           	/* 382 */
void p_RPL_YOURESERVICE( message_irc *message );                /* 383 */
void p_RPL_MYPORTIS( message_irc *message );            	/* 384 */
void p_RPL_NOTOPERANYMORE( message_irc *message );              /* 385 */
void p_RPL_QLIST( message_irc *message );               	/* 386 */
void p_RPL_ENDOFQLIST( message_irc *message );          	/* 387 */
void p_RPL_ALIST( message_irc *message );               	/* 388 */
void p_RPL_ENDOFALIST( message_irc *message );          	/* 389 */
void p_RPL_TIME( message_irc *message );                	/* 391 */
void p_RPL_USERSSTART( message_irc *message );          	/* 392 */
void p_RPL_USERS( message_irc *message );               	/* 393 */
void p_RPL_ENDOFUSERS( message_irc *message );          	/* 394 */
void p_RPL_NOUSERS( message_irc *message );             	/* 395 */
void p_RPL_TRACELINK( message_irc *message );           	/* 200 */
void p_RPL_TRACECONNECTING( message_irc *message );             /* 201 */
void p_RPL_TRACEHANDSHAKE( message_irc *message );              /* 202 */
void p_RPL_TRACEUNKNOWN( message_irc *message );                /* 203 */
void p_RPL_TRACEOPERATOR( message_irc *message );               /* 204 */
void p_RPL_TRACEUSER( message_irc *message );           	/* 205 */
void p_RPL_TRACESERVER( message_irc *message );                 /* 206 */
void p_RPL_TRACESERVICE( message_irc *message );                /* 207 */
void p_RPL_TRACENEWTYPE( message_irc *message );                /* 208 */
void p_RPL_TRACECLASS( message_irc *message );          	/* 209 */
void p_RPL_STATSHELP( message_irc *message );           	/* 210 */
void p_RPL_STATSLINKINFO( message_irc *message );               /* 211 */
void p_RPL_STATSCOMMANDS( message_irc *message );               /* 212 */
void p_RPL_STATSCLINE( message_irc *message );          	/* 213 */
void p_RPL_STATSOLDNLINE( message_irc *message );               /* 214 */
void p_RPL_STATSILINE( message_irc *message );          	/* 215 */
void p_RPL_STATSKLINE( message_irc *message );          	/* 216 */
void p_RPL_STATSQLINE( message_irc *message );          	/* 217 */
void p_RPL_STATSYLINE( message_irc *message );          	/* 218 */
void p_RPL_ENDOFSTATS( message_irc *message );          	/* 219 */
void p_RPL_STATSBLINE( message_irc *message );          	/* 220 */
void p_RPL_UMODEIS( message_irc *message );             	/* 221 */
void p_RPL_SQLINE_NICK( message_irc *message );                 /* 222 */
void p_RPL_STATSGLINE( message_irc *message );          	/* 223 */
void p_RPL_STATSTLINE( message_irc *message );          	/* 224 */
void p_RPL_STATSELINE( message_irc *message );          	/* 225 */
void p_RPL_STATSNLINE( message_irc *message );          	/* 226 */
void p_RPL_STATSVLINE( message_irc *message );          	/* 227 */
void p_RPL_STATSBANVER( message_irc *message );                 /* 228 */
void p_RPL_STATSSPAMF( message_irc *message );          	/* 229 */
void p_RPL_STATSEXCEPTTKL( message_irc *message );              /* 230 */
void p_RPL_SERVICEINFO( message_irc *message );                 /* 231 */
void p_RPL_RULES( message_irc *message );               	/* 232 */
void p_RPL_SERVICE( message_irc *message );             	/* 233 */
void p_RPL_SERVLIST( message_irc *message );            	/* 234 */
void p_RPL_SERVLISTEND( message_irc *message );                 /* 235 */
void p_RPL_STATSLLINE( message_irc *message );          	/* 241 */
void p_RPL_STATSUPTIME( message_irc *message );                 /* 242 */
void p_RPL_STATSOLINE( message_irc *message );          	/* 243 */
void p_RPL_STATSHLINE( message_irc *message );          	/* 244 */
void p_RPL_STATSSLINE( message_irc *message );          	/* 245 */
void p_RPL_STATSXLINE( message_irc *message );          	/* 247 */
void p_RPL_STATSULINE( message_irc *message );          	/* 248 */
void p_RPL_STATSDEBUG( message_irc *message );          	/* 249 */
void p_RPL_STATSCONN( message_irc *message );           	/* 250 */
void p_RPL_LUSERCLIENT( message_irc *message );                 /* 251 */
void p_RPL_LUSEROP( message_irc *message );             	/* 252 */
void p_RPL_LUSERUNKNOWN( message_irc *message );                /* 253 */
void p_RPL_LUSERCHANNELS( message_irc *message );               /* 254 */
void p_RPL_LUSERME( message_irc *message );             	/* 255 */
void p_RPL_ADMINME( message_irc *message );             	/* 256 */
void p_RPL_ADMINLOC1( message_irc *message );            	/* 257 */
void p_RPL_ADMINLOC2( message_irc *message );            	/* 258 */
void p_RPL_ADMINEMAIL( message_irc *message );          	/* 259 */
void p_RPL_TRACELOG( message_irc *message );            	/* 261 */
void p_RPL_LOCALUSERS( message_irc *message );          	/* 265 */
void p_RPL_GLOBALUSERS( message_irc *message );                 /* 266 */
void p_RPL_SILELIST( message_irc *message );            	/* 271 */
void p_RPL_ENDOFSILELIST( message_irc *message );               /* 272 */
void p_RPL_STATSDLINE( message_irc *message );          	/* 275 */
void p_RPL_HELPHDR( message_irc *message );             	/* 290 */
void p_RPL_HELPOP( message_irc *message );              	/* 291 */
void p_RPL_HELPTLR( message_irc *message );             	/* 292 */
void p_RPL_HELPHLP( message_irc *message );             	/* 293 */
void p_RPL_HELPFWD( message_irc *message );             	/* 294 */
void p_RPL_HELPIGN( message_irc *message );             	/* 295 */
void p_RPL_MAP( message_irc *message );                 	/* 006 */
void p_RPL_MAPMORE( message_irc *message );             	/* 610 */
void p_RPL_MAPEND( message_irc *message );              	/* 007 */
void p_ERR_WHOSYNTAX( message_irc *message );           	/* 522 */
void p_ERR_WHOLIMEXCEED( message_irc *message );                /* 523 */
void p_ERR_OPERSPVERIFY( message_irc *message );                /* 524 */
void p_RPL_SNOMASK( message_irc *message );             	/* 008 */
void p_RPL_LOGON( message_irc *message );               	/* 600 */
void p_RPL_LOGOFF( message_irc *message );              	/* 601 */
void p_RPL_WATCHOFF( message_irc *message );            	/* 602 */
void p_RPL_WATCHSTAT( message_irc *message );           	/* 603 */
void p_RPL_NOWON( message_irc *message );               	/* 604 */
void p_RPL_NOWOFF( message_irc *message );              	/* 605 */
void p_RPL_WATCHLIST( message_irc *message );           	/* 606 */
void p_RPL_ENDOFWATCHLIST( message_irc *message );              /* 607 */
void p_RPL_DCCSTATUS( message_irc *message );           	/* 617 */
void p_RPL_DCCLIST( message_irc *message );             	/* 618 */
void p_RPL_ENDOFDCCLIST( message_irc *message );                /* 619 */
void p_RPL_DCCINFO( message_irc *message );             	/* 620 */
void p_RPL_DUMPING( message_irc *message );             	/* 640 */
void p_RPL_DUMPRPL( message_irc *message );             	/* 641 */
void p_RPL_EODUMP( message_irc *message );              	/* 642 */
void p_RPL_SPAMCMDFWD( message_irc *message );          	/* 659 */
void p_RPL_WHOISSECURE( message_irc *message );         	/* 671 */
void p_ERR_CANNOTDOCOMMAND( message_irc *message );             /* 972 */
void p_ERR_CANNOTCHANGECHANMODE( message_irc *message );        /* 974 */
void p_ERR_NUMERICERR( message_irc *message );          	/* 999 */

#endif


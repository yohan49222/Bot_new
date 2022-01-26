#include "main.h"

/**
	verifi si la regex str_regex est valide
**/
int verif_compile(const char *str_regex)
{
	regex_t preg;
	int err;

	err = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED | REG_ICASE);

	return err;
}

/**
	verifi si str_request correspond a la regex str_regex
**/
int verif_pattern(const char *str_regex , const char *str_request)
{
	regex_t preg;
	int match;

	match = regcomp (&preg, str_regex, REG_NOSUB | REG_EXTENDED);
	if(match == 0)
	{

		match = regexec (&preg, str_request, 0, NULL, 0);
		regfree (&preg);
		return match;
	}
	return -2;
}





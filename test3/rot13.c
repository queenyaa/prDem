#include "main.h"
/**
 * pr_rot13 - encrypts string with rot13
 * @args: string to change
 * Return: modified string
 */
char *pr_rot13(va_list args)
{
	int x = 0;
	char *str;
	char *pstr;

	/* store va_arg to only access argument once */
	str = va_arg(args, char *);

	/* malloc new variable to assign over new rot13 characters */
	pstr = malloc(sizeof(char) * (_strlen(str) + 1));
	if (pstr == NULL)
		return (NULL);

	/* iterate str and assign rot13 char to nstr */
	while (str[x] != '\0')
	{
		if ((str[x] >= 'a' && str[x] <= 'm') || (str[x] >= 'A' && str[x] <= 'M'))
		{
			pstr[x] = str[x] + 13;
		}
		else if ((str[x] >= 'n' && str[x] <= 'z') || (str[x] >= 'N' && str[x] <= 'Z'))
		{
			pstr[x] = str[x] - 13;
		}
		else
			(pstr[x] = str[x]);
		x++;
	}
	pstr[x] = '\0';

	return (pstr);
}

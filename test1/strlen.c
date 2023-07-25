#include "main.h"

/**
 * _strlen - prints length string in integer
 * @s: string passed to function
 * Return: a
 */
int _strlen(char *s)
{
	int w = 0;

	while (s[w] != '0')
		w++;

	return (w);
}


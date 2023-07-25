#include "main.h"

unsigned int pr_wth(buff_t *out, unsigned int printed,
		unsigned char flgs, int wth);
unsigned int pr_str_wth(buff_t *out,
		unsigned char flgs, int wth, int prec, int size);
unsigned int pr_nwth(buff_t *out, unsigned int printed,
		unsigned char flgs, int wth);

/**
 * pr_wth - Stores leading spaces to a buffer for a width modifier.
 * @out: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int pr_wth(buff_t *out, unsigned int printed,
		unsigned char flgs, int wth)
{
	unsigned int t = 0;
	char bth = ' ';

	if (NEG_FLG == 0)
	{
		for (wth -= printed; wth > 0;)
			t += _memcpy(out, &bth, 1);
	}

	return (t);
}

/**
 * pr_str_wth - Stores leading spaces to a buffer for a width modifier.
 * @out: A buffer_t struct containing a character array.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @sz: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int pr_str_wth(buff_t *out,
		unsigned char flgs, int wth, int prec, int sz)
{
	unsigned int t = 0;
	char bth = ' ';

	if (NEG_FLG == 0)
	{
		wth -= (prec == -1) ? sz : prec;
		for (; wth > 0; wth--)
			t += _memcpy(out, &bth, 1);
	}

	return (t);
}

/**
 * pr_nwth - Stores trailing spaces to a buffer for a '-' flag.
 * @out: A buffer_t struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int pr_nwth(buff_t *out, unsigned int printed,
		unsigned char flgs, int wth)
{
	unsigned int t = 0;
	char bth = ' ';

	if (NEG_FLG == 1)
	{
		for (wth -= printed; wth > 0; wth--)
			t += _memcpy(out, &bth, 1);
	}

	return (t);
}

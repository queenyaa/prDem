#include "main.h"

unsigned int conv_sbase(buff_t *out, long int num, char *base,
		unsigned char flgs, int wth, int prec);
unsigned int conv_ubase(buff_t *out,
		unsigned long int num, char *base,
		unsigned char flgs, int wth, int prec);

/**
 * conv_sbase - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @out: A buffer_t struct containing a character array.
 * @num: A signed long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_sbase(buff_t *out, long int num, char *base,
		unsigned char flgs, int wth, int prec)
{
	int sz;
	char digit, pad = '0';
	unsigned int t = 1;

	for (sz = 0; *(base + sz);)
		sz++;

	if (num >= sz || num <= -sz)
		t += conv_sbase(out, num / sz, base,
				flgs, wth - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, wth--) /* Handle precision */
			t += _memcpy(out, &pad, 1);

		if (NEG_FLG == 0) /* Handle width */
		{
			pad = (ZERO_FLG == 1) ? '0' : ' ';
			for (; wth > 1; wth--)
				t += _memcpy(out, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % sz)];
	_memcpy(out, &digit, 1);

	return (t);
}

/**
 * conv_ubase - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @out: A buffer_t struct containing a character array.
 * @num: An unsigned long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_ubase(buff_t *out, unsigned long int num, char *base,
		unsigned char flgs, int wth, int prec)
{
	unsigned int sz, t = 1;
	char digit, pad = '0', *lead = "0x";

	for (sz = 0; *(base + sz);)
		sz++;

	if (num >= sz)
		t += conv_ubase(out, num / sz, base,
				flgs, wth - 1, prec - 1);

	else
	{
		if (((flgs >> 5) & 1) == 1) /* Printing a ptr address */
		{
			wth -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wth--) /* Handle precision */
			t += _memcpy(out, &pad, 1);

		if (NEG_FLG == 0) /* Handle width */
		{
			pad = (ZERO_FLG == 1) ? '0' : ' ';
			for (; wth > 1; wth--)
				t += _memcpy(out, &pad, 1);
		}
		if (((flgs >> 5) & 1) == 1) /* Print 0x for ptr address */
			t += _memcpy(out, lead, 2);
	}

	digit = base[(num % sz)];
	_memcpy(out, &digit, 1);

	return (t);
}

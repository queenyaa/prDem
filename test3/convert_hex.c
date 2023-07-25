#include "main.h"

unsigned int conv_x(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_X(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);

/**
 * conv_x - Converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @out: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_x(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int t = 0;
	char *ld = "0x";

	if (len == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLG == 1 && num != 0)
		t += _memcpy(out, ld, 2);

	if (!(num == 0 && prec == 0))
		t += conv_ubase(out, num, "0123456789abcdef",
				flgs, wth, prec);

	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

/**
 * conv_X - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @out: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_X(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	unsigned long int num;
	unsigned int t = 0;
	char *ld = "0X";

	if (len == LONG)
		num = va_arg(args, unsigned long);
	else
		num = va_arg(args, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLG == 1 && num != 0)
		t += _memcpy(out, ld, 2);

	if (!(num == 0 && prec == 0))
		t += conv_ubase(out, num, "0123456789ABCDEF",
				flgs, wth, prec);

	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

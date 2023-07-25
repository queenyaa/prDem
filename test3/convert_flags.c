#include "main.h"

unsigned int conv_c(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_percent(va_list args, buff_t *out,
		unsigned char flags, int wth, int prec, unsigned char len);
unsigned int conv_p(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);

/**
 * conv_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @out: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_c(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char c;
	unsigned int t = 0;

	(void)prec;
	(void)len;

	c = va_arg(args, int);

	t += pr_wth(out, t, flgs, wth);
	t += _memcpy(out, &c, 1);
	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

/**
 * conv_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @out: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int conv_percent(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char percent = '%';
	unsigned int t = 0;

	(void)args;
	(void)prec;
	(void)len;

	t += pr_wth(out, t, flgs, wth);
	t += _memcpy(out, &percent, 1);
	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

/**
 * conv_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @out: A buff_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_p(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int addr;
	unsigned int t = 0;

	(void)len;

	addr = va_arg(args, unsigned long int);
	if (addr == '\0')
		return (_memcpy(out, null, 5));

	flgs |= 32;
	t += conv_ubase(out, addr, "0123456789abcdef",
			flgs, wth, prec);
	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

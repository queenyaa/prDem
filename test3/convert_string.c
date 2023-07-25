#include "main.h"

unsigned int conv_s(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_S(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_r(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);
unsigned int conv_R(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len);

/**
 * conv_s - Converts an argument to a string and
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
unsigned int conv_s(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int sz;
	unsigned int t = 0;

	(void)flgs;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(out, null, 6));

	for (sz = 0; *(str + sz);)
		sz++;

	t += pr_str_wth(out, flgs, wth, prec, sz);

	prec = (prec == -1) ? sz : prec;
	while (*str != '\0' && prec > 0)
	{
		t += _memcpy(out, str, 1);
		prec--;
		str++;
	}

	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

/**
 * conv_S - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @out: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int conv_S(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int sz, ind;
	unsigned int t = 0;

	(void)len;
	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(out, null, 6));

	for (sz = 0; str[sz];)
		sz++;

	t += pr_str_wth(out, flgs, wth, prec, sz);

	prec = (prec == -1) ? sz : prec;
	for (ind = 0; *(str + ind) != '\0' && ind < prec; ind++)
	{
		if (*(str + ind) < 32 || *(str + ind) >= 127)
		{
			t += _memcpy(out, hex, 2);
			if (*(str + ind) < 16)
				t += _memcpy(out, &zero, 1);
			t += conv_ubase(out, *(str + ind),
						 "0123456789ABCDEF", flgs, 0, 0);
			continue;
		}
		t += _memcpy(out, (str + ind), 1);
	}

	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

/**
 * conv_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_r(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char *str, *null = "(null)";
	int sz, end, x;
	unsigned int t = 0;

	(void)flgs;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(out, null, 6));

	for (sz = 0; *(str + sz);)
		sz++;

	t += pr_str_wth(out, flgs, wth, prec, sz);

	end = sz - 1;
	prec = (prec == -1) ? sz : prec;
	for (x = 0; end >= 0 && x < prec; x++)
	{
		t += _memcpy(out, (str + end), 1);
		end--;
	}

	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

/**
 * conv_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be converted.
 * @flgs: Flag modifiers.
 * @wth: A width modifier.
 * @prec: A precision modifier.
 * @len: A lenth modifier.
 * @out: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_R(va_list args, buff_t *out,
		unsigned char flgs, int wth, int prec, unsigned char len)
{
	char *lett = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int x, y, sz;
	unsigned int t = 0;

	(void)flgs;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(out, null, 6));

	for (sz = 0; *(str + sz);)
		sz++;

	t += pr_str_wth(out, flgs, wth, prec, sz);

	prec = (prec == -1) ? sz : prec;
	for (x = 0; *(str + x) != '\0' && x < prec; x++)
	{
		for (y = 0; y < 52; y++)
		{
			if (*(str + x) == *(lett + y))
			{
				t += _memcpy(out, (rot13 + y), 1);
				break;
			}
		}
		if (y == 52)
			t += _memcpy(out, (str + x), 1);
	}

	t += pr_nwth(out, t, flgs, wth);

	return (t);
}

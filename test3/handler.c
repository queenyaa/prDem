#include "main.h"

unsigned char h_flgs(const char *flg, char *ind);
unsigned char h_length(const char *modifier, char *ind);
int h_wth(va_list args, const char *modifier, char *ind);
int h_p(va_list args, const char *modifier, char *ind);
unsigned int (*h_spec(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char);

/**
 * h_flgs - Matches flags with corresponding values.
 * @flg: A pointer to a potential string of flags.
 * @ind: An index counter for the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char h_flgs(const char *flg, char *ind)
{
	int x, y;
	unsigned char t = 0;
	flg_t flgs[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (x = 0; flg[x]; x++)
	{
		for (y = 0; flgs[y].flg != 0; y++)
		{
			if (flg[x] == flgs[y].flg)
			{
				(*ind)++;
				if (t == 0)
					t = flgs[y].val;
				else
					t |= flgs[y].val;
				break;
			}
		}
		if (flgs[y].val == 0)
			break;
	}

	return (t);
}

/**
 * h_length - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @ind: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char h_length(const char *modifier, char *ind)
{
	if (*modifier == 'h')
	{
		(*ind)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*ind)++;
		return (LONG);
	}

	return (0);
}

/**
 * h_wth - Matches a width modifier with its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @ind: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int h_wth(va_list args, const char *modifier, char *ind)
{
	int val = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*ind)++;

		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
				return (0);
			return (val);
		}

		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}

	return (val);
}

/**
 * h_p - Matches a precision modifier with
 *                    its corresponding value.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @ind: An index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int h_p(va_list args, const char *modifier, char *ind)
{
	int val = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*ind)++;

	if ((*modifier <= '0' || *modifier > '9') &&
		 *modifier != '*')
	{
		if (*modifier == '0')
			(*ind)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
		   (*modifier == '*'))
	{
		(*ind)++;

		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
				return (0);
			return (val);
		}

		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}

	return (val);
}

/**
 * h_spec - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @spec: A pointer to a potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*h_spec(const char *specifier))(va_list, buff_t *,
		unsigned char, int, int, unsigned char)
{
	int x;
	convert_t converts[] = {
		{'c', conv_c},
		{'s', conv_s},
		{'d', conv_di},
		{'i', conv_di},
		{'%', conv_percent},
		{'b', conv_b},
		{'u', conv_u},
		{'o', conv_o},
		{'x', conv_x},
		{'X', conv_X},
		{'S', conv_S},
		{'p', conv_p},
		{'r', conv_r},
		{'R', conv_R},
		{0, NULL}
	};

	for (x = 0; converts[x].bf; x++)
	{
		if (converts[x].specifier == *specifier)
			return (converts[x].bf);
	}

	return (NULL);
}

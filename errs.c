#include "shell.h"

/**
 * rm_coms - replaces first instance of '#' with '\0'
 * @b: the buffer
 *
 * Return: 0
 */
void rm_coms(char *b)
{
	int a;

	for (a = 0; b[a] != '\0'; a++)
	{
		if (b[a] == '#' && (!a || b[a - 1] == ' '))
		{
			b[a] = '\0';
			break;
		}
	}
}
/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int i;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: 0 or -1
 */
void print_err(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	_deci(info->lc, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * _deci - prints decimal number
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int _deci(int input, int fd)
{
	int (*_pc)(char) = _putchar;
	int a, b = 0;
	unsigned int d, c;

	if (fd == STDERR_FILENO)
		_pc = _puterr;
	if (input < 0)
	{
		d = -input;
		_pc('-');
		b++;
	}
	else
		d = input;
	c = d;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (d / a)
		{
			_pc('0' + c / a);
			b++;
		}
		c %= a;
	}
	_pc('0' + c);
	b++;

	return (b);
}

/**
 * conv_num - convert func
 * @num: number
 * @base: base number
 * @flags: arg flags
 *
 * Return: string
 */
char *conv_num(long int num, int base, int flags)
{
	static char *array, buffer[50];
	char sign = 0, *a;
	unsigned long n = num;

	if (!(flags & CONV_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONV_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	a = &buffer[49];
	*a = '\0';

	do {
		*--a = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--a = sign;
	return (a);
}

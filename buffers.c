#include "shell.h"

/**
 * check_ch - checks chain
 * @in: potential arguments
 * @b: char buffer
 * @a: address in buffer
 * @c: beginning pos
 * @d: length
 */

void check_ch(info_t *in, char *b, size_t *a, size_t c, size_t d)
{
	size_t e = *a;

	if (in->c_type == OR_C)
	{
		if (!in->status)
		{
			b[c] = 0;
			e = d;
		}
	}
	if (in->c_type == AND_C)
	{
		if (in->status)
		{
			b[c] = 0;
			e = d;
		}
	}
	*a = e;
}

/**
 * _chain - checks if delimiter
 * @in: potential arguments
 * @b: char buffer
 * @a: address in buffer
 *
 * Return: 1 or 0
 */

int _chain(info_t *in, char *b, size_t *a)
{
	size_t c = *a;

	if (b[c] == '&' && b[c + 1] == '&')
	{
		b[c] = 0;
		++c;
		in->c_type = AND_C;
	}
	else if (b[c] == '|' && b[c + 1] == '|')
	{
		b[c] = 0;
		++c;
		in->c_type = OR_C;
	}
	else if (b[c] == ';')
	{
		b[c] = 0;
		in->c_type = CHAIN_;
	}
	else
		return (0);
	*a = c;
	return (1);
}

/**
 * _ncpy - copies string
 * @dest: destination string
 * @src: source
 * @n: char buffer
 *
 * Return: ncat string
 */

char *_ncpy(char *dest, char *src, int n)
{
	char *a = dest;
	int b, c;

	for (b = 0; src[b] != '\0' && b < n - 1; ++b)
		dest[b] = src[b];
	if (b < n)
	{
		for (c = b; c < n; ++c)
			dest[c] = '\0';
	}
	return (a);
}

/**
 * get_in - gets newline
 * @in: potential arguments
 *
 * Return: 0
 */
ssize_t get_in(info_t *in)
{
	char *a, **buffer = &(in->arg);
	static char *b;
	ssize_t c = 0;
	static size_t x, y, z;

	_putchar(FLUSH_B);
	c = buf_in(in, &b, &z);
	if (c == -1)
		return (-1);
	if (z)
	{
		y = x;
		a = b + x;
		check_ch(in, b, &y, x, z);
		while (y < z)
		{
			if (_chain(in, b, &y))
				break;
			y++;
		}
		x = y + 1;
		if (x >= z)
		{
			x = z = 0;
			in->c_type = NORM_C;
		}
		*buffer = a;
		return (_len(a));
	}
	*buffer = b;
	return (c);
}

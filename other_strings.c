#include "shell.h"

/**
 * starts_w - finds a substring in a string
 * @a: string
 * @b: substring
 *
 * Return: a
 */

char *starts_w(const char *a, const char *b)
{
	while (*b)
		if (*b++ != *a++)
			return (NULL);
	return ((char *)b);
}

/**
 * _putchar - writes char to stdout
 * @c: char
 *
 * Return: 1 or -1
 */

int _putchar(char c)
{
	static char b[WRITE_SIZE];
	static int a;

	if (c == FLUSH_B || a >= WRITE_SIZE)
	{
		write(1, b, a);
		a = 0;
	}
	if (c != FLUSH_B)
		b[a++] = c;
	return (1);
}

/**
 * _puts - prints input string
 * @s: string
 */

void _puts(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_putchar(s[a]);
		a++;
	}
}

/**
 * _dup - duplicates string
 * @s: string
 *
 * Return: duplicate
 */

char *_dup(const char *s)
{
	char *r;
	int t = 0;

	if (s == NULL)
		return (NULL);
	while (*s++)
		t++;
	r = malloc(sizeof(char) * (t + 1));
	if (!r)
		return (NULL);
	for (t++; t--;)
		r[t] = *--s;
	return (r);
}

/**
 * _cpy - copies string
 * @dest: destination
 * @src: source
 *
 * Return: dest
 */

char *_cpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}

	dest[a] = 0;
	return (dest);
}

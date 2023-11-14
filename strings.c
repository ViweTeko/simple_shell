#include "shell.h"

/**
 * _chr - finds char in string
 * @s: string
 * @c: char
 *
 * Return: s
 */

char *_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++);
	return (NULL);
}

/**
 * _ncat - concats a string
 * @dest: first string
 * @src: second string
 * @n: number of bytes
 *
 * Return: dest
 */

char *_ncat(char *dest, char *src, int n)
{
	char *a = dest;
	int b = 0, c = 0;

	while (dest[b] != '\0')
		c++;
	while (src[c] != '\0' && c < n)
	{
		dest[b] = src[c];
		++b;
		++c;
	}
	if (c < n)
		dest[b] = '\0';
	return (a);
}
/**
 * _cat - concates two strings
 * @dest: destination
 * @src: source
 *
 * Return: dest
 */

char *_cat(char *dest, char *src)
{
	char *a = dest;

	while (*dest != '\0')
		dest++;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = *src;

	return (a);
}

/**
 * _cmp - compares two strings
 * @a: first string
 * @b: second string
 *
 * Return: neg, pos, or 0
 */

int _cmp(char *a, char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	if (*a == *b)
		return (0);
	else
		return (*a < *b ? -1 : 1);
}

/**
 * _len - length of string
 * @s: string
 *
 * Return: length
 */

int _len(char *s)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s++)
		a++;

	return (a);
}


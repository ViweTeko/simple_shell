#include "shell.h"

/**
 * _putfd - writes c to fd
 * @c: char to print
 * @fd: file descriptor
 *
 * Return: 1 or -1
 */
int _putfd(char c, int fd)
{
	static int a;
	static char b[WRITE_SIZE];

	if (c == FLUSH_B || a >= WRITE_SIZE)
	{
		write(fd, b, a);
		a = 0;
	}
	if (c != FLUSH_B)
		b[a++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @s: string to be printed
 * @fd: the file descriptor
 *
 * Return: number of chars put
 */
int _putsfd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putfd(*s++, fd);
	}
	return (i);
}

/**
 * _puterr - writes char to stderr
 * @c: char to print
 *
 * Return: 1 or -1
 */
int _puterr(char c)
{
	static int a;
	static char b[WRITE_SIZE];

	if (c == FLUSH_B || a >= WRITE_SIZE)
	{
		write(2, b, a);
	a = 0;
	}
	if (c != FLUSH_B)
		b[a++] = c;
	return (1);
}

/**
 * _eputs - prints an input string
 * @s: string to be printed
 *
 */
void _eputs(char *s)
{
	int a;

	if (!s)
		return;
	for (a = 0; s[a] != '\0'; ++a)
		_puterr(s[a]);
}

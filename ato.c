#include "shell.h"

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 or 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * inter - returns true if shell is interactive mode
 * @in: struct address
 *
 * Return: 1 or 0
 */

int inter(info_t *in)
{
	return (isatty(STDIN_FILENO) && in->fd_rd <= 2);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int r, sign = 1, flag = 0, out;
	unsigned int result = 0;

	for (r = 0; s[r] != '\0' && flag != 2; r++)
	{
		if (s[r] == '-')
			sign *= -1;

		if (s[r] >= '0' && s[r] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[r] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -result;
	else
		out = result;

	return (out);
}
/**
 * _delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 *
 * Return: 1 if true, 0 if false
 */
int _delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _memset - fills memory with bytes
 * @s: string
 * @b: byte(s)
 * @n: amount of bytes
 *
 * Return: s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; ++a)
		s[a] = b;
	return (s);
}

#include "shell.h"

/**
 * print_list - prints all nodes of list
 * @h: address of node
 *
 * Return: list
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_len - length of list
 * @h: address of node
 *
 * Return: 0
 */

size_t list_len(const list_t *h)
{
	size_t a;

	for (a = 0; h != NULL; ++a)
		h = h->next;

	return (a);
}

/**
 * print_s_list - prints string of list
 * @h: address of node
 *
 * Return: h
 */

size_t print_s_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->s ? h->s : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * strings_list - a list of strings
 * @h: address of node
 *
 * Return: array of s
 */

char **strings_list(list_t *h)
{
	char *s;
	char **st;
	size_t a, b = list_len(h);
	list_t *g = h;

	if (!h || !b)
		return (NULL);
	st = malloc(sizeof(char *) * (b + 1));
	if (!st)
		return (NULL);
	for (b = 0; g; g = g->next, b++)
	{
		s = malloc(_len(g->s) + 1);
		if (!s)
		{
			for (a = 0; a < b; a++)
				free(st[a]);
			free(st);
			return (NULL);
		}
		s = _cpy(s, g->s);
		st[b] = s;
	}
	st[b] = NULL;
	return (st);
}

/**
 * pre_node - node starting with prefix
 * @h: address of node
 * @pre: the prefix
 * @c: following char
 *
 * Return: h or NULL
 */

list_t *pre_node(list_t *h, char *pre, char c)
{
	char *a = NULL;

	while (h)
	{
		a = starts_w(h->s, pre);
		if (a && ((c == -1) || (*a == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}


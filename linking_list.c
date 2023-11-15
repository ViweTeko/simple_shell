#include "shell.h"

/**
 * node_add - adds node at beginning
 * @h: address of node
 * @s: string
 * @num: num of node
 *
 * Return: linked list
 */

list_t *node_add(list_t **h, const char *s, int num)
{
	list_t *g;

	if (!h)
		return (NULL);
	g = malloc(sizeof(list_t));
	if (!g)
		return (NULL);
	_memset((void *)g, 0, sizeof(list_t));
	g->num = num;
	if (s)
	{
		g->s = _dup(s);
		if (!g->s)
		{
			free(g);
			return (NULL);
		}
	}
	g->next = *h;
	*h = g;
	return (g);
}

/**
 * node_end - adds node to end of list
 * @h: address of node
 * @s: string
 * @num: num of node
 *
 * Return: linked list
 */

list_t *node_end(list_t **h, const char *s, int num)
{
	list_t *g, *f;

	if (!h)
		return (NULL);
	f = *h;
	g = malloc(sizeof(list_t));
	if (!g)
		return (NULL);
	_memset((void *)g, 0, sizeof(list_t));
	g->num = num;
	if (s)
	{
		g->s = _dup(s);
		if (!g->s)
		{
			free(g);
			return (NULL);
		}
	}
	if (f)
	{
		while (f->next)
			f = f->next;
		f->next = g;
	}
	else
		*h = g;
	return (g);
}

/**
 * get_index - gets node index
 * @h: address of list
 * @node: the node
 *
 * Return: node or -1
 */

ssize_t get_index(list_t *h, list_t *node)
{
	size_t a = 0;

	while (h)
	{
		if (h == node)
			return (a);
		h = h->next;
		a++;
	}
	return (-1);
}

/**
 * delete_node - deletes node
 * @h: address to node
 * @index: index to delete
 *
 * Return: 1 or 0
 */

int delete_node(list_t **h, unsigned int index)
{
	unsigned int a = 0;
	list_t *g, *i;

	if (!*h || !h)
		return (0);
	if (!index)
	{
		i = *h;
		*h = (*h)->next;
		free(i->s);
		free(i);
		return (1);
	}
	i = *h;
	while (i)
	{
		if (a == index)
		{
			g->next = i->next;
			free(i->s);
			free(i);
			return (1);
		}
		a++;
		g = i;
		i = i->next;
	}
	return (0);
}

/**
 * list_free - frees all nodes of list
 * @h: address of node
 */

void list_free(list_t **h)
{
	list_t *g, *i, *hd;

	if (!*h || !h)
		return;
	hd = *h;
	g = hd;
	while (g)
	{
		i = g->next;
		free(g->s);
		free(g);
		g = i;
	}
	*h = NULL;
}


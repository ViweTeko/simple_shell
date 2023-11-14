#include "shell.h"
/**
 * set_ali - sets alias to string
 * @in: potential arguments
 * @st: string alias
 *
 * Return: 0 or 1
 */
int set_ali(info_t *in, char *st)
{
	char *p;

	p = _chr(st, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_ali(in, st));

	unset_ali(in, st);
	return (node_end(&(in->alias), st, 0) == NULL);
}

/**
 * unset_ali - unsets alias from string
 * @in: potential arguments
 * @st: the string alias
 *
 * Return: 0 or 1
 */
int unset_ali(info_t *in, char *st)
{
	char *p, c;
	int r;

	p = _chr(st, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	r = delete_node(&(in->alias),
		get_index(in->alias, pre_node(in->alias, st, -1)));
	*p = c;
	return (r);
}

/**
 * print_ali - prints an alias string
 * @node: the alias node
 *
 * Return: 0 or 1
 */
int print_ali(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _chr(node->s, '=');
		for (a = node->s; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin
 * @in: potential arguments
 *
 *  Return: Always 0
 */
int _alias(info_t *in)
{
	char *p = NULL;
	int a = 0;
	list_t *node = NULL;

	if (in->argc == 1)
	{
		node = in->alias;
		while (node)
		{
			print_ali(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; in->argv[a]; a++)
	{
		p = _chr(in->argv[a], '=');
		if (p)
			set_ali(in, in->argv[a]);
		else
			print_ali(pre_node(in->alias, in->argv[a], '='));
	}

	return (0);
}

/**
 * my_hist - displays the history list
 * @in: potential arguments
 *
 * Return: 0
 */
int my_hist(info_t *in)
{
	print_list(in->history);
	return (0);
}

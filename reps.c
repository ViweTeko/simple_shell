#include "shell.h"

/**
 * rep_ali - replaces alias
 * @in: potential arguments
 *
 * Return: 1 or 0
 */

int rep_ali(info_t *in)
{
	char *a;
	int b;
	list_t *c;

	for (b = 0; b < 10; b++)
	{
		c = pre_node(in->alias, in->argv[0], '=');
		if (!c)
			return (0);
		free(in->argv[0]);
		a = _chr(c->s, '=');
		if (!a)
			return (0);
		a = _dup(a + 1);
		if (!a)
			return (0);
		in->argv[0] = a;
	}
	return (1);
}

/**
 * rep_s - replaces string
 * @o: string to be replaced
 * @n: replacer
 *
 * Return: 1 or 0
 */

int rep_s(char **o, char *n)
{
	free(*o);
	*o = n;

	return (1);
}
/**
 * rep_e - replaces variables in tokens
 * @in: potential arguments
 *
 * Return: 1 or 0
 */

int rep_e(info_t *in)
{
	list_t *b;
	int a;

	for (a = 0; in->argv[a]; a++)
	{
		if (in->argv[a][0] != '$' || !in->argv[a][1])
			continue;
		if (!_cmp(in->argv[a], "$?"))
		{
			rep_s(&(in->argv[a]), _dup(conv_num(in->status, 10, 0)));
			continue;
		}
		if (!_cmp(in->argv[a], "$$"))
		{
			rep_s(&(in->argv[a]), _dup(conv_num(getpid(), 10, 0)));
			continue;
		}
		b = pre_node(in->env, &in->argv[a][1], '=');
		if (b)
		{
			rep_s(&(in->argv[a]), _dup(_chr(b->s, '=') + 1));
			continue;
		}
		rep_s(&in->argv[a], _dup(""));
	}
	return (0);
}

/**
 * setter - sets info struct
 * @in: info struct
 * @argv: argument vector
 */

void setter(info_t *in, char *argv[])
{
	int a;

	in->fname = argv[0];
	if (in->arg)
	{
		in->argv = stow(in->arg, " \t");
		if (!in->argv)
		{
			in->argv = malloc(sizeof(char *) * 2);
			if (in->argv)
			{
				in->argv[0] = _dup(in->arg);
				in->argv[1] = NULL;
			}
		}
		for (a = 0; in->argv && in->argv[a]; a++)
			;
		in->argc = a;
		rep_ali(in);
		rep_e(in);
	}
}


#include "shell.h"

/**
 * get_env - gets the value of an environ variable
 * @in: Potential arguments
 * @name: environment name
 *
 * Return: the value
 */
char *get_env(info_t *in, const char *name)
{
	list_t *h = in->env;
	char *a;

	while (h)
	{
		a = starts_w(h->s, name);
		if (a && *a)
			return (a);
		h = h->next;
	}
	return (NULL);
}

/**
 * my_env - prints current environment
 * @in: Potential arguments
 *
 * Return: 0
 */
int my_env(info_t *in)
{
	print_s_list(in->env);

	return (0);
}
/**
 * my_setenv - initialize new environment variable
 * @in: Potential arguments
 *
 *  Return: 0
 */
int my_setenv(info_t *in)
{
	if (in->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(in, in->argv[1], in->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @in: Potential arguments
 *
 * Return: 0
 */
int my_unsetenv(info_t *in)
{
	int a;

	if (in->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (a = 1; a <= in->argc; a++)
		un_setenv(in, in->argv[a]);

	return (0);
}

/**
 * pop_list - populates environ linked list
 * @in: Potential arguments
 *
 * Return: 0
 */
int pop_list(info_t *in)
{
	list_t *node = NULL;
	size_t u;

	for (u = 0; environ[u]; u++)
		node_end(&node, environ[u], 0);
	in->env = node;
	return (0);
}

#include "shell.h"

/**
 * set_env - sets a new environment variable
 * @in: potential arguments
 * @e: string environment
 * @val: environ value
 *
 * Return: 0
 */
int set_env(info_t *in, char *e, char *val)
{
	list_t *c;
	char *a, *b = NULL;

	if (!e || !val)
		return (0);
	b = malloc(_len(e) + _len(val) + 2);
	if (!b)
		return (1);
	_cpy(b, e);
	_cat(b, "=");
	_cat(b, val);
	c = in->env;

	while (c)
	{
		a = starts_w(c->s, e);
		if (a && *a == '=')
		{
			free(c->s);
			c->s = b;
			in->changed_env = 1;
			return (0);
		}
		c = c->next;
	}
	node_end(&(in->env), b, 0);
	free(b);
	in->changed_env = 1;
	return (0);
}

/**
 * un_setenv - removes envirnment variable
 * @in: potential arguments
 * @e: string environment
 *
 * Return: 1 or 0
 */

int un_setenv(info_t *in, char *e)
{
	char *a;
	size_t b = 0;
	list_t *c = in->env;

	if (!e || !c)
		return (0);
	while (c)
	{
		a = starts_w(c->s, e);
		if (a && *a == '=')
		{
			in->changed_env = delete_node(&(in->env), b);
			b = 0;
			c = in->env;
			continue;
		}
		c = c->next;
		b++;
	}
	return (in->changed_env);
}

/**
 * get_envir - gets the environment copy
 * @in: potential arguments
 *
 * Return: 0
 */

char **get_envir(info_t *in)
{
	if (!in->environ || in->changed_env)
	{
		in->environ = strings_list(in->env);
		in->changed_env = 0;
	}
	return (in->environ);
}

/**
 * find_built - looks for builtin cmd
 * @in: potential arguments
 *
 * Return: -1, 0, 1, or 2
 */

int find_built(info_t *in)
{
	int a, b = -1;
	table_b z[] = {
		{"exit", e_xit}, {"env", my_env},
		{"help", _help}, {"cd", _cd},
		{"unsetenv", my_unsetenv}, {"setenv", my_setenv},
		{"history", my_hist}, {"alias", _alias},
		{NULL, NULL}
	};

	for (a = 0; z[a].type; a++)
		if (_cmp(in->argv[0], z[a].type) == 0)
		{
			in->lc++;
			b = z[a].func(in);
			break;
		}
	return (b);
}

/**
 * fork_c - forks execve to run cmd
 * @in: potential arguments
 */
void fork_c(info_t *in)
{
	pid_t kid;

	kid = fork();
	if (kid == -1)
	{
		perror("Error: Cannot fork pid_t kid\n");
		return;
	}
	if (kid == 0)
	{
		if (execve(in->path, in->argv, get_envir(in)) == -1)
		{
			info_free(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(in->status));
		if (WIFEXITED(in->status))
		{
			in->status = WEXITSTATUS(in->status);
			if (in->status == 126)
				print_err(in, "Permission denied\n");
		}
	}
}

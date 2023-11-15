#include "shell.h"

/**
 * fresh - frees pointer
 * @a: address of pointer
 *
 * Return: 1 or 0
 */

int fresh(void **a)

{
	if (a && *a)
	{
		free(*a);
		*a = NULL;
		return (1);
	}
	return (0);
}

/**
 * path_find - in PATH, finds cmd
 * @in: info
 * @p: PATH
 * @c: the command
 *
 * Return: p or NULL
 */

char *path_find(info_t *in, char *p, char *c)
{
	char *path;
	int a = 0, b = 0;

	if (!p)
		return (NULL);
	if ((_len(c) > 2) && starts_w(c, "./"))
	{
		printf("The path starts with dot slash\n");
		if (is_c(in, c))
		{
			printf("is_c(in, c) is true\n");
			return (c);
		}
	}
	while (1)
	{
		printf("While 1 is true..\n");
		if (!p[a] || p[a] == ':')
		{
			path = dupl(p, b, a);
			if (!*path)
				_cat(path, c);
			else
			{
				_cat(path, "/");
				_cat(path, c);
			}
			if (is_c(in, path))
				return (path);
			if (!p[a])
				break;
			b = a;
		}
		a++;
	}
	return (NULL);
}

/**
 * dupl - duplicates chars
 * @p: PATH
 * @st: beginning
 * @end: end
 *
 * Return: a buffer
 */

char *dupl(char *p, int st, int end)
{
	int b = 0, a = 0;
	static char buffer[1024];

	for (a = st, b = 0; a < end; ++a)
	{
		if (p[a] != ':')
			buffer[b++] = p[a];
	}
	buffer[b] = 0;
	return (buffer);
}

/**
 * is_c - checks if executable cmd
 * @in: info
 * @p: PATH
 *
 * Return: 1 or 0
 */

int is_c(info_t *in, char *p)
{
	struct stat st;

	(void)in;
	if (!p || stat(p, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * find_c - finds cmd in PATH
 * @in: info
 */

void find_c(info_t *in)
{
	int a, b;
	char *p = NULL;

	in->path = in->argv[0];
	if (in->flag_lc == 1)
	{
		in->lc++;
		in->flag_lc = 0;
	}
	for (a = 0, b = 0; in->arg[a]; a++)
	{
		if (!_delim(in->arg[a], " \t\n"))
			b++;
	}
	if (!b)
		return;

	p = path_find(in, get_env(in, "PATH="), in->argv[0]);
	printf("p is %s\n", p);
	if (p)
	{
		in->path = p;
		fork_c(in);
		printf("Forked cmd one..\n");
	}
	else
	{
		if ((inter(in) || get_env(in, "PATH=") || in->argv[0][0] == '/')
			&& is_c(in, in->argv[0]))
		{
			fork_c(in);
			printf("This is true, forked..\n");
		}
		else if (*(in->arg) != '\n')
		{
			in->status = 127;
			print_err(in, "Not Found\n");
		}
	}
}

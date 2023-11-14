#include "shell.h"

/**
 * info_free - frees info_t
 * @in: info struct
 * @a: all fields
 */

void info_free(info_t *in, int a)
{
	free_s(in->argv);
	in->argv = NULL;
	in->path = NULL;
	if (a)
	{
		if (!in->_buf)
			free(in->arg);
		if (in->history)
			list_free(&(in->history));
		if (in->env)
			list_free(&(in->env));
		if (in->alias)
			list_free(&(in->alias));
		free_s(in->environ);
			in->environ = NULL;
		fresh((void **)in->_buf);
		if (in->fd_rd > 2)
			close(in->fd_rd);
		_putchar(FLUSH_B);
	}
}

/**
 * b_read - reads buffer
 * @in: info struct
 * @b: buffer
 * @a: size of buffer
 *
 * Return: i
 */

ssize_t b_read(info_t *in, char *b, size_t *a)
{
	ssize_t c = 0;

	if (*a)
		return (0);
	c = read(in->fd_rd, b, READ_SIZE);
	if (c >= 0)
		*a = c;
	return (c);
}

/**
 * info_init - clears to initialize
 * @in: info struct
 */

void info_init(info_t *in)
{
	in->arg = NULL;
	in->argv = NULL;
	in->path = NULL;
	in->argc = 0;
}

/**
 * buf_in - chain cmd buffer
 * @in: info struct
 * @b: buffer
 * @a: length
 *
 * Return: b
 */

ssize_t buf_in(info_t *in, char **b, size_t *a)
{
	size_t c = 0;
	ssize_t d = 0;

	if (!*a)
	{
		/* fresh((void **)in->_buf); */
		free(*b);
		*b = NULL;
		signal(SIGINT, sig_int);
	#if GETLINE_USED
		 d = getline(b, &c, stdin);
	#else
		d = _getline(in, b, &c);
	#endif
		if (d > 0)
		{
			if ((*b)[d - 1] == '\n')
			{
				(*b)[d - 1] = '\0';
				d--;
			}
			in->flag_lc = 1;
			rm_coms(*b);
			append_list(in, *b, in->histcount++);
			/* if (_chr(*b, ';')) */
			{
				*a = d;
				in->_buf = b;
			}
		}
	}
	return (d);
}

/**
 * _getline - gets line from stdin
 * @in: info struct
 * @b: address of buffer
 * @a: size of buffer
 *
 * Return: line
 */

int _getline(info_t *in, char **b, size_t *a)
{
	char *c, *d = NULL, *e = NULL;
	static char buffer[READ_SIZE];
	size_t kk;
	static size_t si, sj;
	ssize_t f = 0, getting = 0;

	d = *b;
	if (d && a)
		getting = *a;
	if (si == sj)
		si = sj = 0;
	f = b_read(in, buffer, &sj);
	if (f == -1 || (f == 0 && sj == 0))
		return (-1);
	c = _chr(buffer + si, '\n');
	kk = c ? 1 + (unsigned int)(c - buffer) : sj;
	e = _realloc(d, getting, getting ? getting + kk : kk + 1);
	if (!e)
		return (d ? free(d), -1 : -1);
	if (getting)
		_ncat(e, buffer + si, kk - si);
	else
		_ncpy(e, buffer + si, kk - si + 1);
	getting += kk - si;
	si = kk;
	d = e;
	if (a)
		*a = getting;
	*b = d;

	return (getting);
}

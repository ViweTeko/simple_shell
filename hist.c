#include "shell.h"

/**
 * hist_rd - reads history file
 * @in: potential arguments
 *
 * Return: result or 0
 */

int hist_rd(info_t *in)
{
	char *buffer = NULL, *a = hist_file(in);
	int b, c = 0, d = 0;
	ssize_t e, f, g = 0;
	struct stat st;

	if (!a)
		return (0);
	e = open(a, O_RDONLY);
	free(a);
	if (e == -1)
		return (0);
	if (!fstat(e, &st))
		g = st.st_size;
	if (g < 2)
		return (0);
	buffer = malloc(sizeof(char) * (g + 1));
	if (!buffer)
		return (0);
	f = read(e, buffer, g);
	buffer[g] = 0;
	if (f <= 0)
		return (free(buffer), 0);
	close(e);

	for (b = 0; b < g; b++)
		if (buffer[b] == '\n')
		{
			buffer[b] = 0;
			append_list(in, buffer + c, d++);
			c = b + 1;
		}
	if (c != b)
		append_list(in, buffer + c, d++);
	free(buffer);
	in->histcount = d;
	while (in->histcount-- >= HIST_MAX)
		delete_node(&(in->history), 0);
	renum_hist(in);

	return (in->histcount);
}

/**
 * hist_wr - writes to file
 * @in: potential arguments
 *
 * Return: 1 or -1
 */

int hist_wr(info_t *in)
{
	char *a = hist_file(in);
	ssize_t b;
	list_t *c = NULL;

	if (!a)
		return (-1);
	b = open(a, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(a);
	if (b == -1)
		return (-1);
	for (c = in->history; c; c = c->next)
	{
		_putsfd(c->s, b);
		_putfd('\n', b);
	}
	_putfd(FLUSH_B, b);
	close(b);

	return (1);
}

/**
 * renum_hist - renumbers history
 * @in: potential arguments
 *
 * Return: hiscount
 */

int renum_hist(info_t *in)
{
	int a = 0;
	list_t *b = in->history;

	while (b)
	{
		b->num = a++;
		b = b->next;
	}
	return (in->histcount = a);
}

/**
 * hist_file - gets history file
 * @in: potential arguments
 *
 * Return: file
 */

char *hist_file(info_t *in)
{
	char *a, *buffer;

	a = get_env(in, "HOME=");
	if (!a)
		return (NULL);
	buffer = malloc(sizeof(char) * (_len(a) + _len(FILE_H) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_cpy(buffer, a);
	_cat(buffer, "/");
	_cat(buffer, FILE_H);

	return (buffer);
}

/**
 * append_list - appends history list
 * @in: potential arguments
 * @b: buffer
 * @a: linecount
 *
 * Return: 0
 */

int append_list(info_t *in, char *b, int a)
{
	list_t *c = NULL;

	if (in->history)
		c = in->history;
	node_end(&c, b, a);
	if (!in->history)
		in->history = c;

	return (0);
}


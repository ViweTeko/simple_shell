#include "shell.h"

/**
 * main - main function of simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	int fd = 2;
	info_t in[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Cannot open ");
				_eputs(argv[1]);
				_puterr('\n');
				_puterr(FLUSH_B);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		in->fd_rd = fd;
	}
	pop_list(in);
	hist_rd(in);
	hsh(in, argv);
	return (EXIT_SUCCESS);
}

/**
 * hsh - shell loop
 * @in: info struct
 * @argv: argument vector
 *
 * Return: 0 or 1
 */

int hsh(info_t *in, char *argv[])
{
	int b = 0;
	ssize_t a = 0;

	while (b != -2 && a != -1)
	{
		info_init(in);
		if (inter(in))
			_puts("$ ");
		_puterr(FLUSH_B);
		a = get_in(in);
		if (a != -1)
		{
			setter(in, argv);
			b = find_built(in);
			if (b == -1)
				find_c(in);
		}
		else if (inter(in))
			_putchar('\n');
		info_free(in, 0);
	}
	hist_wr(in);
	info_free(in, 1);
	if (b == -2)
	{
		if (in->err_num == -1)
			exit(in->status);
		exit(in->err_num);
	}
	if (!inter(in) && in->status)
		exit(in->status);

	return (b);
}

/**
 * stow - splits string into tokens
 * @s: string
 * @de: delimiter
 *
 * Return: s or NULL
 */

char **stow(char *s, char *de)
{
	char **r;
	int a, b, c, d, e = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!de)
		de = " ";
	for (a = 0; s[a] != '\0'; a++)
		if (!_delim(s[a], de) && (_delim(s[a + 1], de) || !s[a + 1]))
			e++;
	if (e == 0)
		return (NULL);
	r = malloc((1 + e) * sizeof(char *));
	if (!r)
		return (NULL);

	for (a = 0, b = 0; b < e; b++)
	{
		while (_delim(s[a], de))
			a++;
		c = 0;
		while (_delim(s[a + c], de) && s[a + c])
			c++;
		r[b] = malloc((c + 1) * sizeof(char));
		if (!r[b])
		{
			for (c = 0; c < b; c++)
				free(r[c]);
			free(r);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			r[b][d] = s[a++];
		r[b][d] = 0;
	}
	r[b] = NULL;
	return (r);
}

/**
 * stow2 - splits string into token
 * @s: string
 * @de: delimiter
 *
 * Return: strings or NULL
 */

char **stow2(char *s, char de)
{
	char **r;
	int a, b, c, d, e = 0;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (a = 0; s[a] != '\0'; a++)
		if ((s[a] != de && s[a + 1] == de)
				|| (s[a] != de && !s[a + 1])
				|| s[a + 1] == de)
			e++;
	if (e == 0)
		return (NULL);
	r = malloc((1 + e) * sizeof(char *));
	if (!r)
		return (NULL);
	for (a = 0, b = 0; b < e; b++)
	{
		while (s[a] == de && s[a] != de)
			a++;
		c = 0;
		while (s[a + c] != de && s[a + c] && s[a + c] != de)
			c++;
		r[b] = malloc((c + 1) * sizeof(char));
		if (!r[b])
		{
			for (c = 0; c < b; c++)
				free(r[c]);
			free(r);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			r[b][d] = s[a++];
		r[b][d] = 0;
	}
	r[b] = NULL;
	return (r);
}

/**
 * free_s - frees string of strings
 * @z: string of strings
 */

void free_s(char **z)
{
	char **a = z;

	if (!z)
		return;
	while (*z)
		free(*z++);
	free(a);
}


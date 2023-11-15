#include "shell.h"

/**
 * e_xit - exits the shell
 * @in: potential arguments
 *
 * Return: exits with given exit status
 */
int e_xit(info_t *in)
{
	int echeck;

	if (in->argv[1])
	{
		echeck = _erratoi(in->argv[1]);
		if (echeck == -1)
		{
			in->status = 2;
			print_err(in, "Illegal number: ");
			_eputs(in->argv[1]);
			_puterr('\n');
			return (1);
		}
		in->err_num = _erratoi(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * _realloc - reallocates block of memory
 * @m: prev block
 * @n: new block
 * @o: old block
 *
 * Return: n
 */

void *_realloc(void *m, unsigned int o, unsigned int n)
{
	char *p;

	if (!m)
		return (malloc(n));
	if (!n)
		return (free(m), NULL);
	if (n == o)
		return (m);

	p = malloc(n);
	if (!p)
		return (NULL);
	o = o < n ? o : n;
	while (o--)
		p[o] = ((char *)m)[o];
	free(m);
	return (p);
}

/**
 * sig_int - disables Ctrl + C
 * @z: signal number
 */

void sig_int(__attribute__((unused))int z)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_B);
}

/**
 * _cd - changes the current directory
 * @in: potential arguments
 *
 * Return: 0
 */
int _cd(info_t *in)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("error: cannot getcwd\n");
	if (!in->argv[1])
	{
		dir = get_env(in, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = get_env(in, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_cmp(in->argv[1], "-") == 0)
	{
		if (!get_env(in, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(in, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = get_env(in, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(in->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(in, "cannot cd into ");
		_eputs(in->argv[1]), _puterr('\n');
	}
	else
	{
		set_env(in, "OLDPWD", get_env(in, "PWD="));
		set_env(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes current directory of process
 * @in: potential arguments
 *
 * Return: 0
 */
int _help(info_t *in)
{
	char **a_a;

	a_a = in->argv;
	_puts("Help call works. But function not yet implemented \n");
	if (0)
		_puts(*a_a);
	return (0);
}

#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_SIZE 1024
#define WRITE_SIZE 1024
#define FLUSH_B -1
#define NORM_C		0
#define OR_C		1
#define AND_C		2
#define CHAIN_		3

#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2

#define GETLINE_USED 0
#define USE_STRTOK 0

#define FILE_H		".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number
 * @s: a string
 * @next: points to next node
 */
typedef struct liststr
{
	int num;
	char *s;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pseudo-arguments to pass into a function
 * @arg: string from getline containing arguments
 * @argv:an array of strings
 * @path: string path for the current command
 * @argc: argument count
 * @lc: the error count
 * @err_num: the error code for exiting
 * @flag_lc: line count flag
 * @fname: program filename
 * @env: linked list local copy of environ
 * @environ: copy of environ
 * @history: history node
 * @alias: alias node
 * @changed_env: if environ changed
 * @status: return status of last x command
 * @_buf: address of pointer to cmd_buf
 * @c_type: command type
 * @fd_rd: the fd to read line input
 * @histcount: history line count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lc;
	int err_num;
	int flag_lc;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int changed_env;
	int status;
	char **_buf;
	int c_type;
	int fd_rd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - builtin string and related function
 * @type: builtin command flag
 * @func: related function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} table_b;

int hsh(info_t *, char **);
int find_built(info_t *);
void find_c(info_t *);
void fork_c(info_t *);

int is_c(info_t *, char *);
char *dupl(char *, int, int);
char *path_find(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);

int _puterr(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _len(char *);
int _cmp(char *, char *);
char *starts_w(const char *, const char *);

char *_cat(char *, char *);
char *_cpy(char *, char *);
char *_dup(const char *);
void _puts(char *);
int _putchar(char);
char *_ncpy(char *, char *, int);

char *_ncat(char *, char *, int);
char *_chr(char *, char);
char **stow(char *, char *);
char **stow2(char *, char);
char *_memset(char *, char, unsigned int);
int fresh(void **);

void *_realloc(void *, unsigned int, unsigned int);
void free_s(char **);
int inter(info_t *);
int _delim(char, char *);

int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_err(info_t *, char *);
int _deci(int, int);

char *conv_num(long int, int, int);
void rm_coms(char *);
int e_xit(info_t *);
int _cd(info_t *);
int _help(info_t *);

int my_hist(info_t *);
int _alias(info_t *);
ssize_t buf_in(info_t *, char **, size_t *);
int _getline(info_t *, char **, size_t *);
ssize_t get_in(info_t *);

void sig_int(int);
void info_init(info_t *);
void setter(info_t *, char **);
void info_free(info_t *, int);
char *get_env(info_t *, const char *);

int my_env(info_t *);
int my_setenv(info_t *);
int my_unsetenv(info_t *);
int pop_list(info_t *);

char **get_envir(info_t *);
int un_setenv(info_t *, char *);
int set_env(info_t *, char *, char *);
char *hist_file(info_t *in);
int hist_wr(info_t *in);
int hist_rd(info_t *in);

int append_list(info_t *in, char *b, int lc);
int renum_hist(info_t *in);
list_t *node_add(list_t **, const char *, int);
list_t *node_end(list_t **, const char *, int);
size_t print_s_list(const list_t *);

int delete_node(list_t **, unsigned int);
void list_free(list_t **);
size_t list_len(const list_t *);
char **strings_list(list_t *);
size_t print_list(const list_t *);

list_t *pre_node(list_t *, char *, char);
ssize_t get_index(list_t *, list_t *);
int _chain(info_t *, char *, size_t *);
void check_ch(info_t *, char *, size_t *, size_t, size_t);

int rep_ali(info_t *);
int re_e(info_t *);
int rep_s(char **, char *);
int set_ali(info_t *, char *);
int unset_ali(info_t *, char *);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:26:23 by lprieto-          #+#    #+#             */
/*   Updated: 2024/11/12 12:41:22 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

/******************************** Structs Simplification ******************/
typedef struct s_environment	t_env;
typedef struct s_minishell		t_msh;
typedef struct s_tokenizer		t_tok;
typedef struct s_executor		t_exe;

/******************************** Structs *********************************/

struct	s_environment
{
	char	**names;
	char	**values;
	char	*pwd;
	char	*old_pwd;
	char	*home;
	char	*path;
	int		env_count;
	int		exit_status;
};

typedef enum {
	T_WORD,
	T_OPERATOR,
	T_WHITESPACE,
	T_QUOTE
}	token_type_t;

struct	s_tokenizer
{
	char	*cmd;
	char	**args;
	int		token_count;
	int		len;
	int		is_heredoc;
	char	*heredoc_delim;
	token_type_t	type;
	struct s_tokenizer *prev;
	struct s_tokenizer *next;
};

struct s_executor
{
	int		fd_1[2];
	int		status_1;
	int		status_2;
	int		fd_in;
	int		fd_out;
};

typedef struct s_command
{
	char	**args;
	int		arg_count;
}	t_cmd;

struct	s_minishell
{
	t_tok	*tkns;
	t_env	*env;
	t_exe	*mpip;
	t_cmd	*cmds;
	int			cmd_count;
	int		end_sig;
	int		last_exit_code;
	char	**envs;
	int		env_var_count;
	int		shlvl;
};

/******************************* minishell.c ******************************/
void	shell_loop(t_msh *msh);

/******************************** cd_utils ********************************/
char	*built_abspath(char *relative_path, char *pwd);
char	*make_relative(char *arg, t_msh *msh);

/***************************** cd_builting ********************************/
void	handle_cd_path(t_msh *msh);
void	ft_cd(t_msh *msh, int num_cmd);

/****************************** ms_varenv *********************************/
char	*search_env(char *var, t_msh *msh);
int		varenv_man(t_msh *msh, char *builting, char *var_name);

/******************************* ms_b_echo ********************************/
void	ft_echo(t_msh *msh, int num_cmd);

/******************************* ms_b_env *********************************/

int		update_env_var(t_msh *msh, char *name, char *value);
int		ft_env(t_msh *msh);
char	*update_env(t_msh *msh, char *name, char *value);
// void	debug_env(t_msh *msh); borrar?

/******************************* ms_b_exit ********************************/

// static int	is_numeric_arg(char *str);
// static void	handle_numeric_arg(t_msh *msh, char *arg);
// static void	handle_exit_error(t_msh *msh, char *arg);
void	ft_exit(t_msh *msh);

/******************************* ms_b_export ******************************/

// static int	is_valid_identifier(char *str);
// static void	print_export_vars(t_msh *msh);
int		add_env_var(t_msh *msh, char *name, char *value);
// static void	handle_export_arg(t_msh *msh, char *arg);
int		ft_export(t_msh *msh, char **new_var);

/******************************* ms_b_export_utils ************************/

char	*get_var_name(char *var);
char	*get_var_value(char *var);
int		update_env_variable(t_msh *msh, char *name, char *value);

/******************************* ms_b_pwd *********************************/

int		ft_pwd(t_msh *msh);

/******************************** ms_b_unset ******************************/

// static int	is_valid_identifier(char *str);
// static void	remove_var_from_env(t_msh *msh, int pos);
// static int	find_var_in_env(t_msh *msh, char *var_name);
int		ft_unset(t_msh *msh, char **new_var);

/******************************* ms_builtins ******************************/

void	cmd_not_found(t_msh *msh);
void	check_tokens(char *input, t_msh *msh);
void	cleanup_commands(t_msh *msh);
void	exc_cmd(t_msh *msh, int count_tok);
int		is_builtin(t_msh *msh);

/******************************* ms_env ***********************************/

int		env_var_count(t_msh *msh);
int		find_env_var(t_msh *msh, char *var_name);
int		check_envs(void);
void	update_shlvl(t_msh *msh);
int		env_init_values(t_env *env, t_msh *msh);

/******************************* ms_executor ******************************/

// static int	is_command_executable(char *fullpath)
// static void	child_process(t_msh *msh, char *fullpath)
// static void	parent_process(pid_t pid, char *fullpath)
int		execute_command(t_msh *msh, char *fullpath);
int		find_cmd(char *tkn, t_msh *msh);
// static char	**get_path_dirs(char **envs);
// static char	*check_absolute_path(char *cmd);
// static char	*try_path(char *dir, char *cmd);
char	*make_path(char *tkn, t_msh *msh);

/******************************* ms_free **********************************/

void	ft_free_array(char **array);
void	free_tok(t_tok *tok);
void	free_env(t_env *env);
void	free_structs(t_env *env, t_tok *tok, t_exe *mpip);

/******************************* ms_init **********************************/

int		env_alloc_struct(t_env **env, t_msh *msh);
int		tok_alloc_struct(t_tok **tok);
int		mpip_alloc_struct(t_exe **mpip);
int		init_structs(t_env **env, t_msh *msh, t_exe **mpip, t_tok **tok);

/******************************* ms_lexer *********************************/

int		quote_lexer(t_msh *msh);
int		lexer(char **tokens, t_msh *msh);
int		parse_and_validate_commands(t_tok *tok, t_cmd **commands);

/******************************* ms_parser ********************************/

char	*parse_path(char **env);
char	*parse_pwd(char **env);
// static char	**extract_args(t_tok *tokens);
int		parse_input(char *input, t_msh *mshll);

/******************************* ms_rline *********************************/

char	*cmd_gen(const char *text, int state);
char	**cmd_comp(const char *text, int start, int end);
char	*cmd_match(const char *text, int state);

/******************************* ms_signals ********************************/
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	init_signals(void);

/******************************* ms_tokenizer *****************************/
int		size_token(char *input, t_tok *tok);
char	*create_token(char *input, int len, t_tok *tok);
void	ft_token(char *input, t_tok *tok);

/***************************** token_tools.c *******************************/
int	is_quote(char c);
int	is_whitespace(char c);
int	is_operator(char c);
token_type_t	type_token_def(t_tok *tok, char c);

/******************************* ms_tools *********************************/

/******************************* ms_err_handle ****************************/
void	handle_cd_error(char *path, int error_type);
int	ft_err(t_msh *msh, int err_code);

/******************************* Error macros *****************************/

# define E_ARG			"Invalid number of parameters\n"
# define E_MALLOC		"Malloc failure\n"
# define E_ENV			"Error: No environment\n"
# define E_PATH			"No such path\n"
# define E_CMD			"Error: Command not found\n"
# define E_OPEN			"Can't open file\n"
# define E_WR			"W Permission denied\n"
# define E_RD			"R Permission denied\n"
# define E_X			"X Permission denied\n"
# define E_NOFILE		"No such file or directory\n"
# define E_DIRECTORY	"Is a directory\n"
# define E_EXECARG		"Error: minishell doesn't accept arguments\n"
# define E_MEMASF		"Error: memory assignment failed\n"
# define E_ENVGET		"Error: env var retrieval failed\n"
# define E_TOKMEM		"Error: tok mem asignation failed\n"
# define E_PIPMEM		"Error: mpip mem asignation failed\n"
# define E_CDARG		"cd: $ARG: No such file or directory\n"

/******************************** Exec macros ****************************/

# define E_PIPE			"Pipe error"
# define E_FORK			"Fork error"
# define E_DUP			"Dup2 error"
# define E_EXECVE		"Execve error"
# define E_NOCMD		"Command not found"
# define E_NOEXEC		"Permission denied"
# define PIPE_READ		0
# define PIPE_WRITE		1
# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define EXIT_MISUSE	2
# define EXIT_NOEXEC	126
# define EXIT_NOFOUND	127
# define EXIT_SIGBASE	128

/******************************** General macros **************************/

# define TRUE			0
# define FALSE			1

/******************************** Other macros ***************************/

# define PATH_MAX		4096
# define MAX_ARGS		4096
# define MAX_ENV_VARS	4096

/******************************** Color macros ***************************/

# define RD		"\033[1;31m"
# define GR		"\033[1;32m"
# define YL		"\033[1;33m"
# define BL		"\033[1;34m"
# define PK		"\033[0;35m"
# define PP		"\033[1;35m"
# define CY		"\033[1;36m"
# define F		"\033[0m"

#endif

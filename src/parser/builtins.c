/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:12:48 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/19 02:23:24 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_msh *msh)
{
	ft_fd_printf(2, "Error: %s : command not found\n", msh->tkns->cmd);
}

static t_redir	is_there_redir(t_msh *msh, int *pos)
{
	int		i;
	char	*arg;

	i = 0;
	while (msh->tkns->args[i])
	{
		arg = msh->tkns->args[i];
		if (arg[0] == '|')
		{
			*pos = i;
			return (PIPE);
		}
		if (arg[0] == '<' && arg[1] == '<')
		{
			*pos = i;
			return (REDIR_HERE);
		}
		if (arg[0] == '>' && arg[1] == '>')
		{
			*pos = i;
			return (REDIR_APPEND);
		}
		if (arg[0] == '<')
		{
			*pos = i;
			return (REDIR_IN);
		}
		if (arg[0] == '>')
		{
			*pos = i;
			return (REDIR_OUT);
		}
		i++;
	}
	*pos = i;
	return (NO_REDIR);
}

static void	print_redir_info(t_redir redir_type, int redir_pos)
{
	printf("Tipo de redirección: ");
	if (redir_type == NO_REDIR)
		printf("No hay redirección\n");
	else if (redir_type == REDIR_IN)
		printf("de entrada (<)\n");
	else if (redir_type == REDIR_OUT)
		printf("de salida (>)\n");
	else if (redir_type == REDIR_APPEND)
		printf("de salida con append (>>)\n");
	else if (redir_type == REDIR_HERE)
		printf("Heredoc (<<)\n");
	else if (redir_type == PIPE)
		printf("Pipe (|)\n");
	printf("Posición del token: %d\n", redir_pos);
}

void	check_tokens(char *input, t_msh *msh)
{
	int	count_tok;
	int		redir_pos;
	t_redir	redir_type;

	if (!input || !*input)
		return ;
	ft_token(input, msh->tkns);
	if (!msh->tkns->args || !msh->tkns->args[0])
		return ;
	count_tok = 0;
	while (msh->tkns->args[count_tok])
		count_tok++;
	msh->tkns->token_count = count_tok;
	msh->tkns->cmd = ft_strdup(msh->tkns->args[0]);
	redir_type = is_there_redir(msh, &redir_pos);
	print_redir_info(redir_type, redir_pos);
	if (is_builtin(msh->tkns->cmd))
		exc_cmd(msh, count_tok);
	else if (find_cmd(msh->tkns->cmd, msh) == -1)
		cmd_not_found(msh);
	restore_signals();
	free(msh->tkns->cmd);
	msh->tkns->cmd = NULL;
}

// void	cleanup_commands(t_msh *msh)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < msh->cmd_count)
// 	{
// 		j = 0;
// 		while (msh->cmds[i].args[j])
// 		{
// 			free(msh->cmds[i].args[j]);
// 			j++;
// 		}
// 		free(msh->cmds[i].args);
// 		i++;
// 	}
// 	free(msh->cmds);
// 	msh->cmds = NULL;
// 	msh->cmd_count = 0;
// }

int	is_builtin(char	*token)
{
	static char	*builtins[10];
	int			i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "exit";
	builtins[5] = "export";
	builtins[6] = "unset";
	builtins[7] = "test";
	builtins[8] = "test2";
	builtins[9] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(token, builtins[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	exc_cmd(t_msh *msh, int count_tok)
{
	if (ft_strcmp(msh->tkns->cmd, "echo") == 0)
		ft_echo(msh, count_tok);
	else if (ft_strcmp(msh->tkns->cmd, "cd") == 0)
		ft_cd(msh, count_tok);
	else if (ft_strcmp(msh->tkns->cmd, "pwd") == 0)
		ft_pwd(msh);
	else if (ft_strcmp(msh->tkns->cmd, "env") == 0)
		ft_env(msh);
	else if (ft_strcmp(msh->tkns->cmd, "exit") == 0)
		ft_exit(msh);
	else if (ft_strcmp(msh->tkns->cmd, "export") == 0)
		ft_export(msh, count_tok);
	else if (ft_strcmp(msh->tkns->cmd, "unset") == 0)
		ft_unset(msh, count_tok);
	else if (ft_strcmp(msh->tkns->cmd, "test") == 0)
		ft_fd_printf(1, "Envarcount: %d\n", msh->env_var_count);
	else if (ft_strcmp(msh->tkns->cmd, "test2") == 0)
		env_var_exist(msh);
}
// printf("test ejecuta: \n");
// ft_fd_printf(1, "sig_out: %d\n", msh->last_exit_code);


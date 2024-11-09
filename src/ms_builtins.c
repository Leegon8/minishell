/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:12:48 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/09 20:40:14 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_msh *msh)
{
	ft_fd_printf(2, "Error: ");
	ft_fd_printf(2, "%s", msh->tkns->cmd);
	ft_fd_printf(2, ": command not found\n");
}

void	check_tokens(char *input, t_msh *msh)
{
	int		i;

	i = 0;
	if (!input || !*input)
		return ;
	ft_token(input, msh->tkns);
	if (!msh->tkns->args || !msh->tkns->args[0])
		return ;
	msh->cmd_count = parse_and_validate_commands(msh->tkns, &msh->cmds);
	if (msh->cmd_count > 0)
	{
		while (msh->cmds[i].args && i < msh->cmd_count)
		{
			msh->tkns->cmd = msh->cmds[i].args[0];
			msh->tkns->args = msh->cmds[i].args;
			if (is_builtin(msh) == 0)
				exc_cmd(msh, msh->cmds[i].arg_count);
			else if (find_cmd(msh->tkns->cmd, msh) == -1)
				cmd_not_found(msh);
			i++;
		}
		cleanup_commands(msh);
	}
}

void	cleanup_commands(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (i < msh->cmd_count)
	{
		j = 0;
		while (msh->cmds[i].args[j])
		{
			free(msh->cmds[i].args[j]);
			j++;
		}
		free(msh->cmds[i].args);
		i++;
	}
	free(msh->cmds);
	msh->cmds = NULL;
	msh->cmd_count = 0;
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
	{
		char *test_args[] = {"export", "TEST=123", NULL};
		ft_export(msh, test_args);
	}
	else if (ft_strcmp(msh->tkns->cmd, "unset") == 0)
	{	
		char *value[] = {"unset", "SHLVL", NULL};
		ft_unset(msh, value);
	}
	else if (ft_strcmp(msh->tkns->cmd, "test") == 0)
		ft_fd_printf(1, "Envarcount: %d\n", msh->env_var_count);
	else if (ft_strcmp(msh->tkns->cmd, "test2") == 0)
		ft_fd_printf(1, "sig_out: %d\n", msh->last_exit_code);	
}

int	is_builtin(t_msh *msh)
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
		if (ft_strcmp(msh->tkns->cmd, builtins[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

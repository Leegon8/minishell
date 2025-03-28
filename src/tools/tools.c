/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:28:01 by lprieto-          #+#    #+#             */
/*   Updated: 2025/03/28 10:58:04 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe_in_args(char **args)
{
	int	i = 0;

	while (args && args[i])
	{
		if (check_syntax_redir(args, i) == PIPE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	child_process(t_msh *msh, int i, int prev_fd, int pipe_fd[2])
{
	char	*path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < msh->cmd_count - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (is_builtin(msh->cmds[i].args[0]))
	{
		msh->tkns->cmd = ft_strdup(msh->cmds[i].args[0]);
		msh->tkns->args = msh->cmds[i].args;
		exc_cmd(msh, i);
		exit(EXIT_SUCCESS);
	}
	path = make_path(msh->cmds[i].args[0], msh);
	if (!path)
		cmd_not_found(msh);
	else
	{
		execve(path, msh->cmds[i].args, msh->envs);
		free(path);
		ft_fd_printf(2, E_EXECVE);
	}
	exit(EXIT_FAILURE);
}

int	execute_pipeline(t_msh *msh)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (i < msh->cmd_count)
	{
		if (i < msh->cmd_count - 1 && pipe(pipe_fd) == -1)
			return (ft_fd_printf(2, E_PIPE), -1);
		pid = fork();
		if (pid == -1)
			return (ft_fd_printf(2, E_FORK), -1);
		else if (pid == 0)
			child_process(msh, i, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (i < msh->cmd_count - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}

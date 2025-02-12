/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:13:10 by lprieto-          #+#    #+#             */
/*   Updated: 2024/11/13 17:46:16 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_executable(char *fullpath)
{
	if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
		return (TRUE);
	return (FALSE);
}

static void	child_process(t_msh *msh, char *fullpath)
{
	if (execve(fullpath, msh->tkns->args, msh->envs) == -1)
	{
		cmd_not_found(msh);
		free(fullpath);
		exit(EXIT_FAILURE);
	}
}

static void	parent_process(pid_t pid, char *fullpath)
{
	int	status;

	waitpid(pid, &status, 0);
	free(fullpath);
}

int	execute_command(t_msh *msh, char *fullpath)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Error fork\n");
		free(fullpath);
		return (-1);
	}
	else if (pid == 0)
		child_process(msh, fullpath);
	else
		parent_process(pid, fullpath);
	return (TRUE);
}

int	find_cmd(char *tkn, t_msh *msh)
{
	char	*fullpath;

	fullpath = make_path(tkn, msh);
	if (is_command_executable(fullpath))
	{
		if (!execute_command(msh, fullpath))
			return (-1);
	}
	else
	{
		free(fullpath);
		return (-1);
	}
	return (TRUE);
}

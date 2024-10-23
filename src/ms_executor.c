/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:13:10 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/07 13:49:37 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_command_executable(char *fullpath)
{
	if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
		return (1);
	return (0);
}

static void	child_process(t_msh *msh, char *fullpath)
{
	if (execve(fullpath, &msh->tkns->cmd, msh->envs) == -1)
	{
		printf("Error execve\n");
		cmd_not_found(msh);
		free(fullpath);
		exit(EXIT_FAILURE);  // El hijo termina aquí
	}
}

static void	parent_process(pid_t pid, char *fullpath)
{
	int	status;

	waitpid(pid, &status, 0);
	free(fullpath);
}

char	*make_path(t_msh *msh)
{
	char	*fullpath;

	fullpath = malloc(sizeof(char) * 1024);
	ft_strcpy(fullpath, "/bin");
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, msh->tkns->cmd);
	return (fullpath);
}

int	execute_command(t_msh *msh, char *fullpath)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)  // Error al crear el proceso hijo
	{
		printf("Error fork\n");
		free(fullpath);
		return (-1);
	}
	else if (pid == 0)
		child_process(msh, fullpath);
	else  // Proceso padre
		parent_process(pid, fullpath);
	return (0);
}

int	find_cmd(t_msh *msh)
{
	char	*fullpath;

	fullpath = make_path(msh);
	printf("fullpath = %s\n", fullpath);
	if (is_command_executable(fullpath))
	{
		if (execute_command(msh, fullpath) == -1)
		{
			cmd_not_found(msh);
			return (-1);
		}
	}
	else
	{
		cmd_not_found(msh);
		free(fullpath);
		return (-1);
	}
	return (0);
}
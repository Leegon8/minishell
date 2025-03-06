/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:13:10 by lprieto-          #+#    #+#             */
/*   Updated: 2025/02/17 15:54:49 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int setup_redirections(t_msh *msh)
{
    if (msh->mpip->outfile && !handle_output_file(msh, msh->mpip->outfile))
        return (FALSE);
    if (msh->mpip->infile && !handle_input_file(msh, msh->mpip->infile))
        return (FALSE);
    return (TRUE);
}

int	is_command_executable(char *fullpath)
{
	if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
		return (TRUE);
	else
		printf("ERROOOOOOOOR\n");
	return (FALSE);
}

static void	child_process(t_msh *msh, char *fullpath)
{
	if (!setup_redirections(msh))  // Añadir esta línea
	{
		free(fullpath);
		exit(EXIT_FAILURE);
	}
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
		ft_fd_printf(2, "bash: fork: Cannot allocate memory\n");
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

	//printf("fullpath = %s\ntkn = %s\n", fullpath, tkn);
	if (msh->tkns->redir_pos >= 0)
		fullpath = ft_strdup(tkn);
	else
		fullpath = make_path(tkn, msh);
	if (is_command_executable(fullpath))
	{
		printf("IAODJFPIJFSPJFSPIJFJSIPFPIIIIIIIIIII\n");
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

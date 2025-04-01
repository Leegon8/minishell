/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:31:02 by lauriago          #+#    #+#             */
/*   Updated: 2025/03/27 10:39:33 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "status.h"

//This function copy all the args without the redirection token 
static char	**redir_args(char **args, int redir_pos)
{
	char	**result;
	int		i;

	if (!args || redir_pos <= 0)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (redir_pos + 1));
	if (!result)
	{
		ft_fd_printf(2, "malloc failed");
		return (NULL);
	}
	i = 0;
	while (i < redir_pos && args[i])
	{
		result[i] = ft_strdup(args[i]);
		if (!result[i])
		{
			ft_free_array(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

static void	child_process_redir(t_msh *msh, char *fullpath, t_redir type)
{
	char	**new_args;

	new_args = redir_args(msh->tkns->args, msh->tkns->redir_pos);
	if (type == REDIR_OUT || type == REDIR_APPEND)
		handle_output_file(msh, msh->mpip->outfile, type);
	else if (type == REDIR_IN || type == REDIR_HERE)
		handle_input_file(msh, msh->mpip->infile, type);
	if (execve(fullpath, new_args, msh->envs) == -1)
	{
		cmd_not_found(msh);
		free(fullpath);
		exit(EXIT_FAILURE);
	}
	ft_free_array(new_args);
}

static void	parent_process_redir(t_msh *msh, pid_t pid, char *fullpath)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		set_exit_status(128 + WTERMSIG(status));
	cleanup_heredoc(msh);
	free (fullpath);
}

void	exec_redir(t_msh *msh, char *tkn, t_redir type)
{
	pid_t	pid;
	char	*fullpath;

	msh->mpip->backup_out = dup(STDOUT_FILENO);
	msh->mpip->backup_in = dup(STDIN_FILENO);
	fullpath = make_path(tkn, msh);
	pid = fork();
	if (pid == -1)
	{
		ft_fd_printf(2, "bash: fork: Cannot allocate memory\n");
		set_exit_status(1);
		return ;
	}
	else if (pid == 0)
		child_process_redir(msh, fullpath, type);
	else
		parent_process_redir(msh, pid, fullpath);
}

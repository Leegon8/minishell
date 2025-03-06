/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:31:02 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/26 16:31:16 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**extract_command(char**args, int redir_pos)
{
	char	**cmd_args;
	int		i;

	cmd_args = malloc(sizeof(char *) * (redir_pos + 1));
	i = 0;
	while (i < redir_pos)
	{
		cmd_args[i] = ft_strdup(args[i]);
		if (cmd_args[i] == NULL)
		{
			while (i >= 0)
			{
				free(cmd_args[i]);
				i--;
				return (NULL);
			}
		}
		i++;
	}
	cmd_args[redir_pos] = NULL;
	return (cmd_args);
}

int	exec_redir(t_msh *msh)
{
	char	**cmd;
	int		file_pos;
	pid_t	pid;
	int		status;
	char	*fullpath;

	file_pos = msh->tkns->redir_pos + 1;
	cmd = extract_command(msh->tkns->args, msh->tkns->redir_pos);
	printf("filename = %s\n",msh->tkns->args[file_pos]);
	fullpath = make_path(msh->tkns->cmd, msh);
	pid = fork();
	if (pid == -1)
	{
		ft_fd_printf(2, "bash: fork: Cannot allocate memory\n");
		ft_free_array(cmd);
		return (FALSE);
	}
	else if (pid == 0)
	{
		if (cmd == NULL)
		{
			ft_fd_printf(2, "Error al extraer el comando\n");
			exit(EXIT_FAILURE);

		}
		if (!execve(fullpath, cmd, msh->envs))
		{
			cmd_not_found(msh);
			free(fullpath);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (TRUE);
}

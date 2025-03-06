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

int	exec_redir(t_msh *msh)
{
	//int		file_pos;
	pid_t	pid;
	int		status;
	char	*fullpath;

	//file_pos = msh->tkns->redir_pos + 1;
	fullpath = extract_command(msh->tkns->args, msh->tkns->redir_pos);
	//printf("filename = %s\n",msh->tkns->args[file_pos]);
	//printf("fullpath = %s\n", fullpath);
	pid = fork();
 	if (pid == -1)
	{
		ft_fd_printf(2, "bash: fork: Cannot allocate memory\n");
		free(fullpath);
		return (FALSE);
	}
	else if (pid == 0)
	{
		if (fullpath == NULL)
		{
			ft_fd_printf(2, "Error al extraer el comando\n");
			exit(EXIT_FAILURE);
		}
		if (!execve(fullpath, msh->tkns->args, msh->envs))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:57:05 by lauriago          #+#    #+#             */
/*   Updated: 2025/03/07 00:17:00 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_file(t_msh *msh, char *filename, t_redir type)
{
	int	fd;

	msh->mpip->backup_in = dup(STDIN_FILENO);
	if (msh->mpip->backup_in == -1)
		return (FALSE);
	if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (access(filename, F_OK) == 0)
			ft_fd_printf(2, "minishell: %s: Permission denied\n", filename);
		else
			ft_fd_printf(2, "minishell: %s: No such file or directory\n",
				filename);
		return (FALSE);
	}
	msh->mpip->backup_in = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
}

void	handle_redir_in(t_msh *msh, t_redir type)
{
	int	file_pos;

	file_pos = msh->tkns->redir_pos + 1;
	msh->mpip->infile = msh->tkns->args[file_pos];
	if (msh->mpip->infile == NULL && type == REDIR_IN)
	{
		ft_fd_printf(2, E_NW);
		return ;
	}
	// if (is_builtin(msh->tkns->cmd))
	// {
	// 	manage_builting_redir(msh, type);
	// 	return ;
	// }
	exec_redir(msh, msh->tkns->cmd, type);
	restore_redirections(msh);
}
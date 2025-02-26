/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:57:05 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/26 19:57:18 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_file(t_msh *msh, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (access(filename, F_OK) == 0)
			ft_fd_printf(2, "minishell: %s: Permission denied\n", filename);
		else
			ft_fd_printf(2, "minishell: %s: No such file or directory\n", filename);
		return (FALSE);
	}
	msh->mpip->backup_in = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (FALSE);
	close(fd);
	return (TRUE);
}
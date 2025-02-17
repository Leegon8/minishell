/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:16:01 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/12 12:16:13 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redir(t_tok *tok, char *file, int append)
{
	int	flags;

	if (tok->out_fd > 2)
		close(tok->out_fd);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	tok->out_fd = open(file, flags, 0644);
	if (tok->out_fd == -1)
	{
		ft_fd_printf(2, "minishell: %s: Permission denied\n", file);
		return (FALSE);
	}
	return (TRUE);
}

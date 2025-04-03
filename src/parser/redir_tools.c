/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:28:23 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/03 16:28:38 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(t_msh *msh)
{
	int	i;

	i = 0;
	msh->tkns->count_redir = 0;
	while (msh->tkns->args[i])
	{
		if (ft_strcmp(msh->tkns->args[i], ">") == 0)
			msh->tkns->count_redir++;
		else if (ft_strcmp(msh->tkns->args[i], "<") == 0)
			msh->tkns->count_redir++;
		else if (ft_strcmp(msh->tkns->args[i], ">>") == 0)
			msh->tkns->count_redir++;
		else if (ft_strcmp(msh->tkns->args[i], "<<") == 0)
			msh->tkns->count_redir++;
		i++;
	}
	printf("Tiene %d redirecciones\n", msh->tkns->count_redir);
	return (msh->tkns->count_redir);
}

int	handle_one_redir(t_msh *msh, int redir_pos, t_redir	redir_type)
{
	if (redir_type == REDIR_ERROR || redir_type == NO_REDIR)
		return (FALSE);
	if (redir_type == REDIR_OUT || redir_type == REDIR_APPEND)
		handle_redir_out(msh, redir_type);
	if (redir_type == REDIR_IN)
		handle_redir_in(msh, redir_type);
	if (redir_type == REDIR_HERE)
		handle_heredoc(msh, msh->tkns->args[redir_pos + 1]);
	if (redir_type == PIPE)
		handle_pipes(msh);
	return (TRUE);
}

int	handle_multiple_redir(t_msh *msh, int count, int redir_pos, t_redir type)
{
	while (count)
	{

	}
}

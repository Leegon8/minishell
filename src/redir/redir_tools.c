/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:28:23 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/05 10:26:17 by lprieto-         ###   ########.fr       */
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
		else if (ft_strcmp(msh->tkns->args[i], "|") == 0)
			msh->tkns->count_redir++;
		i++;
	}
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
	{
		if (!handle_heredoc(msh, msh->tkns->args[redir_pos + 1]))
			return (TRUE);
		exec_redir(msh, msh->tkns->cmd, redir_type);
		return (TRUE);
	}
	if (redir_type == PIPE)
		handle_pipes(msh);
	return (TRUE);
}

static int	find_next_redir(t_msh *msh, int start_pos)
{
	int	i;

	i = start_pos;
	while (msh->tkns->args[i])
	{
		if (ft_strcmp(msh->tkns->args[i], ">") == 0
			|| ft_strcmp(msh->tkns->args[i], "<") == 0
			|| ft_strcmp(msh->tkns->args[i], ">>") == 0
			|| ft_strcmp(msh->tkns->args[i], "<<") == 0
			|| ft_strcmp(msh->tkns->args[i], "|") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	handle_multip_redir(t_msh *msh, int count, int redir_pos, t_redir type)
{
	int		i;
	int		current_pos;
	t_redir	current_type;

	i = 0;
	current_pos = redir_pos;
	current_type = type;
	printf("Tiene %d redirecciones\n", count);
	while (i < count)
	{
		if (current_type == REDIR_ERROR || current_type == NO_REDIR)
			return (FALSE);
		msh->tkns->redir_pos = current_pos;
		// Manejar la redirección actual
		if (current_type == REDIR_OUT || current_type == REDIR_APPEND)
			handle_redir_out(msh, current_type);
		else if (current_type == REDIR_IN)
			handle_redir_in(msh, current_type);
		else if (current_type == REDIR_HERE)
			handle_heredoc(msh, msh->tkns->args[current_pos + 1]);
		else if (current_type == PIPE)
			handle_pipes(msh);
		// Buscar la siguiente redirección
		current_pos = find_next_redir(msh, current_pos + 2);
		if (current_pos == -1)
			break ;
		current_type = check_syntax_redir(msh, msh->tkns->args, current_pos);
		i++;
	}
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:45:27 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/30 09:21:57 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Comprueba cada token y su siguiente para operador (incompleta) */
int	lexer(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->tkns[i].cmd)
	{
		if (ft_strcmp(msh->tkns[i].cmd, "|") == 0)
		{
			if (i == 0 || msh->tkns[i + 1].cmd == NULL)
			{
				perror("syntax error near unexpected token `|'\n");
				return (-1);
			}
		}
		if (ft_strcmp(msh->tkns[i].cmd, "<<") == 0)
		{
			if (msh->tkns[i + 1].cmd == NULL)
			{
				perror("syntax error near unexpected token `newline'\n");
				return (-1);
			}
			msh->tkns->is_heredoc = 1;
			msh->tkns->heredoc_delim = ft_strdup(msh->tkns[i + 1].cmd);
			i++;
		}
		i++;
	}
	return (0);
}

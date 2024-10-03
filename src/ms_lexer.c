/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:45:27 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/03 13:42:18 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Comprueba cada token y su siguiente para operador (incompleta) */
int	lexer(char **tokens, t_msh *msh)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (i == 0 || tokens[i + 1] == NULL)
			{
				perror("syntax error with | operator\n");
				return (-1);
			}
		}
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (tokens[i + 1] == NULL)
			{
				perror("syntax error: missing delimiter for heredoc\n");
				return (-1);
			}
			msh->tkns->is_heredoc = 1;
			msh->tkns->heredoc_delim = ft_strdup(tokens[i + 1]);
			i++;
		}
		i++;
	}
	return (0);
}

void	check_tokens(char *input, t_msh *msh)
{
	int		i;
	int		count_tok;

	i = 0;
	count_tok = 0;
	if (tokenize_input(input, msh) == 0)
	{
		while (msh->tkns[count_tok].cmd)
			count_tok++;
		while (msh->tkns[i].cmd)
		{
			if (ft_strcmp(msh->tkns[i].cmd, "echo") == 0)
				ft_echo(msh, count_tok);
			if (ft_strcmp(msh->tkns[i].cmd, "cd") == 0)
				ft_cd(msh, count_tok);
			i++;
		}
	}
}

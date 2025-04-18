/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:21:38 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/15 13:21:51 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Counter of all the positions of redirections
int	*find_piperedir(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	msh->tkns->countpip = malloc(sizeof(int) * 1024);
	if (has_redirection(msh->tkns) != -1)
	{
		while (msh->tkns->args[i])
		{
			if (i == 0)
			{
				msh->tkns->countpip[j] = has_redirection(msh->tkns);
				j++;
			}
			if (msh->tkns->countpip[j - 1] != find_next_redir(msh, i)
				&& find_next_redir(msh, i) != -1)
			{
				msh->tkns->countpip[j] = find_next_redir(msh, i);
				j++;
			}
			i++;
		}
	}
	return (msh->tkns->countpip);
}

// Definition of witch type is every redirection
void	type_def(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	msh->tkns->typepip = malloc(sizeof(int) * 1024);
	while (msh->tkns->countpip[i])
	{
		msh->tkns->typepip[j] = check_syntax_redir(msh, msh->tkns->args,
			msh->tkns->countpip[i]);
		j++;
		i++;
	}
}

// Check syntax
int	type_verif(t_msh *msh)
{
	// int	i;

	// i = 0;
	if (ft_strcmp(msh->tkns->args[0], "|"))
	{
		print_error_msg('|');
		return (FALSE);
	}
	return (TRUE);
}
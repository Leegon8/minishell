/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:41:10 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/07 13:57:13 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Imprime los argumentos de echo, opción -n para suprimir el \n final */
void	ft_echo(t_msh *msh, int num_cmd)
{
	int		i;
//	int		j;
	int		n_option;

	i = 1;
	n_option = 0;
	if (num_cmd <= 1)
		printf("\n");
	else if (num_cmd > 1)
	{
		if (ft_strcmp(msh->tkns[i].cmd, "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (msh->tkns[i].cmd)
		{
			//if (msh->tkns[i].cmd == '\'' || msh->tkns[i].cmd == '\"')
			//	i++;
			printf("%s", msh->tkns[i].cmd);
			if (msh->tkns[i + 1].cmd != NULL)
				printf(" ");
			i++;
		}
		if (n_option == 0)
			printf("\n");
	}
}
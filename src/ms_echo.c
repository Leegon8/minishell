/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:21:27 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/03 14:40:00 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Imprime los argumentos de echo, opción -n para suprimir el \n final */
void	ft_echo(t_msh *msh, int num_cmd)
{
	int		i;
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
			printf("%s", msh->tkns[i].cmd);
			if (msh->tkns[i + 1].cmd != NULL)
				printf(" ");
			i++;
		}
		if (n_option == 0)
			printf("\n");
	}
}

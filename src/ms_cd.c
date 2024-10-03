/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:41:10 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/03 14:41:30 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_msh *msh, int num_cmd)
{
	//int	i;

	//i = 0;
	if (num_cmd == 1)
	{
		printf("Entra en la funcion cd\n");
		chdir(msh->env->home);
	}
	else
		printf("ola caracola ns q aser\n");
}
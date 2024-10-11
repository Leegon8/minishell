/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:13:40 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/06 19:28:10 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Actualizar env (TO DO) */


/* builtin para imprimir el environment */
int	ft_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env->names[i] && msh->env->values[i])
	{
		ft_fd_printf(1, "%s=%s\n", msh->env->names[i],
			msh->env->values[i]);
		//ft_fd_printf(1, "O %s\n", msh->envs[i]);
		i++;
	}
	return (1);
}

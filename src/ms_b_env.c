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

/* builtin para imprimir el environment */
int	ft_env(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env->names[i] && msh->env->values[i])
	{
		ft_fd_printf(1, "C %d > %s=%s\n", i, msh->env->names[i],
			msh->env->values[i]);
		ft_fd_printf(1, "O %d > %s\n", i, msh->envs[i]);
		i++;
	}
	return (1);
}

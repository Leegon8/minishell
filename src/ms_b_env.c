/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:13:40 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/04 13:13:47 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* builtin para imprimir el environment */
int ft_env(t_msh *msh)
{
    int i;

    i = 0;
    while (msh->env->names[i] && msh->env->values[i])
    {
        ft_fd_printf(1, "C %d > %s=%s\n", i, msh->env->names[i], msh->env->values[i]);
        ft_fd_printf(1, "O %d > %s\n", i, msh->envs[i]);
        i++;
    }
    return (1);
}

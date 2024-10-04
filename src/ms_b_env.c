/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:43:41 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/04 10:59:19 by lprieto-         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:43:41 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/04 09:50:56 by lprieto-         ###   ########.fr       */
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
        ft_fd_printf(1, "%s=%s\n", msh->env->names[i], msh->env->values[i]);
        i++;
    }
    return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:49:27 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/23 11:08:16 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* inicia las estructuras del .h (no borrar) No trabajo en ella */
/* hay que modificarla para que haga reserva de memoria tambien */
int	init_structs(t_env *env, t_mshll *msh, t_pip *mpip)
{
	ft_bzero(env, sizeof(t_env));
	ft_bzero(msh, sizeof(t_mshll));
	ft_bzero(mpip, sizeof(t_pip));
	return (0);
}

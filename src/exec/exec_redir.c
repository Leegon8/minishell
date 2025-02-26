/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:31:02 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/26 16:31:16 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
    1. Necesitamos la posición donde se encuentra la redirección para ignorarlo
    2. Primer comando
    3. Nombre del archivo en caso de redirección de salida (>)
*/

void	exec_redir(t_msh *msh)
{
	printf("cmd --> %s\n", cmd);
	if (is_builtin(cmd))
	{
		printf("Hay que gestionar builtings conredirecciones\n");
		return ;
	}
	else
	{
		create_token
		find_cmd(msh)
	}

}
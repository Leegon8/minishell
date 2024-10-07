/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:41:10 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/07 17:43:43 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Imprime los argumentos de echo, opción -n para suprimir el \n final */
void	ft_cd(t_msh *msh, int num_cmd)
{
	DIR	*new_path;
	int	i;
	
	i = 1;
	new_path = NULL;
	if (num_cmd > 2)
		ft_fd_printf(2, "bash: %s: too many arguments\n", msh->tkns->cmd);
	else if (num_cmd == 1)
		chdir(msh->env->home);
	/*else if (num_cmd == 2)
	{
		printf("%d, Entra en cd function\n", num_cmd);
		new_path = opendir(msh->tkns[i].cmd);
		readdir(new_path);
		ft_pwd(msh);
	}*/
}
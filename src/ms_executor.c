/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:13:10 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/25 12:37:11 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exec(t_msh *msh)
{
	if (ft_strcmp("pwd", msh->tkns[0].cmd) == 0) /* pwd */
			printf("%s\n", msh->env->pwd);			
	else if (ft_strcmp("clear", msh->tkns[0].cmd) == 0) /* clear :D */
		 	printf("%s", CLEAR);
	else if (ft_strcmp("exit", msh->tkns[0].cmd) == 0) /* para hacer exit sin ctrl+C */
	{
		msh->end_sig = 1;
		exit(msh->end_sig);
	}
}

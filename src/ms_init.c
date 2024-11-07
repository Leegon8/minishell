/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:49:27 by lprieto-          #+#    #+#             */
/*   Updated: 2024/11/03 10:44:43 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* inicia la asignacion de memoria para env en relacion al envs (del sistema) */
int	env_alloc_struct(t_env **env, t_msh *msh)
{
	size_t	env_count;

	*env = malloc(sizeof(t_env));
	if (!*env)
		return (-1);
	ft_memset(*env, 0, sizeof(t_env));
	(*env)->pwd = malloc(PATH_MAX);
	if (!(*env)->pwd)
		return (-1);
	env_count = env_var_count(msh);
	(*env)->names = malloc(sizeof(char *) * (env_count + 1));
	if (!(*env)->names)
		return (-1);
	(*env)->values = malloc(sizeof(char *) * (env_count + 1));
	if (!(*env)->values)
		return (-1);
	(*env)->names[env_count] = NULL;
	(*env)->values[env_count] = NULL;
	return (0);
}

/* inicia la asignacion de memoria  para tok */
int	tok_alloc_struct(t_tok **tok)
{
	*tok = malloc(sizeof(t_tok));
	if (!*tok)
		return (-1);
	ft_memset(*tok, 0, sizeof(t_tok));
	return (0);
}

/* inicia la asignacion de memoria  para mpip */
int	mpip_alloc_struct(t_exe **mpip)
{
	*mpip = malloc(sizeof(t_exe));
	if (!*mpip)
		return (-1);
	ft_memset(*mpip, 0, sizeof(t_exe));
	return (0);
}

/* inicia las estructuras por separado y las enlaza a msh */
int	init_structs(t_env **env, t_msh *msh, t_exe **mpip, t_tok **tok)
{
	if (env_alloc_struct(env, msh))
		return (ft_fd_printf(2, "%s", E_ENVGET) * -1);
	msh->env = *env;
	if (tok_alloc_struct(tok))
	{
		free(*env);
		return (ft_fd_printf(2, "%s", E_TOKMEM) * -1);
	}
	msh->tkns = *tok;
	if (mpip_alloc_struct(mpip))
	{
		free(*env);
		free(*tok);
		return (ft_fd_printf(2, "%s", E_PIPMEM) * -1);
	}
	msh->mpip = *mpip;
	return (0);
}

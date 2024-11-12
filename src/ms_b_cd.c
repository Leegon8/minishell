/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:41:10 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/11 18:41:17 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	*handle_cd_home(t_msh *msh, char *cmd)
{
	char	*home_path;
	char	*result;

	if (!msh->env->home)
	{
		ft_fd_printf(2, "cd: HOME not set\n");
		return (NULL);
	}
	if (!cmd[1])
		result = ft_strdup(msh->env->home);
	else
	{
		home_path = ft_strjoin(msh->env->home, cmd + 1);
		result = ft_strdup(home_path);
		free(home_path);
	}
	return (result);
}

static char	*handle_cd_minus(t_msh *msh)
{
	if (!msh->env->old_pwd)
	{
		ft_fd_printf(2, "cd: OLDPWD not set\n");
		return (NULL);
	}
	ft_fd_printf(1, "%s\n", msh->env->old_pwd);
	return (ft_strdup(msh->env->old_pwd));
}

static void	handle_cd_execute(t_msh *msh, char *path)
{
	if (!path)
		return ;
	if (chdir(path) == -1)
		handle_cd_error(msh->tkns[1].cmd, errno);
	else
	{
		msh->env->old_pwd = update_env(msh, "OLDPWD", msh->env->pwd);
		msh->env->pwd = update_env(msh, "PWD", msh->env->home);
	}
	free(path);
}

void	handle_cd_path(t_msh *msh)
{
	char	*new_path;

	new_path = NULL;
	if (varenv_man(msh, "cd", msh->tkns->args[1]) != 0)
		return ;
	if (msh->tkns->args[1][0] == '-' && msh->tkns->args[1][1] == '\0')
		new_path = handle_cd_minus(msh);
	else if (msh->tkns->args[1][0] == '~')
		new_path = handle_cd_home(msh, msh->tkns[1].cmd);
	else if (msh->tkns->args[1][0] == '/')
		new_path = ft_strdup(msh->tkns->args[1]);
	else
		new_path = make_relative(msh->tkns->args[1], msh);
	if (!new_path)
	{
		ft_fd_printf(2, "cd: memory allocation error\n");
		return ;
	}
	handle_cd_execute(msh, new_path);
}

void	ft_cd(t_msh *msh, int num_cmd)
{
	if (num_cmd > 3)
		ft_fd_printf(2, "bash: %s: too many arguments\n", msh->tkns->cmd);
	else if (num_cmd == 1)
	{
		if (!msh->env->home)
			ft_fd_printf(2, "cd: HOME not set\n");
		else
			chdir(msh->env->home);
	}
	else if (num_cmd <= 3)
		handle_cd_path(msh);
}*/

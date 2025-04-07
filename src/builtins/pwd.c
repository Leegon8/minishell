/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:14:23 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/07 23:29:22 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_msh *msh)
{
	char	*pwdpath;
	int		status;

	status = 0;
	pwdpath = NULL;
	pwdpath = malloc(PATH_MAX);
	if (!pwdpath)
		return (FALSE);
	if (!getcwd(pwdpath, PATH_MAX))
	{
		free(pwdpath);
		return (FALSE);
	}
	update_env(msh, "PWD", pwdpath);
	if (ft_fd_printf(1, "%s\n", pwdpath) < 0)
		status = -1;
	free(pwdpath);
	return (status);
}

int	builtin_redir_check(t_msh *msh)
{
	if (ft_strcmp(msh->tkns->args[1], ">") == 0
		|| ft_strcmp(msh->tkns->args[1], ">>") == 0
		|| ft_strcmp(msh->tkns->args[1], "<") == 0
		|| ft_strcmp(msh->tkns->args[1], "<<") == 0)
		return (TRUE);
	return (FALSE);
}

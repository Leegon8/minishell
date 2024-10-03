/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:56:15 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/03 11:15:59 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_msh *msh)
{
    char    *pwdpath;

    pwdpath = (char *)malloc(sizeof(char) * PATH_MAX);
    if (!pwdpath)
        return (-1);
    getcwd(pwdpath, PATH_MAX);
    msh->env->pwd = pwdpath;
    ft_fd_printf(1, "%s", pwdpath);
    free(pwdpath);
    return (1);
}
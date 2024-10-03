/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:28:03 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/03 11:26:10 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cmd_not_found(t_msh *msh)
{
    ft_fd_printf(2, "Error: ");
    ft_fd_printf(2, "%s", msh->tkns->cmd);
    ft_fd_printf(2, ": command not found\n");
    exit (127);
}

int  is_builtin(t_msh *msh)
{
    // if (ft_strcmp(msh->tkns->cmd, "echo") == 0)
    //     ft_echo(msh);
    // else if (ft_strcmp(msh->tkns->cmd, "cd") == 0)
    //     ft_cd(msh);
    if (ft_strcmp(msh->tkns->cmd, "pwd") == 0)
        ft_pwd(msh);
    // else if (ft_strcmp(msh->tkns->cmd, "export") == 0)
    //     ft_export(msh);
    // else if (ft_strcmp(msh->tkns->cmd, "unset") == 0)
    //     ft_unset(msh);
    else if (ft_strcmp(msh->tkns->cmd, "env") == 0)
        ft_env(msh);
    else if (ft_strcmp(msh->tkns->cmd, "exit") == 0)
        ft_exit(msh);
    else
        return (-1);
    return (1);
}
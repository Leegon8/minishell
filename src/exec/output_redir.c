/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:16:01 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/17 15:57:56 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  handle_output_file(t_msh *msh, char *filename)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        if (access(filename, F_OK) == 0)
            ft_fd_printf(2, "minishell: %s: Permission denied\n", filename);
        else
            ft_fd_printf(2, "minishell: %s: No such file or directory\n", filename);
        return (FALSE);
    }
    msh->mpip->backup_out = dup(STDOUT_FILENO);
    if (dup2(fd, STDOUT_FILENO) == -1)
        return (FALSE);
    close(fd);
    return (TRUE);
}

int  handle_input_file(t_msh *msh, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        if (access(filename, F_OK) == 0)
            ft_fd_printf(2, "minishell: %s: Permission denied\n", filename);
        else
            ft_fd_printf(2, "minishell: %s: No such file or directory\n", filename);
        return (FALSE);
    }
    msh->mpip->backup_in = dup(STDIN_FILENO);
    if (dup2(fd, STDIN_FILENO) == -1)
        return (FALSE);
    close(fd);
    return (TRUE);
}

void    restore_redirections(t_msh *msh)
{
    if (msh->mpip->backup_out != -1)
    {
        dup2(msh->mpip->backup_out, STDOUT_FILENO);
        close(msh->mpip->backup_out);
        msh->mpip->backup_out = -1;
    }
    if (msh->mpip->backup_in != -1)
    {
        dup2(msh->mpip->backup_in, STDIN_FILENO);
        close(msh->mpip->backup_in);
        msh->mpip->backup_in = -1;
    }
}
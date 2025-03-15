/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:16:01 by lauriago          #+#    #+#             */
/*   Updated: 2025/03/15 17:54:11 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_output_file(t_msh *msh, char *filename, t_redir type)
{
    int fd;

    if (!filename || !*filename) // Validar que el nombre del archivo no sea NULL o vacío
    {
        ft_fd_printf(2, "bash: Redirección: Nombre de archivo inválido\n");
        return (FALSE);
    }

    msh->mpip->backup_out = dup(STDOUT_FILENO);
    if (msh->mpip->backup_out == -1)
    {
        perror("Error duplicando stdout");
        return (FALSE);
    }

    if (type == REDIR_OUT)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (type == REDIR_APPEND)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
    {
        ft_fd_printf(2, "bash: Redirección: Tipo de redirección inválido\n");
        close(msh->mpip->backup_out);
        return (FALSE);
    }

    if (fd == -1)
    {
        perror("Error abriendo archivo");
        close(msh->mpip->backup_out);
        return (FALSE);
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Error redirigiendo stdout");
        close(msh->mpip->backup_out);
        close(fd);
        return (FALSE);
    }

    close(fd); // Cerrar el descriptor del archivo después de redirigir
    return (TRUE);
}

void	restore_redirections(t_msh *msh)
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

// void restore_redirections(t_msh *msh)
// {
//     // Restaurar stdout si fue cambiado
//     if (msh->saved_stdout > 0)
//     {
//         dup2(msh->saved_stdout, STDOUT_FILENO);
//         close(msh->saved_stdout);
//         msh->saved_stdout = -1;
//     }
//     // Agregar más restauraciones según sea necesario
// }
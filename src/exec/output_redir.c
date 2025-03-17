/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:16:01 by lauriago          #+#    #+#             */
/*   Updated: 2025/03/10 10:22:36 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_output_file(t_msh *msh, char *filename, t_redir type)
{
	int fd;
	
	msh->mpip->backup_out = dup(STDOUT_FILENO);
	fd = 0;
	printf("Entra a handle_output_file\n");
	if (msh->mpip->backup_out == -1)
	{
		printf("No hay backup_out ERROR!\n");
		return (FALSE);
	}
	if (type == REDIR_OUT)
	{
		printf("Es REDIR_OUT\n");
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (type == REDIR_APPEND) // REDIR_APPEND
	{
		printf("Es REDIR_APPEND!\n");
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd == -1)
	{
		perror ("Error opening file");
		return (FALSE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting soutput");
		close(msh->mpip->backup_out); 
		close(fd);
		return (FALSE);
	}
	printf("Sale de handle_output_file with success exit\n");
	close(fd);
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
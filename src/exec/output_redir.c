/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:16:01 by lauriago          #+#    #+#             */
/*   Updated: 2025/03/16 19:52:42 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_output_file(t_msh *msh, char *filename, t_redir type)
{
	int fd;
	
	printf("DEBUG: Guardando descriptor original (STDOUT_FILENO=%d)\n", STDOUT_FILENO);
	msh->mpip->backup_out = dup(STDOUT_FILENO);
	printf("DEBUG: Descriptor guardado en backup_out=%d\n", msh->mpip->backup_out);
	fd = 0;
	if (msh->mpip->backup_out == -1)
	{
		perror("ERROR: No se pudo duplicar STDOUT_FILENO");
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
		printf("DEBUG: Restaurando STDOUT_FILENO desde backup_out=%d\n", msh->mpip->backup_out);
		int result = dup2(msh->mpip->backup_out, STDOUT_FILENO);
		printf("DEBUG: Resultado de dup2: %d\n", result);
		if (result == -1)
            perror("ERROR: No se pudo restaurar STDOUT_FILENO");
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


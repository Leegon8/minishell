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

int handle_output_file(t_msh *msh, char *filename)
{
	int fd;
	
	msh->mpip->backup_out = dup (STDOUT_FILENO);
	if (msh->mpip->backup_out == -1)
		return (FALSE);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("AQUI1111111111111 --`----> out = %d\n", fd);
	if (fd == -1)
	{
		perror ("minishell");
		return (FALSE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(msh->mpip->backup_out);
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (1);
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

char	*extract_command(char**args, int redir_pos)
{
	char	*fullpath;
	char	*tmp;
	int		i;

	i = 0;
	fullpath = NULL;
	tmp = NULL;
	if (!args || !args[0])
		return (NULL);
 	fullpath = ft_strdup(args[0]);
	if (!fullpath)
		return (NULL); 
	while (i < redir_pos && args[i])
	{
		if (args[0])
			i++;
		tmp = ft_strjoin(fullpath, " ");
		free(fullpath);
		fullpath = NULL;
		fullpath = ft_strjoin(tmp, args[i]);
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (fullpath);
}

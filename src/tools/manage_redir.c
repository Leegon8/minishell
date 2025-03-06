/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:49:04 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/28 16:49:28 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	redirection_manager(t_msh *msh, t_redir type)
// {
// 	char	*cmd;
// 	int		i;

// 	i = 0;
// 	printf("ENTRA EN MANAGER REDIR!!!\n");
// 	printf("cmd = %s.\n", msh->tkns->cmd);
// 	if (!is_builtin(msh->tkns->cmd))
// 	{
// 		while (i < msh->tkns->redir_pos)
// 		{
// 			cmd = malloc(sizeof(char) * ft_strlen(msh->tkns->args[i] + 1));
// 			if (!cmd)
// 				return ;
// 			if (i == 0)
// 				cmd = ft_strdup(msh->tkns->args[i]);
// 			else
// 				ft_strjoin(cmd, msh->tkns->args[i]);
// 			i++;
// 		}
// 		cmd[i] = 0;
// 		printf("cmd = %s.\n", cmd);
// 	} 
// }

/* static char **extract_command(char **args, int redir_pos)
{
    char **cmd_args = malloc(sizeof(char *) * (redir_pos + 1));
    if (cmd_args == NULL)
        return NULL;

    for (int i = 0; i < redir_pos; i++)
    {
        cmd_args[i] = strdup(args[i]);
        if (cmd_args[i] == NULL)
        {
            // Liberar memoria asignada si hay un error
            for (int j = 0; j < i; j++)
                free(cmd_args[j]);
            free(cmd_args);
            return NULL;
        }
    }
    cmd_args[redir_pos] = NULL;

    return cmd_args;
}


void handle_redir(t_msh *msh, t_redir type)
{
    int file_pos;
    pid_t pid;

    file_pos = msh->tkns->redir_pos + 1;
	printf("filename = %s\n",msh->tkns->args[file_pos]);
    if (type == REDIR_OUT || type == REDIR_APPEND)
    {
        // ... (código de redirección existente) ...
		msh->mpip->outfile = msh->tkns->args[file_pos];
		if (msh->mpip->outfile == NULL)
		{
			ft_fd_printf(2, E_NW);
			return ;	
		}
        // Crear un proceso hijo
        pid = fork();
        if (pid == -1)
        {
            ft_fd_printf(2, "Error al crear el proceso hijo\n");
            return;
        }
        else if (pid == 0)
        {
            // Proceso hijo
            char **cmd_args = extract_command(msh->tkns->args, msh->tkns->redir_pos);
            if (cmd_args == NULL)
            {
                ft_fd_printf(2, "Error al extraer el comando\n");
                exit(EXIT_FAILURE);
            }

            execvp(cmd_args[0], cmd_args);
            ft_fd_printf(2, "Error al ejecutar el comando\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Proceso padre
            int status;
            waitpid(pid, &status, 0);
        }

        // Restaurar STDOUT
        dup2(msh->mpip->backup_out, STDOUT_FILENO);
        close(msh->mpip->backup_out);
    }
} */



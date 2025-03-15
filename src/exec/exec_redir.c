/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:31:02 by lauriago          #+#    #+#             */
/*   Updated: 2025/03/15 17:42:07 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This function copy all the args without the redirection token 
static char	**redir_args(char** args, int redir_pos)
{
	char	**result;
	int	i;

	if (!args || redir_pos <= 0)
		return (NULL);
		result = (char **)malloc(sizeof(char *) * (redir_pos + 1));
	if (!result)
	{
		ft_fd_printf(2, "malloc failed");
		return (NULL);
	}
	i = 0;
	while ( i < redir_pos && args[i])
	{
		result[i] = ft_strdup(args[i]);
		if (!result[i])
			ft_free_array(result);
		i++;
	}
	result[i] = NULL;
	return (result);
}

static void	child_process_redir(t_msh *msh, char *fullpath, t_redir type)
{
    char	**new_args;

    new_args = redir_args(msh->tkns->args, msh->tkns->redir_pos);
    if (!new_args)
    {
        free(fullpath);
        exit(EXIT_FAILURE);
    }

    if (!handle_output_file(msh, msh->mpip->outfile, type))
    {
        free(fullpath);
        ft_free_array(new_args);
        exit(EXIT_FAILURE);
    }

    printf("Ejecutando execve con fullpath = %s\n", fullpath);
    if (execve(fullpath, new_args, msh->envs) == -1)
    {
        perror("Error ejecutando execve");
        cmd_not_found(msh);
        free(fullpath);
        ft_free_array(new_args);
        exit(EXIT_FAILURE);
    }
}

void	exec_redir(t_msh *msh, char *tkn, t_redir type)
{
    pid_t	pid;
    char 	*fullpath;
    int		status;

    fullpath = make_path(tkn, msh);
    printf("tkn = %s.\n", fullpath);
    pid = fork();
    if (pid == -1)
    {
        ft_fd_printf(2, "bash: fork: Cannot allocate memory\n");
        return ;
    }
    if (pid == 0)
    {
        printf("Proceso hijo iniciado.\n");
        child_process_redir(msh, fullpath, type);
    }
    else
    {
        printf("Esperando al proceso hijo con PID %d.\n", pid);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Proceso hijo terminó con código de salida %d.\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Proceso hijo terminó debido a una señal: %d.\n", WTERMSIG(status));
    }
    printf("TERMINANDO EXEC_REDIR\n");
    restore_redirections(msh);
}

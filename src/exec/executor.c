/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:13:10 by lprieto-          #+#    #+#             */
/*   Updated: 2025/03/10 10:19:58 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int setup_redirections(t_msh *msh)
{
    if (msh->mpip->outfile)
    {
        printf("Redirecting output to: %s\n", msh->mpip->outfile);
        if (!handle_output_file(msh, msh->mpip->outfile))
            return (FALSE);
    }
    if (msh->mpip->infile)
    {
        printf("Redirecting input from: %s\n", msh->mpip->infile);
        if (!handle_input_file(msh, msh->mpip->infile))
            return (FALSE);
    }
    return (TRUE);
}

int	is_command_executable(char *fullpath)
{
	if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
		return (TRUE);
	else
		printf("COMANDO NO EJECUTABLE\n");
	return (FALSE);
}

static void	child_process(t_msh *msh, char *fullpath)
{
	if (!setup_redirections(msh))  // Añadir esta línea
	{
		free(fullpath);
		exit(EXIT_FAILURE);
	}
	if (execve(fullpath, msh->tkns->args, msh->envs) == -1)
	{
		cmd_not_found(msh);
		free(fullpath);
		exit(EXIT_FAILURE);
	}
}

static void	parent_process(pid_t pid, char *fullpath)
{
	int	status;

	waitpid(pid, &status, 0);
	free(fullpath);
}

int	execute_command(t_msh *msh, char *fullpath)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_fd_printf(2, "bash: fork: Cannot allocate memory\n");
		free(fullpath);
		return (-1);
	}
	else if (pid == 0)
		child_process(msh, fullpath);
	else
		parent_process(pid, fullpath);
	return (TRUE);
}

// int	find_cmd(char *tkn, t_msh *msh)
// {
// 	char	*fullpath;
// 	char	*cmd;
// 	int		i;
	
// 	i = 0;
// 	while (tkn[i] != '>' && tkn[i] != '<' && tkn[i] != '\0')
// 	{
// 		printf("token string %s\n", tkn);
// 		printf("token [%d]: %d\n", i, tkn[i]);
// 		printf("1 token poition FIND_CMD = %d\n", i);
//         i++;
// 		if (tkn[i] == ' ')
// 			i--;
// 	}

// 	printf("2 token poition FIND_CMD = %d\n", i);

//     cmd = ft_strndup(tkn, i);
// 	//printf("fullpath = %s\ntkn = %s\n", fullpath, tkn);
// 	printf("CMD = %s .\n", cmd);
// 	if (msh->tkns->redir_pos >= 0)
// 		fullpath = ft_strdup(cmd);
// 	else
// 		fullpath = make_path(tkn, msh);
// 	free(cmd);
// 	if (is_command_executable(fullpath))
// 	{
// 		printf("IAODJFPIJFSPJFSPIJFJSIPFPIIIIIIIIIII\n");
// 		if (!execute_command(msh, fullpath))
// 			return (-1);
// 	}
// 	else
// 	{
// 		free(fullpath);
// 		return (-1);
// 	}
// 	return (TRUE);
// }

int find_cmd(char *tkn, t_msh *msh)
{
    char *fullpath;
    char *cmd;
    int i;
    int end;

    i = 0;
    while (tkn[i] != '>' && tkn[i] != '<' && tkn[i] != '\0')
    {
        // printf("token string %s\n", tkn);
        // printf("token [%d]: %d\n", i, tkn[i]);
        // printf("1 token poition FIND_CMD = %d\n", i);
        i++;
    }
    printf("token poition FIND_CMD = %d\n", i);

    // Encontrar el último carácter no espacio
    end = i - 1;
    while (end >= 0 && tkn[end] == ' ')
        end--;

    cmd = ft_strndup(tkn, end + 1);
    printf("CMD = %s.\n", cmd);
	
    if (msh->tkns->redir_pos >= 0)
        fullpath = ft_strdup(cmd);
    else
        fullpath = make_path(cmd, msh);
    free(cmd);

    if (is_command_executable(fullpath))
    {
        printf("IAODJFPIJFSPJFSPIJFJSIPFPIIIIIIIIIII\n");
        if (!execute_command(msh, fullpath))
            return (-1);
    }
    else
    {
        free(fullpath);
        return (-1);
    }
    return (TRUE);
}

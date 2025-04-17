/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:49:04 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/17 23:02:57 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipes(t_msh *msh)
{
	int	count;

	if (!msh || !msh->tkns)
		return ;
	count = parse_and_validate_commands(msh, msh->tkns, &msh->cmds);
	if (count <= 0)
		return ;
	msh->cmd_count = count;
	execute_pipeline(msh);
	restore_signals();
	cleanup_commands(msh);
}

// static void	exec_command(t_msh *msh, int i)
// {
// 	char	*path;

// 	if (is_builtin(msh->cmds[i].args[0]))
// 	{
// 		msh->tkns->cmd = ft_strdup(msh->cmds[i].args[0]);
// 		msh->tkns->args = msh->cmds[i].args;
// 		exc_cmd(msh, i);
// 		exit(EXIT_SUCCESS);
// 	}
// 	path = make_path(msh->cmds[i].args[0], msh);
// 	if (!path)
// 		cmd_not_found(msh);
// 	else
// 	{
// 		if (execve(path, msh->cmds[i].args, msh->envs) == -1)
// 		{
// 			free(path);
// 			ft_fd_printf(2, E_EXECVE);
// 		}
// 	}
// 	exit(EXIT_FAILURE);
// }

// static void	child_process(t_msh *msh, int i, int prev_fd, int pipe_fd[2])
// {
// 	if (prev_fd != -1)
// 	{
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 	}
// 	if (i < msh->cmd_count - 1)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[1]);
// 	}
// 	exec_command(msh, i);
// }

void	save_pipe_and_close(int *prev_fd, int *pipe_fd)
{
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

static void	exec_command(t_msh *msh, int i)
{
	char	*path;

	if (is_builtin(msh->cmds[i].args[0]))
	{
		msh->tkns->cmd = ft_strdup(msh->cmds[i].args[0]);
		msh->tkns->args = msh->cmds[i].args;
		exc_cmd(msh, i);
		exit(EXIT_SUCCESS);
	}
	path = make_path(msh->cmds[i].args[0], msh);
	if (!path)
		cmd_not_found(msh);
	else
	{
		if (execve(path, msh->cmds[i].args, msh->envs) == -1)
		{
			free(path);
			ft_fd_printf(2, E_EXECVE);
		}
	}
	exit(EXIT_FAILURE);
}

// static void	child_process(t_msh *msh, int i, int prev_fd, int pipe_fd[2])
// {
// 	if (prev_fd != -1)
// 	{
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 	}
// 	if (i < msh->cmd_count - 1)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], STDOUT_FILENO);
// 		close(pipe_fd[1]);
// 	}
// 	exec_command(msh, i);
// }

static void	child_process(t_msh *msh, int i, int prev_fd, int pipe_fd[2])
{
	// Redirigir stdin desde el comando anterior si existe
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(prev_fd);
	}

	// Redirigir stdout al siguiente comando si no soy el último
	if (i < msh->cmd_count - 1)
	{
		close(pipe_fd[0]); // No voy a leer del siguiente
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(pipe_fd[1]); // Ya no necesito la escritura directa
	}
	else
	{
		// Soy el último: cierro ambos extremos por limpieza
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

	// Ejecutar el comando con las redirecciones ya hechas
	exec_command(msh, i);

	// Si exec_command falla y no hace exit(), forzamos salida
	exit(EXIT_FAILURE);
}

int	execute_pipeline(t_msh *msh)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (i < msh->cmd_count)
	{
		if (i < msh->cmd_count - 1 && pipe(pipe_fd) == -1)
			return (ft_fd_printf(2, E_PIPE), -1);
		pid = fork();
		if (pid == -1)
			return (ft_fd_printf(2, E_FORK), -1);
		else if (pid == 0)
			child_process(msh, i, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (i < msh->cmd_count - 1)
		{
			prev_fd = pipe_fd[0];
			close(pipe_fd[1]);
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}



/*

void	handle_pipes(t_msh *msh)
{
	int	count;

	if (!msh || !msh->tkns)
		return ;
	count = parse_and_validate_commands(msh, msh->tkns, &msh->cmds);
	if (count <= 0)
		return ;
	msh->cmd_count = count;
	execute_pipeline(msh);
	restore_signals();
	cleanup_commands(msh);
}

static void	exec_command(t_msh *msh, int i)
{
	char	*path;

	if (is_builtin(msh->cmds[i].args[0]))
	{
		msh->tkns->cmd = ft_strdup(msh->cmds[i].args[0]);
		msh->tkns->args = msh->cmds[i].args;
		exc_cmd(msh, i);
		exit(EXIT_SUCCESS);
	}
	path = make_path(msh->cmds[i].args[0], msh);
	if (!path)
		cmd_not_found(msh);
	else
	{
		if (execve(path, msh->cmds[i].args, msh->envs) == -1)
		{
			free(path);
			ft_fd_printf(2, E_EXECVE);
		}
	}
	exit(EXIT_FAILURE);
}

static void	child_process(t_msh *msh, int i, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < msh->cmd_count - 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exec_command(msh, i);
}

int	execute_pipeline(t_msh *msh)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (i < msh->cmd_count)
	{
		if (i < msh->cmd_count - 1 && pipe(pipe_fd) == -1)
			return (ft_fd_printf(2, E_PIPE), -1);
		pid = fork();
		if (pid == -1)
			return (ft_fd_printf(2, E_FORK), -1);
		else if (pid == 0)
			child_process(msh, i, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (i < msh->cmd_count - 1)
			save_pipe_and_close(&prev_fd, pipe_fd);
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}

void	save_pipe_and_close(int *prev_fd, int *pipe_fd)
{
	close(pipe_fd[1]);
	*prev_fd = pipe_fd[0];
}

*/
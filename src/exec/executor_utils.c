/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:47:32 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/09 20:37:34 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Busca la variable PATH en el env
static char	**get_path_dirs(char **envs)
{
	int		i;

	i = 0;
	while (envs[i])
	{
		if (ft_strncmp(envs[i], "PATH=", 5) == 0)
			return (ft_split(envs[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

// 
static char	*check_absolute_path(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
		|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

// make the path of executable
char	*make_path(char *cmd, t_msh *msh)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	if (!cmd || !msh || !msh->envs)
		return (NULL);
	cmd_path = check_absolute_path(cmd);
	if (cmd_path)
		return (cmd_path);
	paths = get_path_dirs(msh->envs);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = try_path(paths[i], cmd);
		if (cmd_path)
		{
			ft_free_array(paths);
			return (cmd_path);
		}
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

// char	*make_path(char *cmd, t_msh *msh)
// {
// 	char	**paths;
// 	char	*cmd_path;
// 	int		i;

// 	if (!cmd || !msh || !msh->envs)
// 		return (NULL);
// 	cmd_path = check_absolute_path(cmd);
// 	if (cmd_path)
// 		return (cmd_path);
// 	paths = get_path_dirs(msh->envs);
// 	if (!paths)
// 	{
// 		ft_fd_printf(2, "%s: No such file or directory\n", cmd);
// 		msh->last_exit_code = 127;
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (paths[i])
// 	{
// 		cmd_path = try_path(paths[i], cmd);
// 		if (cmd_path)
// 		{
// 			ft_free_array(paths);
// 			return (cmd_path);
// 		}
// 		i++;
// 	}
// 	ft_free_array(paths);
// 	return (NULL);
// }
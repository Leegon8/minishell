/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:41:10 by lauriago          #+#    #+#             */
/*   Updated: 2024/10/07 17:43:43 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Verifies if it's a relative path & wich relative path type is */
int	is_relative(char *arg)
{
	int	i;

	i = 0;

	while (i < 2)
	{
		if (arg[i] == '.')
			i++;
		if (arg[i] == '-')
			return (2);
		return (1);
	}
	return (-1);
}

/* Converts a relative path to an absolute path */
char	*built_abspath(char *relative_path, char *pwd)
{
	char	*abs_path;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(relative_path) + ft_strlen(pwd) + 2;
	abs_path = malloc(sizeof(char) * len);
	i = -1;
	j = 0;
	if (!abs_path)
		return (NULL);
	while (pwd[++i])
		abs_path[j++] = pwd[i];
	abs_path[j++] = '/';
	i = -1;
	while (relative_path[++i])
		abs_path[j++] = relative_path[i];
	abs_path[j] = '\0';
//	printf("\nabs_path = %s\n", abs_path);
	return (abs_path);
}

/* Verifies the route & acces in case that exists */
void	ft_cd(t_msh *msh, int num_cmd)
{
	char	*new_path;

	new_path = NULL;
	if (num_cmd > 2)
		ft_fd_printf(2, "bash: %s: too many arguments\n", msh->tkns->cmd);
	else if (num_cmd == 1)
		chdir(msh->env->home);
	else if (num_cmd == 2)
	{
		if (msh->tkns[1].cmd[0] == '/') // Is an absolute path
			new_path = strdup(msh->tkns[1].cmd);
		else
			new_path = built_abspath(msh->tkns[1].cmd, msh->env->pwd);
		/*else if (is_relative(msh->tkns[1].cmd) == 2)
		{
			// Has to access to the before path
		}*/
		if (chdir(new_path) == -1)
			perror("cd");
		else
		{
			free(msh->env->pwd);
			msh->env->pwd = getcwd(NULL, 0);
		}
	}
}
// printf("pwd after chdir: %s\n", msh->env->pwd);

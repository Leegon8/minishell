/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_rline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:34:50 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/13 16:51:47 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_generator(const char *text, int state)
{
	static int	lst_idx;
	static int	len;
	char		*name;
	static char	*cmd_lst[] = {"cd", "exit", "ls", "mkdir", "touch", "clear"};

	if (!state)
	{
		lst_idx = 0;
		len = ft_strlen(text);
	}
	while ((name = cmd_lst[lst_idx++]))
	{
		if (ft_strncmp(name, text, len) == 0)
			return (ft_strdup(name));
	}
	return (NULL);
}

char	**command_completion(const char *text, int start, int end)
{
	char	**matches;

	matches = NULL;
	if (start != 0 && end > start)
		matches = rl_completion_matches(text, file_generator);
	else
		matches = rl_completion_matches(text, command_generator);
	return (matches);
}

char	*file_generator(const char *text, int state)
{
	static DIR				*dir;
	static struct dirent	*entry;
	int						len;

	len = ft_strlen(text);
	if (!state)
		dir = opendir(".");
	if (dir)
	{
		while ((entry = readdir(dir)))
		{
			if (ft_strncmp(entry->d_name, text, len) == 0)
				return (ft_strdup(entry->d_name));
		}
		closedir (dir);
		dir = NULL;
	}
	return (NULL);
}

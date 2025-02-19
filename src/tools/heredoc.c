/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:29:27 by lprieto-          #+#    #+#             */
/*   Updated: 2025/02/19 02:31:35 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_until_delimiter(char *delimiter)
{
	char	*line;
	char	*content;
	char	*temp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		temp = content;
		content = ft_strjoin(content, "\n");
		free(temp);
		free(line);
	}
	return (content);
}

int	handle_heredoc(t_msh *msh, char *delimiter)
{
	char	*content;

	handle_heredoc_signals();
	content = read_until_delimiter(delimiter);
	restore_signals();
	if (!content)
		return (FALSE);
    (void)msh;
	// Por ahora solo imprimimos el contenido
	ft_putstr_fd(content, 1);
	free(content);
	return (TRUE);
}
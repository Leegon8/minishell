/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_lexer_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:12:17 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/14 14:06:30 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str, char quote_type)
{
	char *result;
	int i;
	int j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != quote_type)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*search_value(t_msh *msh, char *name)
{
	char	*value;
	int		i;
	
	i = 0;
	value = NULL;

	if (!msh || !msh->env || !msh->env->names || !msh->env->values || !name)
		return (NULL);
	while (msh->env->names[i] && msh->env->values[i])
	{
		if (ft_strcmp(msh->env->names[i], name) == 0)
		{
			value = ft_strdup(msh->env->values[i]);
			printf("value = %s\n", value);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	expand_and_remove_quotes(char *str, t_msh *msh)
{
	char	*value;

	value = NULL;
	if (!str || !msh || !msh->env)
		return ;	
	if (find_env_var(msh, str))
	{
		value = search_value(msh, str);
		if (value != NULL)
			return ;
	}
	str = remove_quotes(str, '\"');
	ft_putstr_fd(str, 1);
	free (str);
	//return (str);
}
    // Aquí implementarías la expansión de variables
    // Por ejemplo: $USER -> "username"
    // Esta función debe manejar la expansión de variables
    // cuando se encuentran dentro de comillas dobles
    // return ; // Placeholder

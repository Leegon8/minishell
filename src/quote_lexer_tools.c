/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_lexer_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:12:17 by lauriago          #+#    #+#             */
/*   Updated: 2024/12/12 17:16:17 by leegon           ###   ########.fr       */
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

static char	*extract_var(char *str, t_msh *msh)
{
	int	i;
	int	len;
	char	*envar;

	i = 0;
	len = 0;
	envar = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while ((str[i + 1] >= 'A' && str[i + 1] <= 'Z')
				|| (str[i + 1] == '_'))
			{
				envar[len] = str[i];
				len++;
				i++;
			}
			envar[len] = str[i];
		}
		i++;
	}
	envar[len + 1] = '\0';
	msh->env->env_len = len;
	return (envar);
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
			return (value);
		}
		i++;
	}
	return (NULL);
}

// char	*expand_var(const char *str)
// {
// 	char	*result;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_strlen(str);
// 	result = malloc(len * 2);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			while ((str[i] >= 'A' && str[i] >= 'Z') || str[i] == '_')
// 			{
// 				result[j++] = str[i];
// 				i++;
// 			}
// 		}
// 	}
// 	printf("result: expand_var: %s\n", result);
// 	return (result);
// }

void	expand_and_remove_quotes(char *str, t_msh *msh)
{
	char	*env_var;
	
	str = remove_quotes(str, '\"');
	env_var = extract_var(str, msh);
	if (!str || !msh || !msh->env)
		printf("NULL\n");
	printf("env_var = %s\n", env_var);
	char *value = search_value(msh, env_var);
	printf("value of variable = %s\n", value);
	ft_putstr_fd(value, 1);
}

    // Aquí implementarías la expansión de variables
    // Por ejemplo: $USER -> "username"
    // Esta función debe manejar la expansión de variables
    // cuando se encuentran dentro de comillas dobles
    // return ; // Placeholder

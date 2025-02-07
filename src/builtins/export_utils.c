/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:40:25 by lprieto-          #+#    #+#             */
/*   Updated: 2024/11/05 10:40:44 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_exist(t_msh *msh)
{
	int i;
	char *name;

	i = 0;
	name = get_var_name(msh->tkns->args[1]);
	// printf("primer valor > token:%s - name:%s\n", msh->tkns->args[1] , name);
	while (msh->env->names[i] && (ft_strcmp(msh->env->names[i], name) != 0))
		i++;
	if (i < msh->env_var_count)
	{
		printf("TRUE: %d\n", i);
		return (TRUE);
	}
	printf("FALSE\n");
	return (FALSE);
}

int	env_var_pos(t_msh *msh)
{
	int pos;
	char *name;

	pos = 0;
	name = get_var_name(msh->tkns->args[1]);
	while (msh->env->names[pos] && (ft_strcmp(msh->env->names[pos], name) != 0))
		pos++;
	printf("TRUE: %d\n", pos);
	return (pos);
}

char	*get_var_name(char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_substr(var, 0, i);
	return (name);
}

char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (ft_strdup(""));
	value = ft_strdup(var + i + 1);
	return (value);
}

int	update_env_var_value(t_msh *msh, int pos, char *value)
{
	char	*new_values;

	// new_values = ft_calloc(pos + 2, sizeof(char *));
	// if (!new_values)
	// 	return (FALSE);
	// pos = -1;
	free(msh->env->values[pos]);
	new_values = ft_strdup(value);
	msh->env->values[pos] = new_values;
	printf("maravilla %s\n", msh->env->values[pos]);
	return (TRUE);
}
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
	printf("primer valor > token:%s - name:%s\n", msh->tkns->args[1] , name);
	while (msh->env->names[i] && (ft_strcmp(msh->env->names[i], name) != 0))
	{
		msh->env->names[i] = msh->env->names[i + 1];
		printf("searching %d\n", i);
		i++;
	}
	if (i < msh->env_var_count)
	{
		printf("TRUE\n");
		return (TRUE);
	}
	printf("FALSE\n");
	return (FALSE);
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

// // Busca posicion de la variable, la actualiza y devuelve la posicion del valor actualizado
// int	update_env_var_p(t_msh *msh, char *name, char *value)
// {
// 	int	pos;

// 	pos = find_env_pos(msh, name);
// 	if (pos >= 0)
// 	{
// 		free(msh->env->values[pos]);
// 		msh->env->values[pos] = ft_strdup(value);
// 		return (FALSE);
// 	}
// 	return (add_env_var(msh, name, value));
// }

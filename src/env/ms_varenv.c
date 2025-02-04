/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_varenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:12:48 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/12 12:41:13 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Busca el valor de una variable de entorno */
char	*search_value(t_msh *msh, char *var)
{
	int	i;

	i = 0;
	while (msh->env->names[i] && msh->env->values[i])
	{
		if (ft_strcmp(msh->env->names[i], var) == 0)
			return (msh->env->values[i]);
		i++;
	}
	return (NULL);
}

/* Función para manejar variables de entorno en "cd" */
int	varenv_man(t_msh *msh, char *builting, char *var_name)
{
	char	*value;
	char	*current_pwd;

	if (!var_name || !builting || !msh)
		return (FALSE);
	value = search_value(msh, var_name);
	if (!value)
		return (FALSE);
	if (ft_strcmp(builting, "cd") == 0)
	{
		if (chdir(value) != -1)
		{
			current_pwd = getcwd(NULL, 0);
			msh->env->old_pwd = update_env(msh, "OLDPWD", msh->env->pwd);
			msh->env->pwd = update_env(msh, "PWD", current_pwd);
			free(current_pwd);
			return (TRUE);
		}
	}
	return (FALSE);
}

/*	Actualiza las variables de entorno, buscando el nombre de la variable
	que se le pasa como argumento. Devuelve el nuevo valor actualizado
	*/
char	*update_env(t_msh *msh, char *name, char *value)
{
	char	*new_value;
	int		i;

	i = 0;
	if (!value || !name)
		return (NULL);
	while (msh->env->names[i] && msh->env->values[i])
	{
		if (ft_strcmp(msh->env->names[i], name) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (NULL);
			free(msh->env->values[i]);
			msh->env->values[i] = new_value;
			break ;
		}
		i++;
	}
	return (msh->env->values[i]);
}

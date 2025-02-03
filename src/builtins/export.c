/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_b_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:15:46 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/03 11:44:34 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		if (ft_isalnum(str[i]))
			i++;
		if (str[i] == '=')
			return (TRUE);
	}
	return (FALSE);
}

int	add_env_var(t_msh *msh, char *name, char *value)
{
	int		count;
	char	**new_names;
	char	**new_values;

	count = env_var_count(msh);
	new_names = ft_calloc(count + 2, sizeof(char *));
	new_values = ft_calloc(count + 2, sizeof(char *));
	if (!new_names || !new_values)
		return (FALSE);
	count = -1;
	while (msh->env->names[++count])
	{
		new_names[count] = ft_strdup(msh->env->names[count]);
		new_values[count] = ft_strdup(msh->env->values[count]);
	}
	new_names[count] = ft_strdup(name);
	new_values[count] = ft_strdup(value);
	ft_free_array(msh->env->names);
	ft_free_array(msh->env->values);
	msh->env->names = new_names;
	msh->env->values = new_values;
	msh->env_var_count++;
	return (TRUE);
}

static void	print_export_vars(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->env->names[i])
	{
		ft_fd_printf(1, "declare -x %s", msh->env->names[i]);
		if (msh->env->values[i][0])
			ft_fd_printf(1, "=\"%s\"", msh->env->values[i]);
		ft_fd_printf(1, "\n");
		i++;
	}
}

static void	handle_export_arg(t_msh *msh, char *arg)
{
	char	*name;
	char	*value;

	if (!is_valid_identifier(msh->tkns->args[1]))
	{
		ft_fd_printf(2, "export: `%s': not a valid identifier\n", arg);
		return ;
	}
	name = get_var_name(msh->tkns->args[1]);
	value = get_var_value(msh->tkns->args[1]);
	ft_fd_printf(2, "NOMBRE????: `%s'\n", name);
	ft_fd_printf(2, "VALOR?????: `%s'\n", value);
	if (!add_env_var(msh, name, value))
		ft_fd_printf(2, "export: memory allocation error\n");
	free(name);
	free(value);
}

int	ft_export(t_msh *msh, int tok_num)
{
	if (tok_num == 1)
	{
		print_export_vars(msh);
		return (TRUE);
	}
	if (tok_num != 2)
	{
		ft_fd_printf(2, E_SYNTX);
		return (FALSE);
	}
	else
		handle_export_arg(msh, msh->tkns->args[1]);
	return (TRUE);
}

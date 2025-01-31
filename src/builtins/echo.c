/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:21:27 by lauriago          #+#    #+#             */
/*   Updated: 2025/01/30 18:36:30 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Imprime los argumentos de echo, opción -n para suprimir el \n final */
// Hay que gestionar variable de entorno 
static int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] != '-')
		return (FALSE);
	i++;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_n_flags(t_msh *msh, int *i)
{
	int	n_flag;
	int	curr_i;

	n_flag = FALSE;
	curr_i = 1;
	while (msh->tkns->args[curr_i])
	{
		if (!is_n_flag(msh->tkns->args[curr_i]))
			break ;
		n_flag = TRUE;
		curr_i++;
	}
	*i = curr_i;
	return (n_flag);
}

static int	echo_has_2_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	handle_echo_quotes(t_msh *msh, char k, int i)
{
	if (k == '\'' || k == '\"')
	{
		if (k == '\'')
			handle_single_quotes(msh, i);
		if (k == '\"')
			handle_double_quotes(msh, i);
	}
	else if (k != '\'' || k != '\"')
	{
		if (echo_has_2_expand(msh->tkns->args[i]))
			expand_and_remove_quotes(msh->tkns->args[i], msh);
		else
			ft_putstr_fd(msh->tkns->args[i], 1);
	}
}

void	ft_echo(t_msh *msh, int num_cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	if (num_cmd <= 1)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	n_flag = check_n_flags(msh, &i);
	while (i < num_cmd)
	{
		if (msh->tkns->args[i][0] == '\'')
			handle_single_quotes(msh, i);
		if (msh->tkns->args[i][0] == '\"')
			handle_double_quotes(msh, i);
		else if (!is_quote(msh->tkns->args[i][0]))
		{
			if (echo_has_2_expand(msh->tkns->args[i]))
				expand_and_remove_quotes(msh->tkns->args[i], msh);
			else
				ft_putstr_fd(msh->tkns->args[i], 1);
		}
		if (i + 1 < num_cmd)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n_flag == FALSE)
		printf("\n");
}

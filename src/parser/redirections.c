/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:50:55 by lauriago          #+#    #+#             */
/*   Updated: 2025/02/20 21:51:10 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print error message
static void	print_error_msg(char c)
{
	ft_fd_printf(2, "minishell: syntax error near unexpected token `%c'\n", c);
}

// Función que verifica si hay redirección 
int	has_redirection(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok->args[i])
	{
		if (is_operator(tok->args[i][0]) || is_pipe(tok->args[i][0]))
			return (i);
		i++;
	}
	return (-1);
}

t_redir	check_syntax_redir(char **tkn, int pos)
{
	int		len;
	char	*arg;

	if (!tkn || !tkn[pos] || pos < 0)
		return (NO_REDIR);
	len = ft_strlen(tkn[pos]);
	arg = tkn[pos];
	if (len == 2)
	{
		if (arg[0] == '<' && arg[1] == '<')
			return (REDIR_HERE);
		if (arg[0] == '>' && arg[1] == '>')
			return (REDIR_APPEND);
	}
	if (len == 1)
	{
		if (arg[0] == '<')
			return (REDIR_IN);
		if (arg[0] == '>')
			return (REDIR_OUT);
		if (arg[0] == '|')
			return (PIPE);
	}
	return (REDIR_ERROR);
}

static void	print_redir_info(t_redir redir_type, int redir_pos)
{
	printf("Tipo de redirección: ");
	if (redir_type == NO_REDIR)
		printf("No hay redirección\n");
	else if (redir_type == REDIR_IN)
		printf("de entrada (<)\n");
	else if (redir_type == REDIR_OUT)
		printf("de salida (>)\n");
	else if (redir_type == REDIR_APPEND)
		printf("de salida con append (>>)\n");
	else if (redir_type == REDIR_HERE)
		printf("Heredoc (<<)\n");
	else if (redir_type == PIPE)
		printf("Pipe (|)\n");
	printf("Posición del token: %d\n", redir_pos);
}

// Función generica para verificar sintaxis redirecciones
void	redir_checker(t_msh *msh)
{
	int		redir_pos;
	t_redir	redir_type;

	if (!msh || !msh->tkns || !msh->tkns->args)
		return ;
	redir_pos = has_redirection(msh->tkns);
	if (redir_pos >= 0)
	{
		redir_type = check_syntax_redir(msh->tkns->args, redir_pos);
		if (redir_type == REDIR_ERROR)
		{
			if (msh->tkns->args[redir_pos]
				&& ft_strlen(msh->tkns->args[redir_pos]) > 1)
				print_error_msg(msh->tkns->args[redir_pos][1]);
		}
		print_redir_info(redir_type, redir_pos);
	}
}

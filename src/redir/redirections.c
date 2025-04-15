/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:50:55 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/15 20:20:06 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_redirection(t_msh *msh, t_tok *tok)
{
	int	i;

	i = 0;
	// if (ft_strcmp(tok->args[i], "|") == 0)
	// {
	// 	print_error_msg(msh, '|');
	// 	return (-2);
	// }
	(void)msh;
	while (tok->args[i])
	{
		if (is_operator(tok->args[i][0]) || is_pipe(tok->args[i][0]))
		{
			// if (tok->args[i + 1])
			// {
			// 	if (is_operator(tok->args[i + 1][0])
			// 		|| is_pipe(tok->args[i + 1][0]))
			// 		return (-1);
			// }
			return (i);
		}
		i++;
	}
	return (-1);
}

t_redir	check_syntax_redir(t_msh *msh, char **tkn, int pos)
{
	int		len;

	if (!tkn || pos < 0 || !tkn[pos])
		return (NO_REDIR);
	len = ft_strlen(tkn[pos]);
	if (len == 2 || len == 1)
	{
		if (ft_strcmp(tkn[pos], ">") == 0)
			return (REDIR_OUT);
		if (ft_strcmp(tkn[pos], ">>") == 0)
			return (REDIR_APPEND);
		if (ft_strcmp(tkn[pos], "<") == 0)
			return (REDIR_IN);
		if (ft_strcmp(tkn[pos], "<<") == 0)
			return (REDIR_HERE);
		if (ft_strcmp(tkn[pos], "|") == 0)
			return (PIPE);
	}
	if (len > 2)
	{
		print_error_msg(msh, tkn[pos][1]);
		msh->last_exit_code = 2;
		return (REDIR_ERROR);
	}
	return (REDIR_ERROR);
}

void	handle_redir_out(t_msh *msh, t_redir type)
{
	int	file_pos;

	file_pos = msh->tkns->redir_pos + 1;
	msh->mpip->outfile = msh->tkns->args[file_pos];
	if (msh->mpip->outfile == NULL)
	{
		ft_fd_printf(2, E_NW);
		msh->last_exit_code = 2;
		return ;
	}
	if (is_builtin(msh->tkns->cmd))
	{
		manage_builting_redir(msh, type);
		return ;
	}
	exec_redir(msh, msh->tkns->cmd, type);
	restore_redirections(msh);
}

int	redir_checker(t_msh *msh)
{
	int		redir_pos;
	t_redir	redir_type;
	int		redir_count;

	redir_count = count_redir(msh);
	if (!msh || !msh->tkns || !msh->tkns->args)
		return (FALSE);
	if (type_verif(msh) == FALSE)
	{
		printf("efectivamente entra a FALSE type verif\n");
		return (FALSE);
	}
	else
	{
		redir_pos = has_redirection(msh, msh->tkns);
		msh->tkns->redir_pos = redir_pos;
		redir_type = check_syntax_redir(msh, msh->tkns->args, redir_pos);
		msh->tkns->first_redir_type = redir_type;
		if (redir_type == NO_REDIR || redir_type == REDIR_ERROR)
			return (FALSE);
		if (redir_count == 1)
			return (handle_one_redir(msh, redir_pos, redir_type));
		if (redir_count > 1)
		return (handle_multip_redir(msh, redir_count, redir_pos, redir_type));
	}
	
	return (FALSE);
}

// int	check_pipe_syntax(t_msh *msh)
// {
// 	int	i;

// 	if (!msh || !msh->tkns || !msh->tkns->args)
// 		return (TRUE);
// 	i = 0;
// 	while (msh->tkns->args[i])
// 	{
// 		if (ft_strcmp(msh->tkns->args[i], "|") == 0)
// 		{
// 			if (i == 0 || !msh->tkns->args[i + 1])
// 			{
// 				print_error_msg(msh, '|');
// 				return (FALSE);
// 			}
// 		}
// 		i++;
// 	}
// 	return (TRUE);
// }

int	check_double_pipe(t_msh *msh)
{
	int	i;

	if (!msh || !msh->tkns || !msh->tkns->args)
		return (TRUE);
	i = 0;
	while (msh->tkns->args[i])
	{
		if (ft_strcmp(msh->tkns->args[i], "|") == 0
			&& msh->tkns->args[i + 1]
			&& ft_strcmp(msh->tkns->args[i + 1], "|") == 0)
		{
			print_error_msg(msh, '|');
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_redir_edges(t_msh *msh)
{
	int	i;

	if (!msh || !msh->tkns || !msh->tkns->args)
		return (TRUE);
	i = 0;
	while (msh->tkns->args[i])
	{
		if (is_redir(msh->tkns->args[i]))
		{
			if (!msh->tkns->args[i + 1] || is_redir(msh->tkns->args[i + 1]))
			{
				print_error_msg(msh, '>');
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

int	check_unclosed_quotes(char *input)
{
	int i;
	int single;
	int dbl;

	if (!input)
		return (TRUE);
	i = 0;
	single = 0;
	dbl = 0;
	while (input[i])
	{
		if (input[i] == '\'' && dbl == 0)
			single = !single;
		else if (input[i] == '\"' && single == 0)
			dbl = !dbl;
		i++;
	}
	if (single || dbl)
	{
		printf("Error: Comillas sin cerrar.\n");
		return (FALSE);
	}
	return (TRUE);
}

int	basic_syntax_checker(char *input, t_msh *msh)
{
	if (check_unclosed_quotes(input) == FALSE)
		return (FALSE);
	if (check_redir_edges(msh) == FALSE)
		return (FALSE);
	if (check_double_pipe(msh) == FALSE)
		return (FALSE);
	if (check_redir_edges(msh) == FALSE)
		return (FALSE);
	/* Puedes seguir añadiendo llamadas: check_otros(...) */
	return (TRUE);
}

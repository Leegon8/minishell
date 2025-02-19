/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:45:27 by lprieto-          #+#    #+#             */
/*   Updated: 2025/02/19 02:45:01 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Comprueba cada token y su siguiente para operador (incompleta) */
// --> NO SE ESTA USANDO!!
/*int	lexer(char **tokens, t_msh *msh)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (i == 0 || tokens[i + 1] == NULL)
			{
				perror("syntax error with | operator\n");
				return (-1);
			}
		}
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (tokens[i + 1] == NULL)
			{
				perror("syntax error: missing delimiter for heredoc\n");
				return (-1);
			}
			msh->tkns->is_heredoc = 1;
			msh->tkns->heredoc_delim = ft_strdup(tokens[i + 1]);
			i++;
		}
		i++;
	}
	return (TRUE);
}*/

static int	has_pipe(char *token)
{
	return (token && ft_strcmp(token, "|") == 0);
}

static int	validate_pipe_syntax(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok->args[i])
	{
		if (has_pipe(tok->args[i]))
		{
			if (i == 0 || !tok->args[i + 1])
			{
				ft_fd_printf(2, E_PIP_SYNTX);
				return (TRUE);
			}
		}
		i++;
	}
	return (1);
}

static void	init_command_struct(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * MAX_ARGS);
	if (!cmd->args)
		return ;
	cmd->arg_count = 0;
	cmd->args[0] = NULL;
}

static int	split_commands(t_tok *tok, t_cmd *cmds)
{
	int	i;
	int	cmd_idx;
	int	arg_idx;

	i = 0;
	cmd_idx = 0;
	arg_idx = 0;
	init_command_struct(&cmds[cmd_idx]);
	while (tok->args[i])
	{
		if (has_pipe(tok->args[i]))
		{
			cmds[cmd_idx].args[arg_idx] = NULL;
			cmd_idx++;
			arg_idx = 0;
			init_command_struct(&cmds[cmd_idx]);
		}
		else
		{
			cmds[cmd_idx].args[arg_idx] = ft_strdup(tok->args[i]);
			arg_idx++;
		}
		i++;
	}
	return (cmd_idx + 1);
}

int	parse_and_validate_commands(t_tok *tok, t_cmd **commands)
{
	int		cmd_count;
	t_cmd	*cmds;
	int		i;

	if (!validate_pipe_syntax(tok))
		return (TRUE);
	cmd_count = 1;
	i = 0;
	while (tok->args[i])
	{
		if (has_pipe(tok->args[i]))
			cmd_count++;
		i++;
	}
	cmds = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (!cmds)
		return (TRUE);
	if (split_commands(tok, cmds) != cmd_count)
	{
		free(cmds);
		return (TRUE);
	}
	*commands = cmds;
	return (cmd_count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_lexer_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:00:22 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/14 14:04:36 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quotes(t_quote *quote)
{
	quote = malloc(sizeof(t_quote));
	if (!quote)
		return;
	quote->single_count = 0;
	quote->double_count = 0;
	quote->active_quote = NO_QUOTE;
	quote->is_closed = FALSE;
}

static void	quote_status(t_msh *msh, char c)
{
	if (c == '\'')
		msh->quote->single_count++;
	else if (c == '\"')
		msh->quote->double_count++;
	if (c == '\'' && msh->quote->active_quote != DOUBLE_QUOTE)
	{
		if (msh->quote->active_quote == NO_QUOTE)
			msh->quote->active_quote = SINGLE_QUOTE;
		else if (msh->quote->active_quote == SINGLE_QUOTE)
			msh->quote->active_quote = NO_QUOTE;
	}
	else if (c == '\"' && msh->quote->active_quote != SINGLE_QUOTE)
	{
		if (msh->quote->active_quote == NO_QUOTE)
			msh->quote->active_quote = DOUBLE_QUOTE;
		else if (msh->quote->active_quote == DOUBLE_QUOTE)
			msh->quote->active_quote = NO_QUOTE;
	}
}

int	analyze_quotes(t_msh *msh, char *arg)
{
	int	i;

	i = 0;
	init_quotes(msh->quote);
	if (!arg || !msh || !msh->quote)
		return(FALSE);
	while (arg[i])
	{
		quote_status(msh, arg[i]);
		if (msh->quote->single_count == 2 || msh->quote->double_count == 2)
				msh->quote->is_closed = TRUE;
		i++;
	}
	if (msh->quote->double_count < 2 || msh->quote->double_count < 2)
		msh->quote->is_closed = FALSE;
	return (msh->quote->is_closed);
}

void	handle_quotes(t_msh *msh, t_quote *q, int i)
{
	char	*str;

	if (!q || !msh || !msh->tkns || !msh->tkns->args[i])
		return;
	if (analyze_quotes(msh, msh->tkns->args[i]))
	{
		printf("sigle_count = %d\ndouble_count = %d\n", q->single_count, q->double_count);
		if (q->single_count == 2)
		{
			str = remove_quotes(msh->tkns->args[i], '\'');
			ft_putstr_fd(str, 1);
			free (str);
		}
		else if (q->double_count == 2)
			expand_and_remove_quotes(msh->tkns->args[i], msh);
		else
			ft_putstr_fd(msh->tkns->args[i], 1);
	}
	q->double_count = 0;
	q->single_count = 0;
}
/* Comprueba caso de comillas simples / dobles y si estan bien cerradas o no */
// int	quote_lexer(char *arg)
// {
// 	int	quote;
// 	int	i;
// 	// int	len;

// 	quote = 3;
// 	i = 0;
// 	len = ft_strlen(arg);
// 	if ((ft_strcmp(msh->tkns->cmd, "\'") != 0)
// 		|| (ft_strcmp(msh->tkns->cmd, "\"") != 0))
// 		return (-1);
// 	while (arg[i])
// 	{
// 		if (arg[i] == '\'' || arg[i] == '\"')
// 			quote -= 1;
// 		i++;
// 	}
// 	printf("num quotes = %d\n", quote);
// 	return (quote);
// }
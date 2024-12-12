/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_lexer_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leegon <leegon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:00:22 by lauriago          #+#    #+#             */
/*   Updated: 2024/11/22 14:54:10 by leegon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote	*init_quotes(void)
{
	t_quote	*quote;

	quote = malloc(sizeof(t_quote));
	if (!quote)
		return (NULL);
	quote->single_count = 0;
	quote->double_count = 0;
	quote->active_quote = NO_QUOTE;
	quote->is_closed = FALSE;
	return (quote);
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
	if (!arg || !msh || !msh->quote)
		return(FALSE);
	msh->quote->single_count = 0;
	msh->quote->double_count = 0;
	msh->quote->is_closed = FALSE;
	msh->quote->active_quote = NO_QUOTE;

	while (arg[i] != '\0')
	{
		quote_status(msh, arg[i]);
		if (msh->quote->single_count == 2 || msh->quote->double_count == 2)
				msh->quote->is_closed = TRUE;
		i++;
	}
	return (msh->quote->is_closed);
}

void	handle_quotes(t_msh *msh, t_quote *q, int i)
{
	char	*str;
	int		quote_status;

	msh->quote = init_quotes();
	q = msh->quote;
	if (!q || !msh || !msh->tkns || !msh->tkns->args[i])
		return;
	quote_status = analyze_quotes(msh, msh->tkns->args[i]);
	printf("sigle_count = %d\ndouble_count = %d\n", msh->quote->single_count, msh->quote->double_count);
	if (quote_status == TRUE)
	{
		if (q->single_count == 2)
		{
			str = remove_quotes(msh->tkns->args[i], '\'');
			ft_putstr_fd(str, 1);
			free(str);
		}
		else if (q->double_count == 2)
			expand_and_remove_quotes(msh->tkns->args[i], msh);
		else
			ft_putstr_fd(msh->tkns->args[i], 1);
	}
}

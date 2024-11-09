/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:35:57 by lprieto-          #+#    #+#             */
/*   Updated: 2024/11/09 23:03:10 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /* corta el str de entrada con un separador (CON mallocs) trabajando en ella */
// char	*ft_strtok(char *str, const char *separator)
// {
// 	static char	*ptr = NULL;
// 	char		*token;
// 	size_t		token_len;
// 	char		*res;

// 	if (str != NULL)
// 		ptr = str;
// 	while (*ptr != '\0' && ft_strchr(separator, *ptr) != NULL)
// 		ptr++;
// 	if (*ptr == '\0')
// 		return (NULL);
// 	token = ptr;
// 	while (*ptr != '\0' && ft_strchr(separator, *ptr) == NULL)
// 		ptr++;
// 	token_len = ptr - token;
// 	if (*ptr != '\0')
// 	{
// 		*ptr = '\0';
// 		ptr++;
// 	}
// 	res = malloc(token_len + 1);
// 	if (!res)
// 		return (NULL);
// 	ft_strncpy(res, token, token_len);
// 	res[token_len] = '\0';
// 	return (res);
// }

// /* Tokeniza el input y lo guarda en memoria de la estructura tkns de msh */
// int	tokenize_input(char *input, t_msh *msh)
// {
// 	char	*token;
// 	int		i;

// 	msh->tkns = malloc(sizeof(t_tok) * ft_strlen(input) + 10);
// 	if (!msh->tkns)
// 		return (-1);
// 	i = 0;
// 	token = ft_strtok(input, " \t\n");
// 	while (token != NULL)
// 	{
// 		msh->tkns[i].cmd = token;
// 		if (!msh->tkns[i].cmd)
// 			return (-1);
// 		msh->tkns[i].args = NULL;
// 		msh->tkns[i].is_heredoc = 0;
// 		msh->tkns[i].heredoc_delim = NULL;
// 		msh->tkns[i].t_len = ft_strlen(token);
// 		i++;
// 		token = ft_strtok(NULL, " \t\n");
// 	}
// 	msh->tkns[i].cmd = NULL;
// 	return (0);
// }



token_type_t	type_token_def(t_tok *tok, char c)
{
	if (is_quote(c))
		tok->type = T_QUOTE;
	if (is_operator(c))
		tok->type = T_OPERATOR;
	if (is_whitespace(c))
		tok->type = T_WHITESPACE;
	else if (!is_operator(c) && !is_quote(c) && !is_whitespace(c))
		tok->type = T_WORD;
	return (tok->type);
}

int size_token(char *input, t_tok *tok)
{
    int i;
	
	(void)tok;
    i = 0;
    while (input[i] && !is_whitespace(input[i]))
    {
        if (is_operator(input[i]))
        {
            if (i == 0)
                return (1);
            break ;
        }
        if (is_quote(input[i]))
        {
            char quote = input[i];
            i++;
            while (input[i] && input[i] != quote)
                i++;
            if (input[i])
                i++;
            continue ;
        }
        i++;
    }
    return (i);
}

char    *create_token(char *input, int len, t_tok *tok)
{
    char    *new_token;
    int     i;

    new_token = malloc(sizeof(char) * (len + 1));
    if (!new_token)
        return (NULL);
    i = 0;
    while (i < len)
    {
        new_token[i] = input[i];
        i++;
    }
    new_token[i] = '\0';
    tok->cmd = new_token;
    return (new_token);
}


void    ft_token(char *input, t_tok *tok)
{
    int     i;
    int     arg_index;

    tok->args = malloc(MAX_ARGS * sizeof(char*));
    if (!tok->args)
        return;
    i = 0;
    arg_index = 0;
    while (input[i])
    {
        while (input[i] && is_whitespace(input[i]))
            i++;
        if (!input[i])
            break;
        tok->len = size_token(&input[i], tok);
        if (tok->len > 0)
        {
            tok->args[arg_index] = create_token(&input[i], tok->len, tok);
            if (!tok->args[arg_index])
                return;
            arg_index++;
            i += tok->len;
        }
        else
            i++;
    }
    tok->args[arg_index] = NULL;
	// for (int j = 0; j < arg_index; j++) {
    //     printf("args[%d] --> %s\n", j, tok->args[j]);
    // }
}

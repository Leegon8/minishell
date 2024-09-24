/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:35:57 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/24 19:22:14 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* corta el str de entrada con un separador (CON mallocs) trabajando en ella */
char	*ft_strtok(char *str, const char *separator)
{
	static char	*ptr = NULL;
	char		*token;
	size_t		token_len;
	char		*res;

	if (str != NULL)
		ptr = str;	
	while (*ptr != '\0' && ft_strchr(separator, *ptr) != NULL)
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	token = ptr;
	while (*ptr != '\0' && ft_strchr(separator, *ptr) == NULL)
		ptr++;
	token_len = ptr - token;
	if (*ptr != '\0')
	{
		*ptr = '\0';
		ptr++;
	}
	res = malloc(token_len + 1);
	if (!res)
		return (NULL);	
	ft_strncpy(res, token, token_len);
	res[token_len] = '\0';
	return (res);
}

// /* corta el str de entrada con un separador (no mallocs) trabajando en ella */

// char	*ft_strtok(char *str, const char *separator)
// {
// 	static char	*ptr = NULL;
// 	char		*token;

// 	if (str != NULL)
// 		ptr = str;
// 	while (*ptr != '\0' && ft_strchr(separator, *ptr) != NULL)
// 		ptr++;
// 	if (*ptr == '\0')
// 		return (NULL);
// 	token = ptr;
// 	while (*ptr != '\0' && ft_strchr(separator, *ptr) == NULL)
// 		ptr++;
// 	if (*ptr != '\0')
// 	{
// 		*ptr = '\0';
// 		ptr++;
// 	}

// 	return (token);
// }

/* Tokeniza el input y lo guarda en memoria de la estructura tkns contenida en msh */
int tokenize_input(char *input, t_msh *msh)
{
    char    *token;
    int     i;
    
    msh->tkns = malloc(sizeof(t_tok) * (ft_strlen(input) + 1)); // reserva espacio para los tokens
    if (!msh->tkns)
        return (-1);
    i = 0;
    token = ft_strtok(input, " \t\n");
    while (token != NULL)
    {
        msh->tkns[i].cmd = token;
        if (!msh->tkns[i].cmd)
            return (-1);
        msh->tkns[i].args = NULL;
        msh->tkns[i].is_heredoc = 0;
        msh->tkns[i].heredoc_delim = NULL;
        msh->tkns[i].t_len = ft_strlen(token);
        i++;
        token = ft_strtok(NULL, " \t\n");
    }
    msh->tkns[i].cmd = NULL; // Marcar el final de los tokens con NULL
    return (0);
}
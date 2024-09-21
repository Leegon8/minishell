/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:35:57 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/21 18:31:07 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* corta el str de entrada con un separador (no modificar) estoy trabajando en ella */
char	*ft_strtok(char *str, const char *separator)
{
	static char	*ptr;
	char		*start;

	if (str != NULL)
		ptr = str;	
	if(ptr == NULL)
		return (NULL);
	while (*ptr != '\0' && ft_strchr(separator, *ptr) != NULL)
		ptr++;
	if (*ptr == '\0')
		return (NULL);
	start = ptr;
	while (*ptr != '\0' && ft_strchr(separator, *ptr) == NULL)
		ptr++;
	if (*ptr != '\0')
	{
		*ptr = '\0';
		ptr++;
	}
	return (start);
}

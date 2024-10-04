/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:09:34 by lprieto-          #+#    #+#             */
/*   Updated: 2024/10/04 10:14:50 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*dest;
	int		l;

	l = 0;
	while (str[l] != '\0')
		l++;
	dest = (char *)malloc(l + 1);
	if (dest == NULL)
		return (0);
	ft_memcpy(dest, str, l);
	dest[l] = '\0';
	return (dest);
}

/*int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
//	char *res_ft_strdup = ft_strdup(argv[1]);
	char *resultado_strdup = strdup(argv[1]);
//	printf("ft_strdup:%s \n", res_ft_strdup);
	printf("strdup:%s", resultado_strdup);
	return(0);
}*/
//memcopyloop
	// while (str[i])
	// {
	// 	dest[i] = str[i];
	// 	++i;
	// }
/* ************************************************************************** *
 *								FT_STRDUP
 *
 * DESCRIPCION:	se utiliza para duplicar un string en una posicion de memoria 
 * reservada de antemano. Eimportante tener en cuenta la asignación y 
 * liberación adecuada de memoria al utilizar esta función para evitar 
 * fugas de memoria
 * 
 * INPUT:	char *str
 * 
 * MAKE:	recorre el array de origen para saber la longitud, despues reserva
 * una cantidad de memoria igual a la longitud + 1 para el '\0' final y aplica
 * lo llena de los mismos caractetres que el string original.
 *  
 * OUTPUT:	devuelve un string identido al original pero en una posicion de 
 * memoria diferente
 * 
 * ***************************************************************************/

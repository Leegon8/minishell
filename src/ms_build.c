/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 21:21:27 by lauriago          #+#    #+#             */
/*   Updated: 2024/09/13 22:54:37 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Calculo num de argumentos para gestionar las 2 posibilidades de echo
int	num_arg(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	*ft_echo(char **av)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	if (num_arg(av) > 1)
	{
		while (av[i] && ft_strcmp(av[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (av[i])
		{
			ft_putstr(av[i]);
			if (av[1 + i])
				printf(" ");
			i++;
		}
	}
	if (n_option == 0)
		printf("\n");
	return(NULL);
}

/*int	main(int ac, char **av)
{
	if (ac > 1)
	{
		if (ft_strcmp(av[1], "echo") == 0)
			ft_echo(av);
	}
	return (0);
}*/

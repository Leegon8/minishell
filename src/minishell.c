/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:25:04 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/13 16:48:49 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envs)
{
	char	*input;
	t_hist	hist;
	t_env	env;
	t_mshll	msh;
	char	*pwd;

	if (argc != 1 || argv[1])
	{
		ft_fd_printf(2, "%s", E_EXECARG);
		exit (0);
	}
	init_structs(&env, &hist, &msh);
	pwd = parse_pwd(envs);
	printf("pwd: %s\n", pwd);
	while (msh.end_sig == 0)
	{
		rl_attempted_completion_function = command_completion;
		input = readline("\033[1;96m 👽 Space 🛸 shell $\e[0m> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		if (ft_strncmp("clearh", input, 6) == 0) /* borra el historial */
			rl_clear_history();
		if (ft_strncmp("clear", input, 5) == 0) /* clear :D */
			printf("%s", CLEAR);
	//	if (ft_strncmp("ls", input, 2))     /* execve rompe el bucle */
	//		execve("/bin/ls", argv, NULL);
		free(input);
	}
	return (0);
}

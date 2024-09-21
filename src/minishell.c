/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:25:04 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/21 12:03:25 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envs)
{
	char	*input;
	t_env	*env;
	t_mshll	msh;

	if (argc != 1 || argv[1])
	{
		ft_fd_printf(2, "%s", E_EXECARG);
		exit (0);
	}
	env = malloc(sizeof(t_env));
	if (!env)
		return (-1);
	init_structs(env, &msh);
	env->pwd = malloc(PATH_MAX);
	if (!env->pwd)
		return (-1);
	printf("pwd 1: %s\n", env->pwd);
	printf("Numero de variables en env: %d\n", env_var_count(envs));
	getcwd(env->pwd,PATH_MAX);
	printf("pwd getcwd: %s\n", env->pwd);
	// env->pwd = getenv("PWD");
	// printf("pwd getenv: %s\n", env->pwd);
	// {
	// 	perror("Error: getcwd failed");
	// 	return (-1);
	// }
	//init_env(env, envs);

	while (msh.end_sig == 0)
	{
		rl_attempted_completion_function = command_completion;
		input = readline("\033[1;96m👽 Space 🛸 shell $\e[0m> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		if (ft_strcmp("pwd", input) == 0) /* pwd */
			printf("%s\n", env->pwd);
		if (ft_strncmp("clearh", input, 6) == 0) /* borra el historial */
			clear_history();
		if (ft_strncmp("clear", input, 5) == 0) /* clear :D */
			printf("%s", CLEAR);
		if (ft_strncmp("echo", input, 4) == 0)
			ft_echo(argv);
		if (ft_strncmp("exit", input, 4) == 0) /* para hacer exit sin ctrl+C */
			msh.end_sig = 1;
	//	if (ft_strncmp("ls", input, 2))     /* execve rompe el bucle, hace exit */
	//		execve("/bin/ls", argv, NULL);
		free(input);
	}
	return (0);
}

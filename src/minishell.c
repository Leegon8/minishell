/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:25:04 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/23 11:13:13 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Bucle principal del shell que gestiona la entrada del usuario y ejecuta comandos */
void	shell_loop(t_env *env, t_mshll *msh)
{
	char	*input;
	char	*token;

	while (msh->end_sig == 0)
	{
		rl_attempted_completion_function = cmd_comp;
		input = readline("\033[1;96m👽 Space 🛸 shell $\e[0m> ");
		if (input == NULL)
			break ;
		if (*input)
			add_history(input);
		
		token = ft_strtok(input, " \t\n");
		while (token != NULL)
		{
			if (ft_strcmp("pwd", token) == 0) /* pwd */
				printf("%s\n", env->pwd);
			if (ft_strcmp("clearh", token) == 0) /* borra el historial */
				clear_history();
			if (ft_strcmp("clear", token) == 0) /* clear :D */
				printf("%s", CLEAR);
			// if (ft_strcmp("echo", token) == 0) /* Esto no va a funcionar por el tokenizador */
			// 	ft_echo(argv);
			if (ft_strcmp("exit", token) == 0) /* para hacer exit sin ctrl+C */
				msh->end_sig = 1;
			if (ft_strcmp("ola", token) == 0) /* para hacer exit sin ctrl+C */
				printf("prueba: %s\n", msh->env->pwd);
			free(token);
			token = ft_strtok(NULL, " \t\n");
		}
	//	if (ft_strncmp("ls", input, 2))     /* execve rompe el bucle, hace exit */
	//		execve("/bin/ls", argv, NULL);
	free(input);
	}
}

/* Función principal que inicializa el entorno y estructuras, y lanza el bucle del shell */
int	main(int argc, char **argv, char **envs)
{
	t_env	*env;
	t_mshll	msh;
	t_pip	*mpip;
	t_tok	*tok;

	if (argc != 1 || argv[1])
		exit (ft_fd_printf(2, "%s", E_EXECARG) * 0);
	env = malloc(sizeof(t_env));
	if (!env)
		return (-1);
	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (-1);
	mpip = malloc(sizeof(t_pip));
	if (!mpip)
		return (-1);
	init_structs(env, &msh, mpip);
	env->pwd = malloc(PATH_MAX);
	if (!env->pwd)
		return (-1);
	init_env(env, envs);
	shell_loop(env, &msh); /* Este es el loop principal, que esta en la funcion shell_loop */
	free_structs(env, tok, mpip); /* Libera las estructuras que le pasemos */
	return (0);
}

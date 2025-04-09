/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 09:25:04 by lprieto-          #+#    #+#             */
/*   Updated: 2025/04/08 10:12:38 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Bucle principal gestiona la entrada del usuario y ejecuta comandos */
void	shell_loop(t_msh *msh)
{
	char	*input;

	while (msh->end_sig == 0)
	{
		input = readline("\033[0;96m🛸 Space_shell 👽:\e[0m");
		if (!input)
			msh->end_sig = 1;
		else
		{
			add_history(input);
			if (ft_strlen(input) > 0)
				check_tokens(input, msh);
			free(input);
		}
	}
}

static char	**create_minimal_env(void)
{
	char	**new_env;
	char	*cwd;

	new_env = malloc(sizeof(char *) * 5);
	if (!new_env)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(new_env);
		return (NULL);
	}
	new_env[0] = ft_strjoin("PWD=", cwd);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("PATH=/usr/bin:/bin");
	new_env[3] = ft_strdup("HOME=/");
	new_env[4] = NULL;
	free(cwd);
	return (new_env);
}

int	main(int argc, char **argv, char **envs)
{
	t_env	*env;
	t_msh	msh;
	t_exe	*mpip;
	t_tok	*tok;

	tok = NULL;
	if (argc != 1 || argv[1])
		exit (ft_fd_printf(2, "%s", E_EXECARG) * 0);
	ft_memset(&msh, 0, sizeof(t_msh));
	msh.envs = envs;
	if (!envs || !msh.envs[0])
		msh.envs = create_minimal_env();
	if (init_structs(&env, &msh, &mpip, &tok) != TRUE)
	{
		if (env)
			free_env(env);
		return (ft_fd_printf(2, "%s", E_MEMASF));
	}
	msh.env_var_count = env_var_count(&msh);
	if (env_init(env, &msh) != TRUE)
	{
		free_env(env);
		return (ft_fd_printf(2, "%s", E_MEMASF));
	}
	init_signals();
	shell_loop(&msh);
	free_structs(env, tok, mpip);
	return (msh.last_exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:25:46 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/19 18:41:15 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cuenta las variables que hay en env (No modificar) trabajando en ella */
int env_var_count(char **envs)
{
    int i;
    
    i = 0;
     if (!envs || envs == NULL)
        printf("NO HAY ENV\n");
    else
    {    
        while (envs && envs[i])
            i++;
    }
    return (i);
}

int set_env_vars(t_env env, char **envs)
{
    if (!envs || envs == NULL || env_var_count(envs) != 36)
    {
        getcwd(env.pwd, sizeof(env));
        printf("NO HAY ENV\n");
        return (0);
    }
    else
        getenv(*envs);
    return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:25:46 by lprieto-          #+#    #+#             */
/*   Updated: 2024/09/19 21:39:34 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cuenta las variables que hay en env (No modificar) trabajando en ella */
int env_var_count(char **envs)
{
    int i;
    
    i = 0;
     if (!envs || envs == NULL)
        printf("NO HAY ENV 1\n");
    else
    {    
        while (envs && envs[i])
            i++;
    }
    return (i);
}

char    *ft_strndup(const char *s, size_t len)
{
    char    *dup;
    size_t  slen;
    
    slen = ft_strlen(s);
    if (len > slen)
        len = slen;
    dup = malloc(len + 1);
    if (dup)
        ft_strlcpy(dup, s, len + 1);
    return (dup);
}


int init_env(t_env *env, char **envs)
{
    int     i;
    char    *eq_sep;
    
    i = 0;
    env->pwd = getenv("PWD");
    env->home = getenv("HOME");
    while (envs[i])
    {
        eq_sep = ft_strchr(envs[i], '=');
        if (eq_sep)
        {
            env->name = ft_strndup(envs[i], (eq_sep - envs[i]));
            env->value = ft_strdup(eq_sep + 1);
            printf("nombre: %s, valor: %s\n", env->name, env->value);
        }
        i++;
    }
    return (0);
}


int set_env_vars(t_env env, char **envs)
{
    int     i;
    char    *eq_sep = NULL;
    int     vlen;
    
    i = 0;
    vlen = 0;
    if (!envs || envs == NULL)
    {
        getcwd(env.pwd, sizeof(env));
        printf("NO HAY ENV 2\n");
        return (0);
    }
    else
    {
        while (envs[i])
        {
            if (eq_sep)
            {
                vlen = eq_sep - envs[i];
                env.name = ft_strndup(envs[i], vlen);
                env.value = ft_strdup(eq_sep + 1);
            }
            i++;
        }
    }
    return (1);
}

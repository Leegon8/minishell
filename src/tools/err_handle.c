/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprieto- <lprieto-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:36 by lprieto-          #+#    #+#             */
/*   Updated: 2025/03/27 10:02:09 by lprieto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "status.h"

void	handle_cd_error(t_msh *msh, int error_type)
{
	if (error_type == EACCES)
		ft_fd_printf(2, "cd: %s: Permission denied\n", msh->tkns->args[1]);
	else if (error_type == ENOTDIR)
		ft_fd_printf(2, "cd: %s: Not a directory\n", msh->tkns->args[1]);
	else
		ft_fd_printf(2, "cd: %s: No such file or directory\n", msh->tkns->args[1]);
	set_exit_status(1);
}

int	ft_err(t_msh *msh, int err_code)
{
	int	final_err;

	final_err = err_code % 256;
	if (err_code < 0)
		final_err += 256;
	msh->last_exit_code = final_err;
	return (final_err);
}

void	handle_exit_status(t_msh *msh)
{
	char	*code;

	(void)msh;
	code = ft_itoa(get_exit_status());
	ft_putstr(code);
	free(code);
}

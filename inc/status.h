/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauriago <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:36:02 by lauriago          #+#    #+#             */
/*   Updated: 2025/04/01 12:37:02 by lauriago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
#define STATUS_H

extern int	g_exit_status;

void	set_exit_status(int status);
int	get_exit_status(void);

#endif


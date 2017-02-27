/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __shell_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 18:52:51 by afeuerst          #+#    #+#             */
/*   Updated: 2017/02/27 17:46:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_info					g_info;

void					ft_segfault(int signum)
{
	(void)signum;
	wwrite(1, "\e[32msegfault chouette !\n\e[37m")
}

void					ft_init(void)
{
	char				buffer[8096];

	ft_memset_ll(buffer, 0, 1012);
	if (getcwd(buffer, 1012))
		g_info.o_path = ft_copy(buffer);
	else
		g_info.o_path = NULL;
	g_info.restricted = 0;
	ft_init_signal();
	ft_save_env();
}

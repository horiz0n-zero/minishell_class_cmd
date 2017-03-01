/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __shell_deinit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:44:14 by afeuerst          #+#    #+#             */
/*   Updated: 2017/03/01 13:57:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h>
static void		ft_free_board(void)
{
	t_board		*board;
	t_board		*tmp;

	board = (t_board*)ft_typeofpath(NULL, NULL, 1);
	if (board == NULL)
		return ;
	while (board)
	{
		while (*board->content)
			free(*board->content++);
		tmp = board;
		board = board->next;
		free(tmp);
	}
}

void			ft_shell_deinit(const t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->last == NULL)
			break ;
		else
			cmd = cmd->last;
	}
	while (cmd)
	{
		(*(struct s_class**)cmd)->ctor(cmd);
		cmd = cmd->next;
	}
	ft_free_board();
}

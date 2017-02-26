/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 13:57:22 by afeuerst          #+#    #+#             */
/*   Updated: 2017/02/26 15:44:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int32_t				ft_typeofpath(const char *bin_path, char **dst)
{
	static t_board	*board = NULL;
	static t_board	*save = NULL;
	uint16_t		index;

	index = 0;
	if (board == NULL)
		(board = ft_get_bin_board()) && (save = board);
	while (board)
	{
		while (board->content[index])
		{
			if (!ft_strncmp(bin_path, board->content[index], ft_strlen(board->content[index])))
			{
				*dst = ft_stc_strjoin(ft_stc_pluslash(board->path), board->content[index]);
				board = save;
				return (1);
			}
			else
				index++;
		}
		board = board->next;
		index = 0;
	}
	board = save;
	return (-1);
}

static void			ft_launch_command(const t_cmd * const cmd, const char *bin_path)
{
	pid_t			pid;
	extern char		**environ;

	pid = fork();
	if (!pid)
	{
		execve(bin_path, cmd->args, environ);
		exit(1);
	}
	else
		wait(NULL);
	// todo : passer a wait pid ** pour utiliser les taches de fonds.
}

void				ft_start_command(const t_cmd * const cmd)
{
	int32_t			typeof_path;
	char			*bin_path;

	bin_path = NULL;
	typeof_path = ft_typeofpath(*cmd->args, &bin_path);
	if (typeof_path < 0)
	{
		write(1, "\e[31mCommande not found : ", sizeof("\e[31mCommande not found : "));
		write(1, *cmd->args, ft_strlen(*cmd->args));
		write(1, "\e[37m\n", sizeof("\e[37m\n"));
	}
	else if (!typeof_path)
	{
		// builtins maison :-)
	}
	else
		ft_launch_command(cmd, bin_path);
}
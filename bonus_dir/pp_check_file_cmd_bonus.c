/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_check_file_cmd_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:38:36 by odessein          #+#    #+#             */
/*   Updated: 2022/11/29 10:50:32 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static t_bool	pp_append_or_truncate(t_info *info, char *file)
{
	if (!info->here_doc)
	{
		info->fd[1] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0600);
		if (info->fd[1] == -1)
		{
			perror(file);
			return (FALSE);
		}
	}
	else
	{
		info->fd[1] = open(file, O_CREAT | O_RDWR | O_APPEND, 0600);
		if (info->fd[1] == -1)
		{
			perror(file);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	pp_check_file(int ac, char **av, t_info *info)
{
	if (!pp_append_or_truncate(info, av[ac -1]))
		return (FALSE);
	if (!info->here_doc)
	{
		if (access(av[1], F_OK) == -1)
		{
			info->infile = FALSE;
			perror(av[1]);
		}
		else
		{
			info->infile = TRUE;
			info->fd[0] = open(av[1], O_RDONLY);
			if (info->fd[0] == -1)
			{
				perror(av[1]);
				return (FALSE);
			}
		}
	}
	return (TRUE);
}

t_bool	pp_check_cmd(int ac, char **av, t_info *info)
{
	char		**path_lst;

	path_lst = ft_split(info->path, ':');
	if (!pp_loop_arg(ac, av, path_lst, info))
	{
		pp_free_double_arr(path_lst);
		return (FALSE);
	}
	pp_free_double_arr(path_lst);
	return (TRUE);
}

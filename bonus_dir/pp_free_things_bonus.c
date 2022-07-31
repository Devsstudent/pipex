/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free_things_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:44:37 by odessein          #+#    #+#             */
/*   Updated: 2022/07/22 17:44:39 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pp_free_things(t_info *info)
{
	if (info->path)
		free(info->path);
	if (info->cmd)
		ft_lstclear(&info->cmd, free);
	if (info->opt)
		ft_lstclear(&info->opt, free);
	if (info->path_cmd)
		ft_lstclear(&info->path_cmd, free);
	if (info->fd[1] != -1)
		close(info->fd[1]);
	if (info->tmp_fd != -1)
		close(info->tmp_fd);
}

void	pp_free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

void	pp_free_and_close(int pipe_fd[2], int *pid, t_info *info)
{
	free(pid);
	pp_free_double_arr(info->arg);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

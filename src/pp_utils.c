/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:32:35 by odessein          #+#    #+#             */
/*   Updated: 2022/07/30 21:39:11 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pp_close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

t_bool	pp_waitpid(int i, int *pid, t_info *info)
{
	int	j;

	close(info->fd[1]);
	j = 0;
	while (j < i)
	{
		if (waitpid(pid[j], NULL, 0) == -1)
		{
			free(pid);
			return (FALSE);
		}
		j++;
	}
	free(pid);
	return (TRUE);
}

void	pp_check_end(t_info *info, int pipe_fd[2])
{
	if (info->end)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

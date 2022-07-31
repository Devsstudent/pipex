/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:14:02 by odessein          #+#    #+#             */
/*   Updated: 2022/07/30 21:34:09 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//Exec all process at the same time 
//Loop on all the command

//Fork for each command

//Sending
t_bool	pp_subprocess(t_info *info, char **envp, int pipe_fd[2]);
t_bool	pp_pipe_fork(int pipe_fd[2], int *pid, t_info *info, char **envp);

t_bool	pp_loop_exec(t_info *info, char **envp)
{
	t_list	*buff;
	int		*pid;
	int		pipe_fd[2];

	pid = (int *) malloc(sizeof(*pid) * ft_lstsize(info->path_cmd));
	if (!pid)
		return (FALSE);
	buff = info->path_cmd;
	info->ind = 0;
	while (buff != NULL)
	{
		if (buff->next == NULL)
			info->end = TRUE;
		info->arg = pp_arg_for_exec(info, info->ind);
		info->cmd_exec = buff->content;
		if (!pp_pipe_fork(pipe_fd, pid, info, envp))
			return (FALSE);
		close(pipe_fd[1]);
		buff = buff->next;
		(info->ind)++;
		pp_free_double_arr(info->arg);
	}
	if (!pp_waitpid(info->ind, pid, info))
		return (FALSE);
	return (TRUE);
}

t_bool	pp_pipe_fork(int pipe_fd[2], int *pid, t_info *info, char **envp)
{
	if (pipe(pipe_fd) == -1)
	{
		free(pid);
		free(info->arg);
		return (FALSE);
	}
	pp_check_end(info, pipe_fd);
	pid[info->ind] = fork();
	if (pid[info->ind] == -1)
	{
		pp_free_and_close(pipe_fd, pid, info);
		return (FALSE);
	}
	else if (pid[info->ind] == 0)
	{
		if (!pp_subprocess(info, envp, pipe_fd))
		{
			pp_free_and_close(pipe_fd, pid, info);
			return (FALSE);
		}
	}
	if (info->tmp_fd != -1)
		close(info->tmp_fd);
	info->tmp_fd = pipe_fd[0];
	return (TRUE);
}

static t_bool	pp_dup_from_last(int pipe[2], int tmp)
{
	close(pipe[0]);
	if (dup2(tmp, STDIN_FILENO) == -1)
	{
		close(pipe[1]);
		return (FALSE);
	}
	if (tmp != -1)
		close(tmp);
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	{
		close(pipe[1]);
		return (FALSE);
	}
	close(pipe[1]);
	return (TRUE);
}

t_bool	pp_dup_subprocess(int pipe_fd[2], t_info *info)
{
	if (info->end)
	{
		if (dup2(info->tmp_fd, STDIN_FILENO) == -1)
		{
			pp_close_pipe(pipe_fd);
			return (FALSE);
		}
		close(info->tmp_fd);
		if (dup2(info->fd[1], STDOUT_FILENO) == -1)
		{
			close(pipe_fd[1]);
			return (FALSE);
		}
		close(info->fd[1]);
	}
	else if (!pp_dup_from_last(pipe_fd, info->tmp_fd))
	{
		pp_close_pipe(pipe_fd);
		return (FALSE);
	}
	if (info->end == FALSE && info->fd[0] != -1)
		close(info->fd[0]);
	return (TRUE);
}

t_bool	pp_subprocess(t_info *info, char **envp, int pipe_fd[2])
{
	if (!pp_dup_subprocess(pipe_fd, info))
		return (FALSE);
	close(pipe_fd[1]);
	close(info->fd[1]);
	if (execve(info->cmd_exec, info->arg, envp) == -1)
	{
		perror(info->cmd_exec);
		return (FALSE);
	}
	return (TRUE);
}

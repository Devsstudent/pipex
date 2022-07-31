/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_infile_outfile_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:14:59 by odessein          #+#    #+#             */
/*   Updated: 2022/07/30 17:34:32 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

t_bool	pp_handle_infile_here_doc(t_info *info, char **av)
{
	if (info->here_doc)
	{
		if (!pp_heredoc(info, av[2]))
		{
			pp_free_things(info);
			return (FALSE);
		}
	}
	else if (info->infile)
			info->tmp_fd = info->fd[0];
	else
		info->tmp_fd = -1;
	return (TRUE);
}

static void	pp_ctrl(t_info *info, char *eof)
{
	char	*error_msg;
	char	*eof_join;

	if (info->ctrld)
	{
		eof_join = ft_strjoin(eof, "')");
		error_msg = ft_strjoin("warning: here-document (wanted `", eof_join);
		ft_putstr_fd(error_msg, 2);
		free(eof_join);
		free(error_msg);
	}
}

t_bool	pp_heredoc(t_info *info, char *eof)
{
	int		fpipe[2];
	char	*buffer;
	char	*eof_n;

	eof_n = ft_strjoin(eof, "\n");
	if (pipe(fpipe) == -1)
		return (-1);
	buffer = get_next_line(0);
	if (!pp_loop_here_doc(info, fpipe, buffer, eof_n))
		return (FALSE);
	pp_ctrl(info, eof);
	close(fpipe[1]);
	free(eof_n);
	info->tmp_fd = fpipe[0];
	return (TRUE);
}

t_bool	pp_loop_here_doc(t_info *info, int fpipe[2], char *buffer, char *eof_n)
{
	while (buffer)
	{
		if (write(fpipe[1], buffer, ft_strlen(buffer)) == -1)
		{
			perror("write Error");
			close(fpipe[1]);
			close(fpipe[0]);
			free(buffer);
			free(eof_n);
			return (FALSE);
		}
		if (ft_strncmp(buffer, eof_n, ft_strlen(buffer)) == 0)
		{
			free(buffer);
			info->ctrld = FALSE;
			info->tmp_fd = fpipe[0];
			return (TRUE);
		}
		free(buffer);
		buffer = get_next_line(0);
	}
	return (TRUE);
}

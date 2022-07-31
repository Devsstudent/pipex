/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:46:05 by odessein          #+#    #+#             */
/*   Updated: 2022/07/28 14:18:51 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	pp_init_info(t_info *info, char **envp)
{
	info->cmd = NULL;
	info->opt = NULL;
	info->path_cmd = NULL;
	info->here_doc = FALSE;
	info->infile = FALSE;
	info->path = pp_get_path(envp);
	info->tmp_fd = -1;
	info->fd[1] = -1;
	info->fd[0] = -1;
	info->ctrld = TRUE;
	info->end = FALSE;
}

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	pp_init_info(&info, envp);
	if (ac == 1 || !info.path || !pp_parse(ac, av, &info))
	{
		pp_free_things(&info);
		return (1);
	}
	if (!pp_handle_infile_here_doc(&info, av))
		return (1);
	if (!pp_loop_exec(&info, envp))
	{
		pp_free_things(&info);
		return (1);
	}
	pp_free_things(&info);
	return (0);
}

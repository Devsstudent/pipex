/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_infile_outfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:14:59 by odessein          #+#    #+#             */
/*   Updated: 2022/07/25 19:14:04 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

t_bool	pp_handle_infile(t_info *info)
{
	if (info->infile)
		info->tmp_fd = info->fd[0];
	else
		info->tmp_fd = -1;
	return (TRUE);
}

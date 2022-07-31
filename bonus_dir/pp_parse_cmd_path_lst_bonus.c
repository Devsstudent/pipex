/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parse_cmd_path_lst_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:36:14 by odessein          #+#    #+#             */
/*   Updated: 2022/07/23 22:17:24 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static	t_bool	pp_fill_new(t_list **new, char *path, char *path_cmd)
{
	*new = ft_lstnew(path_cmd);
	if (!(*new))
	{
		free(path);
		free(path_cmd);
		return (FALSE);
	}
	return (TRUE);
}

void	pp_hardlink_cmd(char *path_lst, char **cmd, char **path,
		char **path_cmd)
{
	*path = ft_strjoin(path_lst, "/");
	*path_cmd = ft_strjoin(*path, *cmd);
}

t_bool	pp_not_in_env(char *cmd, t_bool *valid, t_info *info, t_list *new)
{
	if (!(*valid))
	{
		if (!pp_fill_new(&new, NULL, ft_strjoin("", cmd)))
			return (FALSE);
		ft_lstadd_back(&info->path_cmd, new);
	}
	return (TRUE);
}

t_bool	pp_check_path(char **path_lst, char *cmd, t_bool *valid, t_info *info)
{
	int		i;
	t_list	*new;
	char	*path;
	char	*path_cmd;

	i = -1;
	*valid = FALSE;
	while (path_lst[++i] != 0)
	{
		pp_hardlink_cmd(path_lst[i], &cmd, &path, &path_cmd);
		if (access(path_cmd, F_OK) != -1 && !(*valid))
		{
			if (!pp_fill_new(&new, path, path_cmd))
				return (FALSE);
			ft_lstadd_back(&info->path_cmd, new);
			*valid = TRUE;
		}
		else
			free(path_cmd);
		if (path)
			free(path);
	}
	if (!pp_not_in_env(cmd, valid, info, new))
		return (FALSE);
	return (TRUE);
}

char	**pp_arg_for_exec(t_info *info, int i)
{
	t_list	*buff;
	int		j;
	char	*cmd;
	char	*cmd_opt;
	char	**arg;

	j = -1;
	buff = info->cmd;
	while (++j < i)
		buff = buff->next;
	cmd = ft_strjoin(buff->content, " ");
	j = -1;
	buff = info->opt;
	while (++j < i)
		buff = buff->next;
	cmd_opt = ft_strjoin(cmd, buff->content);
	arg = ft_split(cmd_opt, ' ');
	free(cmd_opt);
	free(cmd);
	if (!arg)
		return (NULL);
	return (arg);
}

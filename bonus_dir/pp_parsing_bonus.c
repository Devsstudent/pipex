/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:39:14 by odessein          #+#    #+#             */
/*   Updated: 2022/07/28 14:20:30 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	pp_parse(int ac, char **av, t_info *info)
{
	int	max;

	max = 5;
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
	{
		info->here_doc = TRUE;
		max = 6;
	}
	if (ac < max)
	{
		ft_putstr_fd("Need at least 4 or 5 arguments if here_doc", 2);
		return (FALSE);
	}
	if (!pp_check_file(ac, av, info))
		return (FALSE);
	if (!pp_check_cmd(ac, av, info))
		return (FALSE);
	return (TRUE);
}

t_bool	pp_loop_arg(int ac, char **av, char **path_lst, t_info *info)
{
	int		i;
	char	*command;
	char	*option;
	t_bool	good;

	command = NULL;
	option = NULL;
	i = 2;
	if (info->here_doc)
		i = 3;
	while (i < ac - 1)
	{
		if (!pp_fill_lst(info, av[i], &command, &option))
			return (FALSE);
		good = FALSE;
		if (!pp_check_path(path_lst, command, &good, info))
			return (FALSE);
		i++;
		free(command);
	}
	return (TRUE);
}

static t_bool	pp_check_new(t_list *new, char *content)
{
	if (!new)
	{
		free(content);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	pp_fill_lst(t_info *info, char *arg, char **cmd, char **option)
{
	t_list	*new;
	int		i;
	char	*content;

	i = 0;
	while (arg[i] != ' ' && arg[i] != 0)
		i++;
	if (i <= 0)
		return (FALSE);
	*option = &(arg[i]);
	*cmd = ft_substr(arg, 0, i);
	content = ft_strdup(*cmd);
	new = ft_lstnew(content);
	if (!pp_check_new(new, content))
		return (FALSE);
	ft_lstadd_back(&info->cmd, new);
	content = ft_strdup(*option);
	new = ft_lstnew(content);
	if (!pp_check_new(new, content))
		return (FALSE);
	ft_lstadd_back(&info->opt, new);
	return (TRUE);
}
